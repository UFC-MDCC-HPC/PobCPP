#include "pobcpp.h"
#include "piglet.h"

#include <string>
#include <sstream>
#include <map>
#include <algorithm>

extern char* itoa(int value); // elsa/pobcpp.cc FIXME

Pobcpp::Pobcpp(Patcher &patcher):patcher(patcher) {  }

Pobcpp::~Pobcpp() {
  using std::string;
  using std::map;
  using std::pair;
  using std::vector;
  map<int, vector<PobcppPatch*> >::iterator iter;
    for(iter = patchess.begin(); iter != patchess.end(); ++iter ) {
      std::sort(iter->second.begin(), iter->second.end(), PobcppPatchCmp());
      vector<PobcppPatch*>::const_iterator viter;
      int iline = iter->first;
      std::string sline  = patcher.getLine(iline, file);
      std::string line = sline;
      unsigned int diff = 0;
      for(viter = iter->second.begin(); viter != iter->second.end(); ++viter) {
        PobcppPatch* patch = *viter;
        if(patch->kind == Insert) {
          sline.insert(diff + patch->col-1, patch->str);
  //					std::cout << "Inserir na coluna " << patch->col << " a string " << patch->str << " com diff: " << diff << std::endl;
  //					std::cout << "Linha com patch: " << sline << std::endl;
          diff += patch->str.length();
        }
        else {
          diff -= patch->erase;
          sline.erase(diff+ patch->col-2, patch->erase);
  //					std::cout << "Remover na coluna " << patch->col << " essa quantidade: " << patch->erase << " com diff: " << diff << std::endl;
  //					std::cout << "Linha com patch: " << sline << std::endl;

        }
      }

      sline += " //";
      patcher.insertBefore(file.c_str(), UnboxedLoc(iter->first,1), sline);
  }
  // FIXME
  patches.clear();
}

std::string Pobcpp::getLine(SourceLoc loc, int line) {
  return patcher.getLine(line, file);
}

bool Pobcpp::visitTypeSpecifier(TypeSpecifier *type) {
  if (type->isTS_classSpec()) {
    return subvisitTS_classSpec(type->asTS_classSpec());
  }
  if(type->isTS_elaborated()) {
    return subvisitTS_elaborated(type->asTS_elaborated());
  }
  return true;
}

bool Pobcpp::subvisitTS_elaborated(TS_elaborated *spec) {
  using std::string;
  if(spec->keyword == TI_UNIT) { // unit?
    removeUnitDecl(spec->loc);
  }
  return true;
}

bool Pobcpp::subvisitTS_classSpec(TS_classSpec *spec) {
  using std::string;
  if(spec->keyword == TI_UNIT) { // unit?
    removeUnitDecl(spec->loc);
    int iline = sourceLocManager->getLine(spec->loc);
    int col = sourceLocManager->getCol(spec->loc);
    string sline;
    string::size_type found;
    // Search for a ':' or a '{' and insert ' : public Pobcpp::Unit '
    int enumCount = spec->enumerators->count();
    col--; // columns start by 1 and string's indexes by 0
    bool inheritance = false;
    while(1) {
      sline = getLine(spec->loc, iline);
      // If we have Enumerators a number of enumCount of ':' must be skiped.
      while(enumCount) {
        found = sline.find(':', col);
        if(found != string::npos) {
          enumCount--;
          if(enumCount >= 0) {
            col = found+1;
            continue;
          }
        }
        else {
          col = found+1;
          found = sline.find(':', col);
          break;
        }
      }
      // ':' case
      if(!inheritance) {
        found = sline.find(':', col);
        if(found != string::npos) {
          appendPobunitBaseClass(false, iline, found+2);
          inheritance = true;
        }
      }
      // '{' case

      found = sline.find('{', col);
      if(found != string::npos) {
        if(!inheritance) {
          appendPobunitBaseClass(true, iline, found+1);
        }
        if(spec->enumerators->count()) {
          //de mucreateEnumerator(spec, iline, found);
        }
        break;
      }
      col = 0;
      ++iline;
    }
  }
  else if(spec->keyword == TI_CLASS) {
    unsigned short units = 0;  // How many units exist inside this class?
    units = countUnits(&(spec->members->list));

    if(!units)
      return true;
    else {
      int iline = sourceLocManager->getLine(spec->endBracket);
      int col = sourceLocManager->getCol(spec->endBracket);
      appendPobTypeArrayFunc(spec, iline, col-2, units);
    }
  }
  return true;
}
 


void Pobcpp::createEnumerator(TS_classSpec* spec, int line, std::string::size_type found) {
  using std::string;
  // unit Name [i:m] { }
  // Insert two statements:
  // const unsigned int i;
  // const unsigned int m;
  int iline = sourceLocManager->getLine(spec->loc);
  int col = sourceLocManager->getCol(spec->loc);
  FAKELIST_FOREACH_NC(PobcppEnumeratorSpec, spec->enumerators, pobcppEnumSpec) {
    string name = string(" public: const unsigned int ") + string(pobcppEnumSpec->name);
    string size = string("; const unsigned int ") + string(pobcppEnumSpec->size) + string("; private:");
    PobcppPatch* insert = new PobcppPatch(Insert, name+size, found+2);
    (patchess[iline]).push_back(insert);
  }
}

void Pobcpp::appendPobTypeArrayFunc(TS_classSpec* spec, int iline, std::string::size_type found, unsigned int units) {
	using std::string;
  //TODO FIXME
  // Append this definition:
  // Pob_Type_Array __get_types() {
  //   Pob_Type_Array pobtypes(units);
  //   pobtypes.add_type<unit A>(0);
  //   pobtypes.add_type<unit B>(1);
  //   ...
  //   return pobtypes;
  // }
  string function = "public: Pob_Type_Array __get_types() { Pob_Type_Array pobtypes(" + string(itoa(units)) + "); ";

  unsigned int j = 0; // Unit order
  for(unsigned int i = 0; i < classes.size(); i++) { // FIXME Better search algorithm.
    if(classes[i].c != spec->name->asPQ_name()->name)
      continue;
    if(classes[i].enumerators == 0) {
      function += "pobtypes.add_type<" + string(classes[i].u) + ">(" + string(itoa(j)) + ");";
    } else {
      function += "pobtypes.add_type<" + string(classes[i].u) + ">(" + string(itoa(j)) + ", " + string(itoa(classes[i].enumerators)) +  ");";
    }
    j++;
  }
  function += "return pobtypes; } private:";
  PobcppPatch* insert = new PobcppPatch(Insert, function, found+2);
  (patchess[iline]).push_back(insert);
}

void Pobcpp::appendPobunitBaseClass(bool firstBaseClass, int line, std::string::size_type found) {
  // FIXME
  // maybe here we need to insert "virtual" public Pobcpp::Unit
  if(firstBaseClass) {
    PobcppPatch* insert = new PobcppPatch(Insert, std::string(": public Pobcpp::Unit "), found);
    (patchess[line]).push_back(insert);
  }
  else {
    PobcppPatch* insert = new PobcppPatch(Insert, std::string(" public Pobcpp::Unit, "), found);
    (patchess[line]).push_back(insert);
  }
}

bool Pobcpp::removeUnitDecl(SourceLoc loc) {
  using std::string;
  int iline = sourceLocManager->getLine(loc);
  int col = sourceLocManager->getCol(loc);
  string sline;
  string::size_type found;

  sline = getLine(loc, iline);

  found = sline.find("unit", col-1);

  if(found != string::npos ) {
    PobcppPatch* erase = new PobcppPatch(Erase, string(), col+5, 4);
    PobcppPatch* insert = new PobcppPatch(Insert, std::string("class"), col);
    (patchess[iline]).push_back(erase);
    (patchess[iline]).push_back(insert);
    return true;
  }
  else {
    return false;
  }
}

unsigned int Pobcpp::countUnits(ASTList<Member> *memberList) {
  unsigned int units = 0;
  FOREACH_ASTLIST_NC(Member, *memberList, iter) {
    if(iter.data()->isMR_decl()) {
      MR_decl* iter_decl = iter.data()->asMR_decl();
      if(iter_decl->d->spec->isTS_classSpec()) {
        if(iter_decl->d->spec->asTS_classSpec()->keyword == TI_UNIT) {
          units++;
        }
      }
    }
  }
  return units;
}

int main(int argc, char **argv) {
  PigletParser parser;
  Patcher p;
  Pobcpp visitor(p);
	for (int i = 1 ;i< argc;i+=2) {
		visitor.setFile(argv[i+1]);
    TranslationUnit *unit = parser.getASTNoExc(argv[i]);
    visitor.classes = parser.classes;
    unit->traverse(visitor);
  }
  return 0;
}

