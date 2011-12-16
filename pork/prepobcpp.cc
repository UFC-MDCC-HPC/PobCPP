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

PrePObCppVisitor::PrePObCppVisitor(Patcher &patcher) : patcher(patcher) { } 

bool PrePObCppVisitor::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  return true;
}
bool PrePObCppVisitor::subvisitTS_classSpec(TS_classSpec *spec) {
		// check if attributes or methods are declared.
		// Include them on inner units.
  if(spec->keyword == TI_CLASS) {
    std::vector<MR_decl*> MR_decls;
    unsigned short units = 0;  // How many units exist inside this class?
    FOREACH_ASTLIST_NC(Member, spec->members->list, iter) {
      if(iter.data()->isMR_decl()) {
        MR_decl* iter_decl = iter.data()->asMR_decl();
        if(iter_decl->d->spec->isTS_classSpec()) {
          if(iter_decl->d->spec->asTS_classSpec()->keyword == TI_UNIT) {
           	for(unsigned int i = 0; i < MR_decls.size(); i++) {
							std::cerr << "adding 1 to members" << std::endl;
//              iter_decl->d->spec->asTS_classSpec()->members->list.append(MR_decls[i]);
            }
          }
        }
        else {
          MR_decl* clone_decl = iter.data()->asMR_decl();
          MR_decls.push_back(clone_decl);
        }
      }
    }
  }
  return true;
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
