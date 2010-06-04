// Stopwatch: given a list of methods, injects instrumentation code into them
#include "piglet.h"
#include "expr_visitor.h"
#include "patcher.h"
#include <set>
#include <sstream>
#include <string>
using namespace std;

static set<sm::string> methods;

class Stopwatch : public ExpressionVisitor
{
public:
  Stopwatch(Patcher &patcher):patcher(patcher) {
  }
  virtual bool visitFunction(Function *func) {
    Variable *v = func->nameAndParams->var;
    if (v->isImplicitMemberFunc())
      return false;

    sm::string fullname = v->fullyQualifiedName0();
    if (methods.find(fullname) != methods.end()) {
      return false;
    }
    S_compound *body = func->body->asS_compound();
    // punt on headers
    char const *file = sourceLocManager->getFile(body->loc);
    if (!strstr(file, ".cpp"))
      return false;
    
    CPPSourceLoc csl(body->loc);

    if (!csl.hasExactPosition())
      return false;
  
    string indent = "\n";

    if (body->stmts.isEmpty())
      return false;

    Statement *firstStatement = body->stmts.first();

    // functions that begin with a return usually aren't interesting
    if (firstStatement->isS_return())
      return false;

    CPPSourceLoc endcsl(firstStatement->loc);
    if (!endcsl.hasExactPosition()) {
      if (endcsl.macroExpansion)
        endcsl.overrideLoc(endcsl.macroExpansion->preStartLoc);
      indent = patcher.getRange(PairLoc(csl, endcsl));
      //get rid of {
      if (indent.size())
        indent.erase(0,1);
      string::size_type endline = indent.rfind("\n");
      if (endline != string::npos) {
        indent.erase(0, endline);
      }
    }

    stringstream ss;
    ss << indent << "InstrumentBlock __ib(\"" << fullname
       << "\");";
    patcher.insertBefore(csl, ss.str(), 1);
    ensureInclude(file);
    return false;
  }
  
  void ensureInclude (char const *file) {
    if (files.find(file) != files.end())
      return;
    files.insert(file);
    ifstream f(file);
    string linestr;
    int line = 0;
    while (getline(f, linestr)) {
      ++line;
      if (!strncmp("#include", linestr.c_str(), 8)) {
        UnboxedLoc loc(line, 1);
        patcher.insertBefore(file, loc, "#include \"instrument.h\"\n");
        break;
      }
    }
    f.close();
  }

private:
  Patcher &patcher;
  set<char const *> files;
};

int main(int argc, char **argv)
{
  int curarg = 1;
  if (curarg + 1 < argc && !strcmp("--methodlist", argv[curarg])) {
    ifstream f(argv[++curarg]);
    string line;
    while (getline(f, line)) {
      methods.insert(line.c_str());
    }
    f.close();
    ++curarg;
  }
  PigletParser parser;
  Patcher p;
  Stopwatch visitor(p);
  for (int i = curarg;i< argc;i++) {
    TranslationUnit *unit = parser.getASTNoExc(argv[i]);
    unit->traverse(visitor);
  }
  return 0;
}
