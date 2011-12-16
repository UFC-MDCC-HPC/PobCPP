#ifndef __PREPOBCPPVISITOR_H__
#define __PREPOBCPPVISITOR_H__

#include "cc_ast.h"          // C++ AST (r)
#include <vector>
#include <map>
#include <string>
#include "patcher.h"
#include "pobpatch.h"
#include "expr_visitor.h"

class PrePObCppVisitor : public ExpressionVisitor {
  public:
	PrePObCppVisitor(Patcher &patcher);
  void setFile(const char* _file) { file = _file;	}
	
	private:
  virtual bool visitTypeSpecifier(TypeSpecifier *type);
  virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	Patcher &patcher;
	std::string file;
	std::map<int, std::string> patches;
  // TODO
  // Clear patchess on object destruction.
	std::map<int, std::vector<PobcppPatch*> > patchess;

};

void PrePObCpp(TranslationUnit *unit);

#endif // __PREPOBCPPVISITOR_H__
