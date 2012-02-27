#include "prepobcpp.h"
#include "piglet.h"

#include "cc_type.h"

#include <map>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "patcher.h"
#include "expr_visitor.h"
#include "elsa/pobcpp.h"

//#define POBCPPDEBUG

PrePObCppVisitor::PrePObCppVisitor(Patcher &patcher) : patcher(patcher) { } 

PrePObCppVisitor::~PrePObCppVisitor() {
  using std::string;
  using std::map;
  using std::pair;
  using std::vector;
  string original_file = file;
  map<int, vector<PobcppPatch*> >::iterator iter;
  for(iter = patchess.begin(); iter != patchess.end(); ++iter ) {
    std::sort(iter->second.begin(), iter->second.end(), PobcppPatchCmp());
    vector<PobcppPatch*>::const_iterator viter;
    int iline = iter->first;
    std::string sline  = patcher.getLine(iline, file);
    std::string line = sline;
    int diff = 0;
    for(viter = iter->second.begin(); viter != iter->second.end(); ++viter) {
      PobcppPatch* patch = *viter;
      if(patch->kind == Insert) {
        sline.insert(diff + patch->col-1, patch->str);
        diff += patch->str.length();
      }
      else {
        if(patch->erase == 0) {
          sline.erase(diff+ patch->col-1, sline.size() - patch->col+1);
        }
        else {
          diff -= patch->erase;
          sline.erase(diff+ patch->col-1, patch->erase);
        }
      }
    }
    sline += " //";
    patcher.insertBefore(original_file.c_str(), UnboxedLoc(iter->first, 1), sline);
  }
  // FIXME
  patchess.clear();
}

std::string PrePObCppVisitor::getLine(int line) const {
  return patcher.getLine(line, file);
}

std::string PrePObCppVisitor::getMember(Member *member) const {
  SourceLoc beg = member->loc;
  SourceLoc end = member->endloc;
  int begLine = sourceLocManager->getLine(beg);
  int begCol = sourceLocManager->getCol(beg);
  int endLine = sourceLocManager->getLine(end);
  int endCol = sourceLocManager->getCol(end);
  if(begLine == endLine) {
    std::string line = getLine(begLine).substr(begCol-1, endCol-begCol);
    return line;
  } else {
    //FIXME
    std::string lines;
    for(int i = begLine; i <= endLine; i++) {
      if(i == begLine) {
        std::string line =  getLine(i);
        int size = line.size();
        lines += line.substr(begCol-1, size-begCol+1);
      } else if(i == endLine) {
        std::string line =  getLine(i);
        int size = line.size();
        lines += line.substr(0, endCol);
      }
      else {
        lines += getLine(i);
      }
    }
    return lines;
  }
}

bool PrePObCppVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}

void PrePObCppVisitor::postvisitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) 
		if(type->asTS_classSpec()->keyword == TI_UNIT)
			sclass.pop();
}

bool PrePObCppVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
  // check if attributes or methods are declared.
  // Include them on inner units.
  if(spec->keyword == TI_CLASS) {
    std::vector<Member*> decls;
    FOREACH_ASTLIST_NC(Member, spec->members->list, iter) {
      if(iter.data()->isMR_decl()) {
        MR_decl* iter_decl = iter.data()->asMR_decl();
        if(iter_decl->d->spec->isTS_classSpec()) {
          TS_classSpec* unitSpec = iter_decl->d->spec->asTS_classSpec();
          if(unitSpec->keyword == TI_UNIT) {
            for(unsigned int i = 0; i < decls.size(); i++) {
              int col = sourceLocManager->getCol(unitSpec->beginBracket);
              int line = sourceLocManager->getLine(unitSpec->beginBracket);
              std::string member = getMember(decls[i]) + " ";
              PobcppPatch* insert1 = new PobcppPatch(Insert, member, col+1);
              (patchess[line]).push_back(insert1);
            }
          }
        }
        else {
          Member* clone_decl = iter.data();
          decls.push_back(clone_decl);
        }
      }
      else {
        Member* clone_decl = iter.data();
        decls.push_back(clone_decl);
      }
    }
  }
	else if(spec->keyword == TI_UNIT) { // unit?
		sclass.push(spec); // Taking note of each unit/function list
    int inheritance = !(spec->bases->count());
    int iline = sourceLocManager->getLine(spec->beginBracket);
    int col = sourceLocManager->getCol(spec->beginBracket);
    if(inheritance)
      appendPobunitBaseClass(inheritance, iline, col);
    else
      appendPobunitBaseClass(inheritance, iline, col);
	}
  return true;
}

bool PrePObCppVisitor::visitFunction(Function* func) {
  if(((func->dflags) & DF_PARALLEL) != 0) {
    // TODO
  }
  IDeclarator* idecl = func->nameAndParams->decl;
  if(idecl->isD_func()) {
    removeCommunicatorDecl(idecl->asD_func(), idecl->asD_func()->params->count(), true);
  }

  return true;
}

bool PrePObCppVisitor::visitIDeclarator(IDeclarator* idecl) {
  if (idecl->isD_func()) {
		D_func* dfunc = idecl->asD_func();
		sfuncs.push(dfunc);
    removeCommunicatorDecl(dfunc, dfunc->params->count(), false);
		if((!sclass.empty()) && (dfunc->comm != NULL))
			classDecl[sclass.top()].push_back(dfunc);
	}
  return true;
}

void PrePObCppVisitor::postvisitIDeclarator(IDeclarator* idecl) {
	if(idecl->isD_func())
			sfuncs.pop();
}

//FIXME create visitE_funcall() function;
bool PrePObCppVisitor::visitExpression(Expression* exp) {
  using std::string;
	if(exp->kind() == Expression::E_FUNCALL) {
		E_funCall* e_funCall = dynamic_cast<E_funCall*>(exp);
		if(e_funCall != NULL) {
			if(e_funCall->commCall != NULL) { // func(...) [[comm]]
				PobcppCommunicatorCall* commCall = e_funCall->commCall;
				int beginCol = sourceLocManager->getCol(commCall->b1SquareBracket);
				int beginLine = sourceLocManager->getLine(commCall->b1SquareBracket);
				int endCol = sourceLocManager->getCol(commCall->e1SquareBracket);
				int endLine = sourceLocManager->getLine(commCall->e1SquareBracket);
				PobcppPatch* erase1 = new PobcppPatch(Erase, string(), beginCol+2, 3); //FIXME We should remove ( too, but here we just assume his position
				(patchess[beginLine]).push_back(erase1);
				if(e_funCall->args->count()) {
					PobcppPatch* insert = new PobcppPatch(Insert, string(","), beginCol+2); 
					(patchess[beginLine]).push_back(insert);
					std::cerr << "Inserint ',' - count()" << e_funCall->args->count() << std::endl;
				}
				PobcppPatch* erase2 = new PobcppPatch(Erase, string(), endCol+2, 2);
				(patchess[endLine]).push_back(erase2);
				PobcppPatch* insert = new PobcppPatch(Insert, string(")"), endCol+2); 
				(patchess[endLine]).push_back(insert);
				std::cerr << "Found a call to commCall: " << beginLine << "," << beginCol << std::endl;
			}
			else { // func(...)
				if(!sclass.empty()) {
					std::vector<IDeclarator*> funcs = classDecl[sclass.top()];
					PQ_name* funcallName = NULL;
					if(e_funCall->func->isE_variable()) {
						E_variable* evar = e_funCall->func->asE_variable();
						if(evar->name->isPQ_name()) {
							std::cerr << "E_funcall called: " << evar->name->asPQ_name()->name << std::endl;
							funcallName = evar->name->asPQ_name();
						}
					}
					if(sclass.top()->name->isPQ_name()) {
						std::cerr << "Functions from " << sclass.top()->name->asPQ_name()->name << std::endl;
					}
					//FIXME need to check funcallName nullness
					for(unsigned int i = 0; i < funcs.size(); i++) {
						D_func* dfunc = funcs[i]->asD_func();;
						std::cerr << "Checking D_func: " << dfunc->base->asD_name()->name->asPQ_name()->name << std::endl;
						PQ_name* defFuncName = dfunc->base->asD_name()->name->asPQ_name();
						if(string(defFuncName->name) == string(funcallName->name)) {
							std::cerr << "Equal names" << std::endl;
							//FIXME check args
							//Create patch
							if(!sfuncs.empty()) {
								D_func* currentFunc = sfuncs.top();
								if(currentFunc->comm != 0) {
									std::cerr << "Miracle" << std::endl;
									PQ_name* curFuncName = currentFunc->base->asD_name()->name->asPQ_name();
									int col = sourceLocManager->getCol(exp->endloc);
									int line = sourceLocManager->getLine(exp->endloc);
									PobcppPatch* insert = new PobcppPatch(Insert, string(curFuncName->name), col+1);
									(patchess[line]).push_back(insert);
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	else if((exp->kind() == Expression::E_RANKSOF)) {
		E_ranksof* e_ranksof = dynamic_cast<E_ranksof*>(exp);
		int beginParentCol = sourceLocManager->getCol(e_ranksof->beginParenthesis);
		int beginParentLine = sourceLocManager->getLine(e_ranksof->beginParenthesis);
		int endParentCol = sourceLocManager->getCol(e_ranksof->endParenthesis);
		int endParentLine = sourceLocManager->getLine(e_ranksof->endParenthesis);
		int commaCol = sourceLocManager->getCol(e_ranksof->comma);
		int commaLine = sourceLocManager->getLine(e_ranksof->comma);

		PobcppPatch* erase1 = new PobcppPatch(Erase, string(), beginParentCol+1, 1);
		(patchess[beginParentLine]).push_back(erase1);
		PobcppPatch* insert1 = new PobcppPatch(Insert, string("_<"), beginParentCol+1);
		(patchess[beginParentLine]).push_back(insert1);
		PobcppPatch* erase2 = new PobcppPatch(Erase, string(), endParentCol+1, 1);
		(patchess[endParentLine]).push_back(erase2);
		if(!e_ranksof->singleUnit || !e_ranksof->implicit) {
			PobcppPatch* erase2 = new PobcppPatch(Erase, string(), commaCol+1, 1);
			(patchess[commaLine]).push_back(erase2);
		} else {
			
		}
		
		if(e_ranksof->implicit) {	
			if(!e_ranksof->singleUnit) {
				PobcppPatch* insert2 = new PobcppPatch(Insert, string(">(comm, "), commaCol+1); //FIXME comm must be the communicator identifier of the function
				(patchess[commaLine]).push_back(insert2);
			} else {
				PobcppPatch* insert2 = new PobcppPatch(Insert, string(">(comm"), endParentCol+1); //FIXME comm must be the communicator identifier of the function
				(patchess[endParentLine]).push_back(insert2);
				
			}
			PobcppPatch* insert3 = new PobcppPatch(Insert, string(", Unit_Type(this))"), endParentCol+1);
			(patchess[endParentLine]).push_back(insert3);
		}
		else {
			PobcppPatch* insert2 = new PobcppPatch(Insert, string(">("), commaCol+1);
			(patchess[commaLine]).push_back(insert2);
			PobcppPatch* insert3 = new PobcppPatch(Insert, string(", Unit_Type(this))"), endParentCol+1);
			(patchess[endParentLine]).push_back(insert3);
		}
	}
		return true;
}

void PrePObCppVisitor::appendPobunitBaseClass(bool firstBaseClass, int line, std::string::size_type found) {
  if(firstBaseClass) {
    PobcppPatch* insert = new PobcppPatch(Insert, std::string(" : virtual public Pobcpp::Unit "), found);
    (patchess[line]).push_back(insert);
  }
  else {
    PobcppPatch* insert = new PobcppPatch(Insert, std::string(" ,virtual public Pobcpp::Unit "), found);
    (patchess[line]).push_back(insert);
  }
}

void PrePObCppVisitor::removeCommunicatorDecl(D_func* func, int params, bool body) {
  #ifdef POBCPPDEBUG
  std::cerr << "removeCommunicator() call" << std::endl;
  #endif
  if(func->inspected)
    return;
  if(func->comm == 0)
    return;
  if(!func->comm->defined)
    return;
  using std::string;
  string typeName = func->comm->typeId->spec->asTS_name()->name->asPQ_name()->name;
  int endParenthesisCol = sourceLocManager->getCol(func->endParenthesis);
  int endParenthesisLine = sourceLocManager->getLine(func->endParenthesis);
  PobcppCommunicatorSpec* spec = (func->comm);
  int iline = sourceLocManager->getLine(spec->endSquareBracket);
  int col = sourceLocManager->getCol(spec->endSquareBracket);
  int colbeg = sourceLocManager->getCol(spec->beginSquareBracket);
  PobcppPatch* erase = new PobcppPatch(Erase, string(), col+1, 1);
  (patchess[iline]).push_back(erase);
  if(!body) {
    PobcppPatch* insert = new PobcppPatch(Insert, string(" =") + typeName + string("()"), col+1);
    (patchess[iline]).push_back(insert);
  }
  PobcppPatch* insert = new PobcppPatch(Insert, string(")"), col+1);
  (patchess[iline]).push_back(insert);

  PobcppPatch* erase2 = new PobcppPatch(Erase, string(), colbeg+1, 1);
  (patchess[iline]).push_back(erase2);

  PobcppPatch* erase3 = new PobcppPatch(Erase, string(), endParenthesisCol+1, 1);
  (patchess[endParenthesisLine]).push_back(erase3);
  if(params) {
    PobcppPatch* insert3 = new PobcppPatch(Insert, string(","), endParenthesisCol+2);
    (patchess[endParenthesisLine]).push_back(insert3);
  }
  func->inspected = true;
  #ifdef POBCPPDEBUG
  std::cerr << "removeCommunicator() end" << std::endl;
  #endif
  return;
}



int main(int argc, char **argv) {
  Patcher p;
  PrePObCppVisitor visitor(p);
  PigletParser parser(true);
	for (int i = 1 ;i< argc;i+=2) {
    visitor.setFile(argv[i+1]);
    TranslationUnit *unit = parser.getASTNoExc(argv[i]);
    unit->traverse(visitor);
  }
  return 0;
}
