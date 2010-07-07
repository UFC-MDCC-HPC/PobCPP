#include <sstream>
#include <string>
#include <fstream>
#include "patcher.h"
#include "piglet.h"
#include "expr_visitor.h"

class Pobcpp : public ExpressionVisitor {
public:
  Pobcpp(Patcher &patcher):patcher(patcher) {  }
	virtual bool visitTypeSpecifier(TypeSpecifier *type);
  virtual bool subvisitTS_classSpec(TS_classSpec *spec); 
private:
	void createEnumerator();
	void appendPobTypeArrayFunc();
	void appendPobunitBaseClass();
  Patcher &patcher;
};


bool Pobcpp::visitTypeSpecifier(TypeSpecifier *type) {
	if (type->isTS_classSpec()) {
		return subvisitTS_classSpec(type->asTS_classSpec());
	}
	return true;
}

bool Pobcpp::subvisitTS_classSpec(TS_classSpec *spec) {
	using std::string;
  if(spec->keyword == TI_UNIT) { // unit?
		CPPSourceLoc csl(spec->loc);
		char const *file = sourceLocManager->getFile(spec->loc);
		int iline = sourceLocManager->getLine(spec->loc);
		string sline;
		string::size_type found;
		// Search for a ':' or a '{' and insert ' : public Pobcpp::Unit '
		while(1) {
			sline = patcher.getLine(iline, file);
			std::cout << "Getting line: " << iline << std::endl;
			std::cout << "Linha: " << sline << std::endl;
			// ':' case
			found = sline.find_first_of(':');

			if(found != string::npos ) {
				sline.insert(found+1, std::string(" public Pobcpp::Unit, "));
				sline += " //";

				break;
			}
			// '{' case
			found = sline.find_first_of('{');
			if(found != string::npos ) {
				sline.insert(found-1, std::string(" : public Pobcpp::Unit "));
				sline += " //";
				break;
			}
			++iline;
		}

		csl.overrideLoc(sourceLocManager->encodeLineCol(file, iline, 1));
		patcher.insertBefore(csl, sline, 0);

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

