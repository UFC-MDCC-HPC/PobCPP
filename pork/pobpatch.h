#ifndef POBCPP_PATCH
#define POBCPP_PATCH
enum PatchKind {
	Erase = 0,
	Insert,
};

struct PobcppPatch {
  PobcppPatch(PatchKind _kind, std::string _str = std::string(), int _col = 1, int _erase = 0) : kind(_kind), str(_str) , col(_col), erase(_erase) { 
/*		if(PatchKind == Insert) {
			if(str.size() == 0)
				std::cerr << "Insert invalido" << std::endl;
		}*/
	}
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

#endif
