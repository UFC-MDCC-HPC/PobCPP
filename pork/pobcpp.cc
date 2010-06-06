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
  void ensureInclude (char const *file);
	void createEnumerator();
	void appendPobTypeArrayFunc();
  Patcher &patcher;
};


bool Pobcpp::visitTypeSpecifier(TypeSpecifier *type) {
	if (type->isTS_classSpec()) {
		return subvisitTS_classSpec(type->asTS_classSpec());
	}
	return true;
}

bool Pobcpp::subvisitTS_classSpec(TS_classSpec *spec) {
  if(spec->keyword == TI_UNIT) { // unit?
		char const *file = sourceLocManager->getFile(spec->loc);
		ensureInclude(file);
	}
	return true;
}
 
void Pobcpp::ensureInclude (char const *file) {
	std::ifstream f(file);
	UnboxedLoc loc(1, 1);
	patcher.insertBefore(file, loc, "#include \"pobcpp.h\"\n");
	f.close();
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

