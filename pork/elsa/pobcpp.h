#ifndef __POBCPPVISITOR_H__
#define __POBCPPVISITOR_H__

#include "cc_ast.h"          // C++ AST (r)
#include <vector>
#include <string>

//FIXME Use a better data structure to handle classes and related units.

struct ClassAndUnit {
	ClassAndUnit(StringRef c, StringRef u, unsigned int enumerators = 0) : c(c), u(u), enumerators(enumerators) { }
  StringRef c;
	StringRef u;
	unsigned int enumerators;
};

class PObCppPreTypedASTVisitor : public ASTVisitor {
  public:
  PObCppPreTypedASTVisitor() { locBool = false; }
  StringRef pobCppNamespaceStr;
  StringRef pobTypeArrayStr;
  StringRef addTypeStr;
  StringRef unitTypeStr;
  std::vector<ClassAndUnit> classes;
  
  virtual bool visitTopForm(TopForm* tf);
  virtual bool visitFunction(Function* func);
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
  virtual bool subvisitTS_classSpec(TS_classSpec *spec);

  private:
  void checkStrings();
  SourceLoc loc;
  bool locBool;
};

class PObCppVisitor : public ASTVisitor {
  public:
  PObCppVisitor() { locBool = false; }
  virtual bool visitMember(Member *member);
  virtual bool subvisitTS_classSpec(TS_classSpec *spec);
  private:
  SourceLoc loc;
  bool locBool;
  CompoundType* ctype;
};

std::vector<ClassAndUnit> PObCppPre(TranslationUnit *unit);
void PObCppPos(TranslationUnit *unit);

void PObCppPrint(TranslationUnit *unit, BasicTypeFactory& bt, std::vector<ClassAndUnit>& _classes);

#endif // __POBCPPVISITOR_H__
