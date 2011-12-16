#include "piglet.h"

using namespace std;
static void handle_xBase(Env &env, xBase &x)
{
  // typically an assertion failure from the tchecker; catch it here
  // so we can print the errors, and something about the location
  env.errors.print(cout);
  cout << x << endl;
  cout << "Failure probably related to code near " << env.locStr() << endl;

  // print all the locations on the scope stack; this is sometimes
  // useful when the env.locStr refers to some template code that
  // was instantiated from somewhere else
  //
  // (unfortunately, env.instantiationLocStack isn't an option b/c
  // it will have been cleared by the automatic invocation of
  // destructors unwinding the stack...)
  cout << "current location stack:\n";
  cout << env.locationStackString();

  // I changed from using exit(4) here to using abort() because
  // that way the multitest.pl script can distinguish them; the
  // former is reserved for orderly exits, whereas signals (like
  // SIGABRT) mean that something went really wrong
  abort();
}


PigletParser::PigletParser(bool prePobcpp) : parseWarnings(0), prePobcpp(prePobcpp) {
  lang.GNU_Cplusplus();
}

template<typename R> R
PigletParser::apply(std::unary_function<TranslationUnit*,R> func,
		    const char *filename)
{
  PigletParser parser;
  TranslationUnit *unit = parser.getASTNoExc(filename);
  return func(unit);
}

TranslationUnit *
PigletParser::getAST(const char *filename)
{
  TranslationUnit *unit = parse(filename);
	if(prePobcpp)
		return unit;
  typeCheck(unit);
  elaborate(unit);
  return unit;
}

TranslationUnit *
PigletParser::getASTNoExc(const char *filename)
{
  // I think this is more noise than signal at this point
  xBase::logExceptions = false;

  try {
    return getAST(filename);
  }
  catch (XUnimp &x) {
    HANDLER();
    cout << x << endl;
    exit(10);
  }
  catch (XFatal &x) {
    HANDLER();
    cout << x << endl;
    exit(10);
	}
  catch (xBase &x) {
    HANDLER();
    cout << x << endl;
    abort();
  }
}

TranslationUnit *
PigletParser::parse(const char *inputFname)
{
    SemanticValue treeTop;
    ParseTreeAndTokens tree(lang, treeTop, strTable, inputFname);

    // make elsa not complain about template ambiguities that arise, among
    // other places, in gcc's <algorithm>
    traceAddSys("permissive");
  
    // grab the lexer so we can check it for errors (damn this
    // 'tree' thing is stupid..)
    Lexer *lexer = dynamic_cast<Lexer*>(tree.lexer);
    xassert(lexer);

    CCParse *parseContext = new CCParse(strTable, lang);
    tree.userAct = parseContext;

    traceProgress(2) << "building parse tables from internal data\n";
    ParseTables *tables = parseContext->makeTables();
    tree.tables = tables;

    maybeUseTrivialActions(tree);

    if (!toplevelParse(tree, inputFname)) {
      exit(2); // parse error
    }

    // check for parse errors detected by the context class
    if (parseContext->errors || lexer->errors) {
      exit(2);
    }
    parseWarnings = lexer->warnings + parseContext->warnings;

    // treeTop is a TranslationUnit pointer
		TranslationUnit *unit = (TranslationUnit*) treeTop;

		if(!prePobcpp)
	  	classes = PObCppPre(unit); // PObC++ modification.
    delete parseContext;
    delete tables;

    return unit;
}

void 
PigletParser::typeCheck(TranslationUnit *unit)
  {
    Env env(strTable, lang, tfac, madeUpVariables, builtinVars, unit);

    try {
      env.tcheckTranslationUnit(unit);
      PObCppPos(unit); // PObC++ modification.
    }
    catch (XUnimp &x) {
      HANDLER();

      // relay to handler in main()
      cout << "in code near " << env.locStr() << ":\n";
      throw;
    }
    catch (x_assert &x) {
      HANDLER();

      if (env.errors.hasFromNonDisambErrors()) {
        if (tracingSys("expect_confused_bail")) {
          cout << "got the expected confused/bail\n";
          exit(0);
        }
	// see comment about 'confused' in elsa main.cc
        env.error("confused by earlier errors, bailing out");
        env.errors.print(cout);
        exit(4);
      }
      // if we don't have a basis for reducing severity, pass this on
      // to the normal handler
      handle_xBase(env, x);
    }
    catch (xBase &x) {
      HANDLER();
      handle_xBase(env, x);
    }

    int numErrors = env.errors.numErrors();
    int numWarnings = env.errors.numWarnings() + parseWarnings;

    if (numErrors != 0 || numWarnings != 0) {
      // print errors and warnings
      env.errors.print(cout);

      cout << "typechecking results:\n"
	   << "  errors:   " << numErrors << "\n"
	   << "  warnings: " << numWarnings << "\n";
    }

    if (numErrors != 0) {
      exit(4);
    }
  }

void 
PigletParser::elaborate(TranslationUnit *unit)
  {
    ElabVisitor vis(strTable, tfac, unit);
    if (!lang.isCplusplus) {
      vis.activities = EA_C_ACTIVITIES;
    }
    unit->traverse(vis.loweredVisitor);
  }

