#include "pobcpp.h"

#include "cc_type.h"

#include <iostream>
#include <sstream>

//Helper function
char* itoa(int value) {
  std::string str;
  std::stringstream out;
  out << value;
  str = out.str();
	char* s = new char[str.size()];
	return strcpy(s, str.c_str());
}

bool PObCppPreTypedASTVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}

bool PObCppPreTypedASTVisitor::visitFunction(Function* function) {
  if(function->nameAndParams != NULL) {
    if(function->nameAndParams->decl->isD_func()) {
      if(function->nameAndParams->decl->asD_func()->base->isD_name()) {
        PQ_name* funcName = function->nameAndParams->decl->asD_func()->base->asD_name()->name->asPQ_name();
        if(funcName->toString() == "add_type")
          addTypeStr =funcName->name;
      }
		}
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
      TypeSpecifier *constInt = new TS_simple(SourceLoc(), ST_UNSIGNED_INT);
      constInt->setCVOnce(CV_CONST);
      MR_decl *newEnumerator = new MR_decl(SourceLoc(), SourceLoc(), new Declaration(toApply, constInt, declList));
      spec->members->list.append(newEnumerator);
    }
  }
  else if(spec->keyword == TI_CLASS) {
    if(spec->name->toString() == "Pob_Type_Array") {
      loc = spec->loc;
      if(spec->name->isPQ_name())
        pobTypeArrayStr = spec->name->asPQ_name()->name;
		}
    unsigned short units = 0;  // How many units exist inside this class?
    FOREACH_ASTLIST_NC(Member, spec->members->list, iter) {
      if(iter.data()->isMR_decl()) {
        MR_decl* iter_decl = iter.data()->asMR_decl();
        if(iter_decl->d->spec->isTS_classSpec()) {
          if(iter_decl->d->spec->asTS_classSpec()->keyword == TI_UNIT) {
            units++;
            classes.push_back(ClassAndUnit(spec->name->asPQ_name()->name,
                                           iter_decl->d->spec->asTS_classSpec()->name->asPQ_name()->name));
          }
        }
      }
    }
		if(!units)
			return true;
    // Append this definition:
    // Pob_Type_Array __get_types() {
    //   Pob_Type_Array pobtypes(units);
    //   pobtypes.add_type<unit A>(0);
		//   pobtypes.add_type<unit B>(1);
		//   ...	
		//   return pobtypes;
    // }
    DeclFlags dflag = DF_NONE;
		
	//	TS_simple* tsname = new TS_simple(loc, ST_INT); // We will exchange this int for a Pob_Type_Array.
		if(pobTypeArrayStr == NULL) {
			pobTypeArrayStr = "Pob_Type_Array";
		}
    if(addTypeStr == NULL) {
      addTypeStr = "add_type";
    }
		TS_name* tsname = new TS_name(loc, new PQ_name(loc, pobTypeArrayStr), false);
		D_func *dfunc = new D_func(loc, 
                               new D_name(loc, new PQ_name(loc, "__get_types")),
                               NULL,
                               CV_NONE,
                               NULL,
                               NULL);
    Declarator *decl = new Declarator(dfunc, NULL);

		// Function body
    ASTList<Statement>* stms = new ASTList<Statement>();
    FakeList<ArgExpression>* args;
    FakeList<Declarator>* declList; 
    ArgExpression* arg = new ArgExpression(new E_intLit(loc, SourceLoc(), itoa(units))); //FIXME exchange 42 for units
    args = FakeList<ArgExpression>::makeList(arg);
    Declarator* declpobtypes = new Declarator(new D_name(SourceLoc(),
                                              new PQ_name(SourceLoc(), "pobtypes")),
                                              new IN_ctor(loc, args));
      
    declList = FakeList<Declarator>::makeList(declpobtypes);

    S_decl* sdecl = new S_decl(loc, SourceLoc(), new Declaration(dflag, new TS_name(loc, new PQ_name(loc, pobTypeArrayStr) , false), declList));
    stms->append(sdecl);

    for(unsigned int i = 0; i < units; i++) {
      FakeList<ArgExpression>* addTypeArgs;
      ArgExpression* arg1 = new ArgExpression(new E_intLit(loc, SourceLoc(), itoa(i))); //FIXME exchange 42 for units
      addTypeArgs = FakeList<ArgExpression>::makeList(arg1);
      S_expr* sexpr = new S_expr(loc, SourceLoc(), new FullExpression(
                                 new E_funCall(loc, SourceLoc(),
                                               new E_fieldAcc(loc, SourceLoc(),
                                               new E_variable(loc, SourceLoc(), new PQ_name(SourceLoc(), "pobtypes")),
                                                              new PQ_template(loc, addTypeStr, 
                                                                              new TA_type(new ASTTypeId(new TS_name(loc, new PQ_name(loc, classes[i].u), false),new Declarator(new D_name(loc, NULL),NULL)), NULL))), addTypeArgs)));

      stms->append(sexpr);
    }
    Function *function = new Function(dflag, tsname, decl, NULL, new S_compound(loc, SourceLoc(), stms), NULL);
    MR_func *newFunc = new MR_func(loc, SourceLoc(), function);
    spec->members->list.append(newFunc);
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
	// FIXME
  if(spec->keyword == TI_UNIT) { // unit ?
    PQName* pqname = new PQ_name(SourceLoc(), "Pobcpp::Unit"); // Creating base class
    BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname); 
    spec->bases = spec->bases->prepend(bcs); // Adding to the unit
  }
  return true;
}

bool PObCppVisitor::visitFunction(Function* func) {
	return true;
}

std::vector<ClassAndUnit> PObCppPre(TranslationUnit *unit, StringTable* table) {
  PObCppPreTypedASTVisitor fp;
	fp.table = table;
	fp.pobTypeArrayStr = NULL;
	fp.addTypeStr = NULL;
  unit->traverse(fp);
	return fp.classes; // FIXME create a get_classesAndUnits() function.
}
void PObCppPrint(TranslationUnit *unit, BasicTypeFactory& bt, std::vector<ClassAndUnit>& _classes) {
  PObCppVisitor fp;
  fp.bt = &bt;
	fp.classes = _classes; //FIXME create a constructor. 

  unit->traverse(fp);
}

