#ifndef __POBCPP1ST_H__
#define __POBCPP1ST_H__

#include "cc_ast.h"
#include <vector>
#include <map>
#include <string>
#include <stack>
#include "expr_visitor.h"

class Pobcpp1stPass : public ExpressionVisitor {
	public:
	Pobcpp1stPass() { }
	~Pobcpp1stPass() { }

	std::stack<TS_classSpec*> sclass;
	std::map<TS_classSpec*, std::vector<IDeclarator*> > classDecl;
	std::stack<Function*> sfuncs;

	private:

  virtual bool visitTypeSpecifier(TypeSpecifier *type);
  virtual void postvisitTypeSpecifier(TypeSpecifier *type);
  virtual bool visitIDeclarator(IDeclarator* idecl);
  virtual bool visitFunction(Function* func);
	virtual void postvisitFunction(Function* func);

};



#endif
