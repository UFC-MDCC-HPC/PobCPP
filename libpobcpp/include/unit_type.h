#ifndef __UNIT_TYPE_H__
#define __UNIT_TYPE_H__

#include <string>
#include <typeinfo>
#include <boost/serialization/serialization.hpp>
#include <map>

namespace Pobcpp {

class Unit_Type {
public:
	Unit_Type();
	template<typename Unit>
	Unit_Type(Unit* _unit, unsigned int _enumerators = 0);
	~Unit_Type();

	void set_enums(std::pair<unsigned int, unsigned int> _enums) {
		enumerators = 1;
		enums = _enums;
	}

	std::pair<unsigned int, unsigned int> get_enums() const {
		return enums;
	}

	bool has_enumerators(void) const {
		return enumerators;
	}

	void set_enumerators(unsigned int _enumerators) {
		enumerators = _enumerators;
	}

	bool operator==(const Unit_Type& _unit_type) const;
	bool operator<(const Unit_Type& _unit_type) const;
	//TODO
	// define operator=

	friend std::ostream& operator<<(std::ostream& ostream, const Unit_Type& _unit_type);

private:
	std::string unit_type;
	unsigned int enumerators;
	std::pair<unsigned int, unsigned int> enums;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive&, const unsigned int);		
};

template<typename Unit>
Unit_Type::Unit_Type(Unit* _unit, unsigned int _enumerators) {
	unit_type = typeid(_unit).name();
	enumerators = _enumerators;
}

template<class Archive> void Unit_Type::serialize(Archive& ar, const unsigned int /* file_version */) {
	ar & unit_type;
	ar & enumerators;
	ar & enums;
}

class Pob_Type_Array {
public:
	Pob_Type_Array(const unsigned int _size) : sizearray(_size), types(new Unit_Type[_size])  { }

	~Pob_Type_Array() {
		//delete[] types;		 FIXME
	}

	const unsigned int size() { return sizearray; } const

	Unit_Type get_type(unsigned int _i) const {
		if(_i < sizearray) {
			return types[_i];
		}
		else return Unit_Type();
	}

	template<typename Type>
	void add_type(unsigned int _i, unsigned int enumerators = 0) {
		Type* t;
		Unit_Type type(t, enumerators);
		types[_i] = type;			
	}
	
	template<typename Type>
	bool compare_type() {
		Type* t;
		Unit_Type type(t);
		for(unsigned int i = 0; i < sizearray; i++) {
			if(types[i] == type)
				return true;
		}
		return false;
	}

private:
const unsigned int sizearray;
Unit_Type* types;

};

}

#endif


