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

enum PatchKind {
	Erase = 0,
	Insert,
};

struct PobcppPatch {
  PobcppPatch(PatchKind _kind, std::string _str = std::string(), int _col = 1, int _erase = 0) : kind(_kind), str(_str) , col(_col), erase(_erase) { }
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

  void setFile(const char* _file) { file = _file;	}

	virtual bool visitTypeSpecifier(TypeSpecifier *type);
	virtual bool subvisitTS_classSpec(TS_classSpec *spec);
	virtual bool subvisitTS_elaborated(TS_elaborated *spec);
  virtual bool visitMember(Member *member);
  virtual bool visitFunction(Function* func);

  std::vector<ClassAndUnit> classes; // PObC++ modification.

private:
	std::string getLine(SourceLoc loc, int line);
  /**
   * Modify lines to exclude enumerators declarations.
   * @param enumCount Quantity of enumerators to be excluded.
   * @param loc Initial localization.
   */
  void removeEnumeratorDecls(TS_classSpec *spec);

  void removeCommunicatorDecl(Function* func);

  /**
   * Modify line to include enumerator information.
   * @param spec Current unit.
   * @param line Line with first '{'
   * @param found Column to insert
   */
  void createEnumerator(TS_classSpec *spec);
  /**
   * Modify line to include the reflective function '__get_types()'.
   * @param spec Current unit
   * @param line Line
   * @param found Column to insert
   * @param units Number of units
   */
  void appendPobTypeArrayFunc(TS_classSpec *spec, int line, std::string::size_type found, unsigned int units);
  /**
   * Modify line to include 'Pobcpp::Unit' as base class.
   * @param bool Is there a base class already?
   * @param line Line
   * @param found Column to insert
   */
  void appendPobunitBaseClass(bool firstBaseClass, int line, std::string::size_type found);
  /**
   * Modify line to replace 'unit' for 'class'
   * @param loc (Line+Column) from ELSA pointing to a 'unit' keyword
   */
	bool removeUnitDecl(SourceLoc loc);
  /**
   * Helper function to count how many units a parallel class has.
   * @param memberList ELSA's structure
   */
  unsigned int countUnits(ASTList<Member> *memberList);

	Patcher &patcher;
	std::string file;
	std::map<int, std::string> patches;
  // TODO
  // Clear patchess on object destruction.
	std::map<int, std::vector<PobcppPatch*> > patchess;
};


#endif // __POBCPP_H__
