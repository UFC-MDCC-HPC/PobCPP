#include "pobcpp.h"

#include <iostream>
#include "cc_type.h"

bool PObCppPreTypedASTVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}

bool PObCppPreTypedASTVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  // Checking if it is a Unit.
  if(spec->keyword == TI_UNIT) {
//		PQName* pqname = new PQ_name(SourceLoc(), "Pobcpp::Unit");
//		BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname);
//		spec->bases = spec->bases->prepend(bcs);

    FakeList<PobcppEnumeratorSpec> *pobcppEnum = spec->enumerators;
    if(pobcppEnum->isNotEmpty()) {
      int size = pobcppEnum->count();
      for(int i = 0; i < size; i++) {
        PobcppEnumeratorSpec *pobcppEnumSpec = pobcppEnum->nth(i);

        DeclFlags toApply = DF_NONE;
        FakeList<Declarator>* declList; 
        Declarator* decl = new Declarator(new D_name(SourceLoc(),
                                          new PQ_name(SourceLoc(), pobcppEnumSpec->name)),
                                          NULL);
        
        declList = FakeList<Declarator>::makeList(decl);
        TypeSpecifier *constInt = new TS_simple(SourceLoc(), ST_INT);
        constInt->setCVOnce(CV_CONST);
        MR_decl *newEnumerator = new MR_decl(SourceLoc(), SourceLoc(), new Declaration(toApply, constInt, declList));
        spec->members->list.append(newEnumerator);
      }
    }

  }
  return true;
}

bool PObCppVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}


bool PObCppVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  // Checking if it is a Unit.
  if(spec->keyword == TI_UNIT) {
		PQName* pqname = new PQ_name(SourceLoc(), "Pobcpp::Unit"); // Creating base class
		BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname); 
		spec->bases = spec->bases->prepend(bcs); // Adding to the unit
  }
  return true;
}

void PObCppPre(TranslationUnit *unit) {
  PObCppPreTypedASTVisitor fp;
  unit->traverse(fp);
}
void PObCppPrint(TranslationUnit *unit) {
  PObCppVisitor fp;
  unit->traverse(fp);
}

