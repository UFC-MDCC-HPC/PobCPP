#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include "patcher.h"
#include "piglet.h"
#include "expr_visitor.h"

class Pobcpp : public ExpressionVisitor {
public:
  Pobcpp(Patcher &patcher):patcher(patcher) {  }
	virtual bool visitTypeSpecifier(TypeSpecifier *type);
  virtual bool subvisitTS_classSpec(TS_classSpec *spec); 
private:
	std::string getLine(SourceLoc loc, int line);
	void createEnumerator();
	void appendPobTypeArrayFunc();
	void appendPobunitBaseClass();
	bool removeUnitDecl(SourceLoc loc);
  Patcher &patcher;
	std::map<int, std::string> patches;
};

std::string Pobcpp::getLine(SourceLoc loc, int line) {
	char const *file = sourceLocManager->getFile(loc);
//	std::cout << "Getting line: " << line << std::endl;
	if(patches.count(line)) {
		return patches[line];
	}
	return patcher.getLine(line, file);
}

bool Pobcpp::visitTypeSpecifier(TypeSpecifier *type) {
	if (type->isTS_classSpec()) {
		return subvisitTS_classSpec(type->asTS_classSpec());
	}
	return true;
}

bool Pobcpp::removeUnitDecl(SourceLoc loc) {
	using std::string;
	int iline = sourceLocManager->getLine(loc);
	string sline;
	string::size_type found;

	sline = getLine(loc, iline);

	found = sline.find_first_of("unit");

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

bool Pobcpp::subvisitTS_classSpec(TS_classSpec *spec) {
	using std::string;
	using std::map;

  if(spec->keyword == TI_UNIT) { // unit?
		removeUnitDecl(spec->loc);

		CPPSourceLoc csl(spec->loc);
		int iline = sourceLocManager->getLine(spec->loc);

		string sline;
		string::size_type found;
		// Search for a ':' or a '{' and insert ' : public Pobcpp::Unit '
		while(1) {
			sline = getLine(spec->loc, iline);
//			std::cout << "Analisando linha: " << sline << std::endl;
			// ':' case
			found = sline.find_first_of(':');

			if(found != string::npos ) {
				sline.insert(found+1, std::string(" public Pobcpp::Unit, "));
				sline += " //";
				patches[iline] = sline;
//				std::cout << "Adding line: " << iline << " at" << sline << std::endl;
				break;
			}
			// '{' case
			found = sline.find_first_of('{');
			if(found != string::npos ) {
				sline.insert(found-1, std::string(" : public Pobcpp::Unit "));
				sline += " //";
				patches[iline] = sline;
//				std::cout << "Adding line: " << iline << " at" << sline << std::endl;
				break;
			}
			++iline;
		}
		// Generating patches
		map<int, string>::iterator iter;
		for(iter = patches.begin(); iter != patches.end(); ++iter ) {
//			std::cout << "Adding line: " << iter->second << " at" << iter->first << std::endl;
			char const *file = sourceLocManager->getFile(spec->loc);
			csl.overrideLoc(sourceLocManager->encodeLineCol(file, iter->first, 1));
			patcher.insertBefore(csl, iter->second, 0);
		}
		patches.clear();
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
  for (int i = 1 ;i< argc;i++) {
    TranslationUnit *unit = parser.getASTNoExc(argv[i]);
    unit->traverse(visitor);
  }
  return 0;
}

