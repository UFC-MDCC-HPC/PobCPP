#include "pobcpp.h"

#include "cc_type.h"

#include <iostream>
#include <sstream>
#include <string>

//Helper function
char* itoa(int value) {
  std::string str;
  std::stringstream out;
  out << value;
  str = out.str();
	char* s = new char[str.size()];
	return strcpy(s, str.c_str());
}
bool PObCppPreTypedASTVisitor::visitTopForm(TopForm* tf) {
	if(tf->isTF_namespaceDefn()) {
    if(tf->isTF_namespaceDefn()) {
      if(tf->asTF_namespaceDefn()->name != NULL)
        if(std::string(tf->asTF_namespaceDefn()->name) == "Pobcpp") {
          pobCppNamespaceStr = tf->asTF_namespaceDefn()->name;
        }
    }
	}
	return true;
}

bool PObCppPreTypedASTVisitor::visitFunction(Function* function) {
  if(function->nameAndParams != NULL) {
    if(function->nameAndParams->decl->isD_func()) {
      if(function->nameAndParams->decl->asD_func()->base->isD_name()) {
        if(function->nameAndParams->decl->asD_func()->base->asD_name()->name->isPQ_name()) {
          PQ_name* funcName = function->nameAndParams->decl->asD_func()->base->asD_name()->name->asPQ_name();
          if(funcName->toString() == "add_type")
            addTypeStr =funcName->name;
        }
      }
		}
  }
	return true;
}

bool PObCppPreTypedASTVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}

MR_decl* createEnumerator(StringRef name) {
  DeclFlags toApply = DF_NONE;
  FakeList<Declarator>* declList; 
  Declarator* decl = new Declarator(new D_name(SourceLoc(),
                                    new PQ_name(SourceLoc(), name)),
                                    NULL);
  
  declList = FakeList<Declarator>::makeList(decl);
  TypeSpecifier *constInt = new TS_simple(SourceLoc(), ST_UNSIGNED_INT);
  constInt->setCVOnce(CV_CONST);
  return new MR_decl(SourceLoc(), SourceLoc(), new Declaration(toApply, constInt, declList));

}

bool PObCppPreTypedASTVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  if(spec->keyword == TI_UNIT) { // unit?
		// Adding "real" enumerators to unit definition.
    FAKELIST_FOREACH_NC(PobcppEnumeratorSpec, spec->enumerators, pobcppEnumSpec) {
      spec->members->list.append(createEnumerator(pobcppEnumSpec->name));
      spec->members->list.append(createEnumerator(pobcppEnumSpec->size));
    }

    if(unitTypeStr == NULL) {
      unitTypeStr = "Unit";
	  }
    // Create base class
		PQName* pqname = new PQ_qualifier(loc, pobCppNamespaceStr, NULL, new PQ_name(loc, unitTypeStr));
    BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname); 
    spec->bases = spec->bases->prepend(bcs); // Adding to the unit
  }
  else if(spec->keyword == TI_CLASS) {
    if(spec->name != NULL) {
      if(spec->name->isPQ_name()) {
	      if(spec->name->asPQ_name()->toString() == "Pob_Type_Array") { //FIXME Check if it is defined inside Pobcpp namespace.
  	      loc = spec->loc;
      	  pobTypeArrayStr = spec->name->asPQ_name()->name;
		 	  } else if(spec->name->asPQ_name()->toString() == "Unit") { //FIXME Check if it is defined inside Pobcpp namespace.
            unitTypeStr = spec->name->asPQ_name()->name;
        } else {
            locBool = false;
        }
      }
    }
    unsigned short units = 0;  // How many units exist inside this class?
    FOREACH_ASTLIST_NC(Member, spec->members->list, iter) {
      if(iter.data()->isMR_decl()) {
        MR_decl* iter_decl = iter.data()->asMR_decl();
        if(iter_decl->d->spec->isTS_classSpec()) {
          if(iter_decl->d->spec->asTS_classSpec()->keyword == TI_UNIT) {
            units++;
            classes.push_back(ClassAndUnit(spec->name->asPQ_name()->name,
                                           iter_decl->d->spec->asTS_classSpec()->name->asPQ_name()->name,
                                           iter_decl->d->spec->asTS_classSpec()->enumerators->count()));
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
    DeclFlags dflag = DF_STATIC;
    DeclFlags dflag_decl = DF_NONE;
    if(locBool == false)
      return true;
    checkStrings();

		TS_name* tsname = new TS_name(loc, new PQ_qualifier(loc, pobCppNamespaceStr, NULL, new PQ_name(loc, pobTypeArrayStr)), false);
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
    ArgExpression* arg = new ArgExpression(new E_intLit(loc, SourceLoc(), itoa(units)));
    args = FakeList<ArgExpression>::makeList(arg);
    Declarator* declpobtypes = new Declarator(new D_name(SourceLoc(),
                                              new PQ_name(SourceLoc(), "pobtypes")),
                                              new IN_ctor(loc, args));
      
    declList = FakeList<Declarator>::makeList(declpobtypes);

    S_decl* sdecl = new S_decl(loc, SourceLoc(), new Declaration(dflag_decl, new TS_name(loc, new PQ_qualifier(loc, pobCppNamespaceStr, NULL, new PQ_name(loc, pobTypeArrayStr)) , false), declList)); // Pob_Type_Array pobtypes(units);
    stms->append(sdecl);

		unsigned int j = 0; // Unit order
    for(unsigned int i = 0; i < classes.size(); i++) { // FIXME Better search algorithm.
			if(classes[i].c != spec->name->asPQ_name()->name)
				continue;
      FakeList<ArgExpression>* addTypeArgs;
      ArgExpression* arg1 = new ArgExpression(new E_intLit(loc, SourceLoc(), itoa(j)));
			if(classes[i].enumerators != 0) {
      	ArgExpression* arg2 = new ArgExpression(new E_intLit(loc, SourceLoc(), itoa(classes[i].enumerators)));
      	addTypeArgs = FakeList<ArgExpression>::makeList(arg2);
				addTypeArgs = addTypeArgs->prepend(arg1);
			} else {
      	addTypeArgs = FakeList<ArgExpression>::makeList(arg1);
			}
			// FIXME Find a sane way to instantiate the below statement.
      S_expr* sexpr = new S_expr(loc, SourceLoc(), new FullExpression(
                                 new E_funCall(loc, SourceLoc(),
                                               new E_fieldAcc(loc, SourceLoc(),
                                               new E_variable(loc, SourceLoc(), new PQ_name(SourceLoc(), "pobtypes")),
                                               new PQ_template(loc, addTypeStr,
                                                               new TA_type(new ASTTypeId(new TS_name(loc, new PQ_name(loc, classes[i].u), false),new Declarator(new D_name(loc, NULL),NULL)), NULL))), addTypeArgs))); //   pobtypes.add_type<unit A>(0);

      stms->append(sexpr);
			j++;
    }
		S_return* sreturn = new S_return(loc, SourceLoc(), new FullExpression(new E_variable(loc, SourceLoc(), new PQ_name(SourceLoc(), "pobtypes")))); //   return pobtypes;
		stms->append(sreturn);
    Function *function = new Function(dflag, tsname, decl, NULL, new S_compound(loc, SourceLoc(), stms), NULL);
    MR_func *newFunc = new MR_func(loc, SourceLoc(), function);
    spec->members->list.append(newFunc);
  }
  return true;
}

void PObCppPreTypedASTVisitor::checkStrings() { 
  if(pobCppNamespaceStr == NULL) {
    pobCppNamespaceStr = "Pobcpp";
  }
  if(pobTypeArrayStr == NULL) {
	  pobTypeArrayStr = "Pob_Type_Array";
	}
  if(addTypeStr == NULL) {
    addTypeStr = "add_type";
  }
}


bool PObCppVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
	// FIXME
  /*if(spec->keyword == TI_UNIT) { // unit ?
    PQName* pqname = new PQ_name(SourceLoc(), "Pobcpp::Unit"); // Creating base class
    BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname); 
    spec->bases = spec->bases->prepend(bcs); // Adding to the unit
  }*/
  return true;
}

bool PObCppVisitor::visitMember(Member *member) {
  if(member->isMR_func()) {
    if(member->asMR_func()->f->retspec->isTS_simple()) {
      if(member->asMR_func()->f->retspec->asTS_simple()->id & ST_CDTOR) {
//        std::cout << "Eh um construtor" << std::endl;
//        std::cout << member->asMR_func()->f->receiver->type->toString() << std::endl;
        //std::cout << member->asMR_func()->f->receiver->type-> << std::endl;
        if(member->asMR_func()->f->receiver->type->isPseudoInstantiation()) {
//          std::cout << "Eh um tipo composto" << std::endl;
          //if (member->asMR_func()->f->receiver->type->asCVAtomicType()->atomic->isCompoundType()) { }
          //if(member->asMR_func()->f->receiver->type->asCompoundType()->keyword == TI_UNIT)
          //if(member->asMR_func()->f->receiver->type->isCompoundTypeOf(CompoundType::K_UNIT))
//            std::cout << "Pitomba3" << std::endl;
        }
      }
    }
  }
  return true;
}

std::vector<ClassAndUnit> PObCppPre(TranslationUnit *unit) {
  PObCppPreTypedASTVisitor fp;
	fp.pobCppNamespaceStr = NULL;
	fp.pobTypeArrayStr = NULL;
	fp.addTypeStr = NULL;
	fp.unitTypeStr = NULL;
  unit->traverse(fp);
	return fp.classes; // FIXME create a get_classesAndUnits() function.
}
void PObCppPos(TranslationUnit *unit) {
  PObCppVisitor fp;
  unit->traverse(fp);
}
