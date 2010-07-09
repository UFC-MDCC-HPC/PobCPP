#include "pobcpp.h"
#include "piglet.h"

#include <string>
#include <map>

Pobcpp::Pobcpp(Patcher &patcher):patcher(patcher) {  }

Pobcpp::~Pobcpp() {
	using std::string;
	using std::map;
	using std::pair;
	// Generating patches
	map<int, string >::iterator iter;
	for(iter = patches.begin(); iter != patches.end(); ++iter ) {
			//char const *file = sourceLocManager->getFile(spec->loc);
		//CPPSourceLoc csl;
		//csl.overrideLoc(sourceLocManager->encodeLineCol(file, iter->first, 1));
		// FIXME
		//patcher.insertBefore(csl, iter->second, 0);
		patcher.insertBefore(file.c_str(), UnboxedLoc(iter->first,1), iter->second);
	}
	patches.clear();
}

std::string Pobcpp::getLine(SourceLoc loc, int line) {
	//char const *file = sourceLocManager->getFile(loc);
	//	std::cout << "Getting line: " << line << std::endl;
	if(patches.count(line)) {
		return patches[line];
	}
	return patcher.getLine(line, file);
}

bool Pobcpp::visitTypeSpecifier(TypeSpecifier *type) {
	CPPSourceLoc csl(type->loc);
//	if (!csl.hasExactPosition())
//		return true;
//	if (csl.macroExpansion)
//		return true;

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
//	int col = sourceLocManager->getCol(loc);
	string sline;
	string::size_type found;

	sline = getLine(loc, iline);
//	std::cout << sline << std::endl;

	found = sline.find("unit");

	if(found != string::npos ) {
		sline.erase(found, 5);
		sline.insert(found, std::string("class "));
		sline += " //";
		patches[iline] = sline;
		return true;
	}
	else
		return false;
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
	using std::map;
  if(spec->keyword == TI_UNIT) { // unit?
		removeUnitDecl(spec->loc);

		int iline = sourceLocManager->getLine(spec->loc);
		int col = sourceLocManager->getCol(spec->loc);
		string sline;
		string::size_type found;
		// Search for a ':' or a '{' and insert ' : public Pobcpp::Unit '
		while(1) {
			sline = getLine(spec->loc, iline);
		// ':' case
			found = sline.find(':');

			if(found != string::npos) {
				sline.insert(found+1, string(" public Pobcpp::Unit, "));
				sline += " //";
				patches[iline] = sline; //FIXME
//				std::cout << sline << std::endl;
				break;
			}
			// '{' case
			found = sline.find('{');
			if(found != string::npos) {
				sline.insert(found-1, std::string(" : public Pobcpp::Unit "));
				sline += " //";
//				std::cout << sline << std::endl;
				patches[iline] = sline;
				break;
			}
			++iline;
		}
	}
	return true;
}
 


void Pobcpp::createEnumerator() {
	//TODO
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

