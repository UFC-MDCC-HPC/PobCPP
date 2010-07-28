#include "pobcpp.h"
#include "piglet.h"

#include <string>
#include <sstream>
#include <map>
#include <algorithm>

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
		std::cout << "enumCount" << enumCount << std::endl;
		col--; // columns start by 1 and string's indexes by 0
		bool inheritance = false;
		while(1) {
			sline = getLine(spec->loc, iline);
			// ':' case
			find:
			found = sline.find(':', col);
			if(found != string::npos) {
				enumCount--;
				if(enumCount > -1) {
					col = found+1;
					std::cout << "GOTO" << std::endl;
					goto find;
				}
				PobcppPatch* insert = new PobcppPatch(Insert, std::string(" public Pobcpp::Unit, "), found+2);
				(patchess[iline]).push_back(insert);
				inheritance = true;
				//break;
			}

			// '{' case

			found = sline.find('{', col);
			if(found != string::npos) {
				if(!inheritance) {
					PobcppPatch* insert = new PobcppPatch(Insert, std::string(" : public Pobcpp::Unit "), found+1);
					(patchess[iline]).push_back(insert);
				}
				if(spec->enumerators->count())
					createEnumerator(spec, iline, found);
				break;
			}
			col = 0;
			++iline;
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
		//spec->members->list.append(createEnumerator(pobcppEnumSpec->name));
		//spec->members->list.append(createEnumerator(pobcppEnumSpec->size));
		std::string name = string(" public: const unsigned int ") + string(pobcppEnumSpec->name);
		std::string size = string("; const unsigned int ") + string(pobcppEnumSpec->size) + string("; private:");
		PobcppPatch* insert = new PobcppPatch(Insert, name+size, found+2);
		(patchess[iline]).push_back(insert);
	}

}

void Pobcpp::appendPobTypeArrayFunc() {
	//TODO
    // Append this definition:
    // Pob_Type_Array __get_types() {
    //   Pob_Type_Array pobtypes(units);
    //   pobtypes.add_type<unit A>(0);
		//   pobtypes.add_type<unit B>(1);
		//   ...	
		//   return pobtypes;
    // }

}

int main(int argc, char **argv) {
  PigletParser parser;
  Patcher p;
  Pobcpp visitor(p);
	for (int i = 1 ;i< argc;i+=2) {
		visitor.setFile(argv[i+1]);
    TranslationUnit *unit = parser.getASTNoExc(argv[i]);
    unit->traverse(visitor);
  }
  return 0;
}

