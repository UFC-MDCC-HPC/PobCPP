#ifndef __PREPOBCPPVISITOR_H__
#define __PREPOBCPPVISITOR_H__

#include "cc_ast.h"          // C++ AST (r)
#include <vector>
#include <map>
#include <string>
#include <stack>
#include "patcher.h"
#include "pobpatch.h"
#include "expr_visitor.h"

class PrePObCppVisitor : public ExpressionVisitor {
  public:
	PrePObCppVisitor(Patcher &patcher);
  ~PrePObCppVisitor();
  void setFile(const char* _file) { file = _file;	}
  std::string getMember(Member *member) const;
	std::map<TS_classSpec*, std::vector<IDeclarator*> >* classDecl;
	
	private:
  std::string getLine(int line) const;
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
  virtual void postvisitTypeSpecifier(TypeSpecifier *type);
  virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	virtual bool subvisitTS_elaborated(TS_elaborated *spec);
  virtual bool visitIDeclarator(IDeclarator* idecl);
  virtual bool visitFunction(Function* func);
	virtual void postvisitFunction(Function* func);
	virtual bool visitExpression(Expression* exp);
  void removeCommunicatorDecl(D_func* dfunc, int noparams, bool body);
  void appendPobunitBaseClass(bool firstBaseClass, int line,
			                        std::string::size_type found);
  bool removeUnitDecl(SourceLoc loc);


	Patcher &patcher;
	std::string file;
  // TODO
  // Clear patchess on object destruction.
	std::map<int, std::vector<PobcppPatch*> > patchess;
	std::stack<TS_classSpec*> sclass;
	std::stack<Function*> sfuncs;

};

void PrePObCpp(TranslationUnit *unit);

#endif // __PREPOBCPPVISITOR_H__
