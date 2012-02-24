#ifndef __POBCPP_H__
#define __POBCPP_H__

#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "patcher.h"
#include "expr_visitor.h"
#include "elsa/pobcpp.h"
#include "prepobcpp.h"
#include "pobpatch.h"


class Pobcpp : public ExpressionVisitor {
public:
	Pobcpp(Patcher &patcher);
	~Pobcpp();

  void setFile(const char* _file) { file = _file;	}

	virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	virtual bool visitExpression(Expression* exp);

  std::vector<ClassAndUnit> classes; // PObC++ modification.

private:
  std::string getLine(int line);
	
  void createEnumerator(TS_classSpec *spec);
  void appendPobTypeArrayFunc(TS_classSpec *spec, int line, std::string::size_type found, unsigned int units);
  void appendPobunitBaseClass(bool firstBaseClass, int line, std::string::size_type found);
  unsigned int countUnits(ASTList<Member> *memberList);

	Patcher &patcher;
	std::string file;
  // TODO
  // Clear patchess on object destruction.
	std::map<int, std::vector<PobcppPatch*> > patchess;
};


#endif // __POBCPP_H__
