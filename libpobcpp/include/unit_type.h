#ifndef __UNIT_TYPE_H__
#define __UNIT_TYPE_H__

#include <string>
#include <typeinfo>

#include <boost/serialization/serialization.hpp>

namespace Pobcpp {

class Unit_Type {
public:
	Unit_Type();
	template<typename Unit>
	Unit_Type(Unit* _unit);
	~Unit_Type();

	bool operator==(const Unit_Type& _unit_type) const;
	bool operator<(const Unit_Type& _unit_type) const;
	//TODO
	// define operator=

	friend std::ostream& operator<<(std::ostream& ostream, const Unit_Type& _unit_type);

private:
	std::string unit_type;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive&, const unsigned int);		
};

template<typename Unit>
Unit_Type::Unit_Type(Unit* _unit) {
	unit_type = typeid(_unit).name();
}

template<class Archive> void Unit_Type::serialize(Archive& ar, const unsigned int /* file_version */) {
	ar & unit_type;

}

class Pob_Type_Array {
public:
	Pob_Type_Array(unsigned int _size) : size(_size), types(new Unit_Type[_size])  { }

	~Pob_Type_Array() {
		delete[] types;		
	}

	template<typename Type>
	void add_type(unsigned int _i) {
		Unit_Type type(Type*);
		types[_i] = type;			
	}

	template<typename Type>
	bool compare_type() {
		Unit_Type type(Type*);
		for(unsigned int i = 0; i < size; i++) {
			if(types[i] == type)
				return true;
		}
		return false;
	}

private:
unsigned int size;
Unit_Type* types;

};

}

#endif


