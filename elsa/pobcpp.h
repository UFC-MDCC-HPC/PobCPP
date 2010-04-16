#ifndef __POBCPPVISITOR_H__
#define __POBCPPVISITOR_H__

#include "cc_ast.h"          // C++ AST (r)
#include "strtable.h" // StringTable
#include <vector>
#include <string>

//FIXME Use a better data structure to handle classes and related units.

struct ClassAndUnit {
	ClassAndUnit(StringRef c, StringRef u) : c(c), u(u) { }
  StringRef c;
	StringRef u;
};

class PObCppPreTypedASTVisitor : public ASTVisitor {
  public:
	StringRef pobTypeArrayStr;
	StringRef addTypeStr;
	std::vector<ClassAndUnit> classes;
	virtual bool visitFunction(Function* func);
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
  private:
  SourceLoc loc;
};

class PObCppVisitor : public ASTVisitor {
  public:
  BasicTypeFactory* bt;
	std::vector<ClassAndUnit> classes;
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	virtual bool visitFunction(Function* func);
  private:
  SourceLoc loc;
	CompoundType* ctype;
};

std::vector<ClassAndUnit> PObCppPre(TranslationUnit *unit);

void PObCppPrint(TranslationUnit *unit, BasicTypeFactory& bt, std::vector<ClassAndUnit>& _classes);

#endif // __POBCPPVISITOR_H__
