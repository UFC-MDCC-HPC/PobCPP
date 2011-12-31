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
