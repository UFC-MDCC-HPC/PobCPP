#include "pobcpp1st.h"

bool Pobcpp1stPass::visitTypeSpecifier(TypeSpecifier *type) {
	if(type->isTS_classSpec())
		if(type->asTS_classSpec()->keyword == TI_UNIT)
			sclass.push(type->asTS_classSpec());
	return true;
}

void Pobcpp1stPass::postvisitTypeSpecifier(TypeSpecifier *type) {
	if(type->isTS_classSpec())
		if(type->asTS_classSpec()->keyword == TI_UNIT)
			sclass.pop();
}

bool Pobcpp1stPass::visitFunction(Function* func) {
	sfuncs.push(func);
	return true;
}

void Pobcpp1stPass::postvisitFunction(Function* func) {
	sfuncs.pop();
}

bool Pobcpp1stPass::visitIDeclarator(IDeclarator* idecl) {
	if(idecl->isD_func()) {
		D_func* dfunc = idecl->asD_func();
		if((!sclass.empty()) && (dfunc->comm != NULL)) {
			classDecl[sclass.top()].push_back(dfunc);
		}
	}
}
