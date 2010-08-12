#ifndef MOZ_STATIC_ANALYSIS_PIGLET
#define MOZ_STATIC_ANALYSIS_PIGLET

#include <stdlib.h>       // exit, getenv, abort
#include "parssppt.h"     // ParseTreeAndTokens, treeMain

// TODO remove some of these headers
#include "srcloc.h"       // SourceLocManager
#include "ckheap.h"       // malloc_stats
#include "cc_env.h"       // Env
#include "cc_ast.h"       // C++ AST (r)
#include "cc_ast_aux.h"   // class LoweredASTVisitor
#include "cc_lang.h"      // CCLang
#include "parsetables.h"  // ParseTables
#include "cc_print.h"     // PrintEnv
#include "cc.gr.gen.h"    // CCParse
#include "nonport.h"      // getMilliseconds
#include "ptreenode.h"    // PTreeNode
#include "ptreeact.h"     // ParseTreeLexer, ParseTreeActions
#include "sprint.h"       // structurePrint
#include "strtokp.h"      // StrtokParse
#include "smregexp.h"     // regexpMatch
#include "cc_elaborate.h" // ElabVisitor
#include "integrity.h"    // IntegrityVisitor
#include "xml_file_writer.h" // XmlFileWriter
#include "xml_reader.h"   // xmlDanglingPointersAllowed
#include "xml_do_read.h"  // xmlDoRead()
#include "xml_type_writer.h" // XmlTypeWriter
#include "elsa/pobcpp.h"
#include <functional>

// C++ Parser
//
// Note: the pointer returned by getAST is valid only as long as this
//       object is still alive. (It secretly relies on the private data
//       manager fields declared here.)
class PigletParser {
public:
  PigletParser();

  // Parse the file and call the given fn with the AST.
  template<typename R>
  static R apply(std::unary_function<TranslationUnit*,R> func,
		 const char *filename);

  // Parse the file and return the AST. This may throw Elsa exns.
  TranslationUnit *getAST(const char *filename);
  // Parse the file and return the AST. Die on errors.
  TranslationUnit *getASTNoExc(const char *filename);
  std::vector<ClassAndUnit> classes; // PObC++ modification.
private:
  CCLang lang;
  
  SourceLocManager mgr;
  StringTable strTable;
  BasicTypeFactory tfac;
  
  ArrayStack<Variable*> madeUpVariables;
  ArrayStack<Variable*> builtinVars;

  int parseWarnings;

  TranslationUnit *parse(const char *inputFname);
  void typeCheck(TranslationUnit *unit);
  void elaborate(TranslationUnit *unit);
};

#endif // MOZ_STATIC_ANALYSIS_PIGLET
