#ifndef __POBCPP_H__
#define __POBCPP_H__
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "patcher.h"
#include "expr_visitor.h"

enum PatchKind {
	Erase = 0,
	Insert,
};

struct PobcppPatch {
	PobcppPatch(PatchKind _kind, std::string _str, int _col = 1, int _erase = 0) : kind(_kind), str(_str) , col(_col), erase(_erase) { }
	~PobcppPatch();
	PatchKind kind;
	std::string str;
	int col;
	int erase;

};
struct PobcppPatchCmp {
	bool operator()( const PobcppPatch* p1, const PobcppPatch* p2 ) const {
		return p1->col < p2->col;
	}
};

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
	void createEnumerator(TS_classSpec *spec, int line, std::string::size_type found);
	void appendPobTypeArrayFunc();
	void appendPobunitBaseClass();
	bool removeUnitDecl(SourceLoc loc);

	Patcher &patcher;
	std::string file;
	std::map<int, std::string> patches;
	std::map<int, std::vector<PobcppPatch*> > patchess;
};


#endif // __POBCPP_H__
