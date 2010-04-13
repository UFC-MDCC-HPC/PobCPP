#ifndef __POBCPPVISITOR_H__
#define __POBCPPVISITOR_H__

#include "cc_ast.h"       // C++ AST (r)

class PObCppPreTypedASTVisitor : public ASTVisitor {
  public:
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
  private:
  SourceLoc loc;
};

class PObCppVisitor : public ASTVisitor {
  public:
  BasicTypeFactory* bt;
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	virtual bool visitFunction(Function* func);
  private:
  SourceLoc loc;
	CompoundType* ctype;
};

void PObCppPre(TranslationUnit *unit);
void PObCppPrint(TranslationUnit *unit, BasicTypeFactory& bt);

#endif // __POBCPPVISITOR_H__
