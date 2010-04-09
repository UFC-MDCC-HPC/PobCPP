#include "pobcpp.h"

#include "cc_type.h"

#include <iostream>

bool PObCppPreTypedASTVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}

bool PObCppPreTypedASTVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  if(spec->keyword == TI_UNIT) { // unit?
    FAKELIST_FOREACH_NC(PobcppEnumeratorSpec, spec->enumerators, pobcppEnumSpec) {
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
  return true;
}

bool PObCppVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}


bool PObCppVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  if(spec->keyword == TI_UNIT) { // unit ?
    PQName* pqname = new PQ_name(SourceLoc(), "Pobcpp::Unit"); // Creating base class
    BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname); 
    spec->bases = spec->bases->prepend(bcs); // Adding to the unit
  } 
  else if(spec->keyword == TI_CLASS) {
    unsigned short units = 0;  // How many units exist inside this class?
    FOREACH_ASTLIST_NC(Member, spec->members->list, iter) {
      if(iter.data()->isMR_decl()) {
        MR_decl* iter_decl = iter.data()->asMR_decl();
				if(iter_decl->d->spec->isTS_classSpec()) {
          if(iter_decl->d->spec->asTS_classSpec()->keyword == TI_UNIT)
						units++;
        }
      }
    }
    // Append this definition:
    // Pob_Type_Array __get_types() {
    //   Pob_Type_Array pobtypes(units);
    //   pobtypes.add_type<unit A>(0);
		//   pobtypes.add_type<unit B>(1);
		//   ...	
		//   return pobtypes;
    // }
    DeclFlags dflag = DF_STATIC;
		TS_name *tsname = new TS_name(SourceLoc(), new PQ_name(SourceLoc(), "Pob_Type_Array"), false);
		D_func *dfunc = new D_func(SourceLoc(), new D_name(SourceLoc(), new PQ_name(SourceLoc(), "__get_types")), NULL, CV_NONE, NULL, NULL); // FIXME
		Declarator *decl = new Declarator(dfunc, NULL); // FIXME
				//new Initializer(SourceLoc(), SourceLoc()));
    Function* function = new Function(dflag, tsname, decl, NULL, NULL, NULL); // FIXME
		MR_func *newFunc = new MR_func(SourceLoc(), SourceLoc(), function);
    spec->members->list.append(newFunc);
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

