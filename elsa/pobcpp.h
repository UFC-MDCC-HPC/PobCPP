#ifndef __POBCPPVISITOR_H__
#define __POBCPPVISITOR_H__

#include "cc_ast.h"       // C++ AST (r)

class PObCppPreTypedASTVisitor : public ASTVisitor {
  public:
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
};

class PObCppVisitor : public ASTVisitor {
  public:
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
};

void PObCppPre(TranslationUnit *unit);
void PObCppPrint(TranslationUnit *unit);

#endif // __POBCPPVISITOR_H__
