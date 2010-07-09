#ifndef __POBCPP_H__
#define __POBCPP_H__
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include "patcher.h"
#include "expr_visitor.h"

class Pobcpp : public ExpressionVisitor {
public:
	Pobcpp(Patcher &patcher);
	~Pobcpp();

	void setFile(const char* _file) {
		file = _file;
	}

	virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	virtual bool subvisitTS_elaborated(TS_elaborated *spec);

private:
	std::string getLine(SourceLoc loc, int line);
	void createEnumerator();
	void appendPobTypeArrayFunc();
	void appendPobunitBaseClass();
	bool removeUnitDecl(SourceLoc loc);

	Patcher &patcher;
	std::string file;
	std::map<int, std::string> patches;
};


#endif // __POBCPP_H__
