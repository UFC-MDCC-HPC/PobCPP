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

bool PObCppPreTypedASTVisitor::visitFunction(Function* func) {
	return true;
}
bool PObCppVisitor::visitFunction(Function* func) {
	return true;
}

bool PObCppPreTypedASTVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
		return true;
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}

bool PObCppPreTypedASTVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  if(spec->keyword == TI_UNIT) { // unit?
    if(unitTypeStr == NULL) {
      unitTypeStr = "Unit";
	  }
    // Create base class
		//PQName* pqname = new PQ_qualifier(loc, pobCppNamespaceStr, NULL, new PQ_name(loc, unitTypeStr));
   // BaseClassSpec* bcs = new BaseClassSpec(false, AK_PUBLIC, pqname); 
    //spec->bases = spec->bases->prepend(bcs); // Adding to the unit
  }
  else if(spec->keyword == TI_CLASS) {
    if(spec->name != NULL) {
      if(spec->name->isPQ_name()) {
				/*if(spec->name->asPQ_name()->toString() == "Pob_Type_Array") { //FIXME Check if it is defined inside Pobcpp namespace.					
  	      loc = spec->loc;
      	  pobTypeArrayStr = spec->name->asPQ_name()->name;
          locBool = true;
		 	  } else*/
				if(spec->name->asPQ_name()->toString() == "Unit") { //FIXME Check if it is defined inside Pobcpp namespace.
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
		else
			return true;
    // Append this definition:
    // static Pob_Type_Array __get_types() {
    //   Pob_Type_Array pobtypes(units);
    //   pobtypes.add_type<unit A>(0);
		//   pobtypes.add_type<unit B>(1);
		//   ...	
		//   return pobtypes;
    // }
    DeclFlags dflag = DF_STATIC;
    DeclFlags dflag_decl = DF_NONE;

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
			// FIXME Find a sane way to instantiate the statement below.
      S_expr* sexpr = new S_expr(loc, SourceLoc(), new FullExpression(
                                 new E_funCall(loc, SourceLoc(),
                                               new E_fieldAcc(loc, SourceLoc(),
                                               new E_variable(loc, SourceLoc(), new PQ_name(SourceLoc(), "pobtypes")),
                                               new PQ_template(loc, addTypeStr,
                                                               new TA_type(new ASTTypeId(new TS_name(loc, new PQ_name(loc, classes[i].u), false),new Declarator(new D_name(loc, NULL),NULL)), NULL))), addTypeArgs))); //   pobtypes.add_type<unit A>(0);

			j++;
    }
		S_return* sreturn = new S_return(loc, SourceLoc(), new FullExpression(new E_variable(loc, SourceLoc(), new PQ_name(SourceLoc(), "pobtypes")))); //   return pobtypes;
		stms->append(sreturn);
    Function *function = new Function(dflag, tsname, decl, NULL, new S_compound(loc, SourceLoc(), stms), NULL);
    MR_func *newFunc = new MR_func(loc, SourceLoc(), function);
    //spec->members->list.append(newFunc);
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




bool PObCppVisitor::visitMember(Member *member) { }
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
