#ifndef __UNIT_TYPE_H__
#define __UNIT_TYPE_H__

#include <string>
#include <iostream>

#include <boost/serialization/serialization.hpp>

namespace Pobcpp {

class Unit_Type {
public:
	Unit_Type();
	Unit_Type(const char* _unit_type);
	~Unit_Type();

	bool operator==(const Unit_Type& _unit_type) const;
	bool operator<(const Unit_Type& _unit_type) const;

	friend std::ostream& operator<<(std::ostream& ostream, const Unit_Type& _unit_type);

private:
	std::string unit_type;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive&, const unsigned int);		
};
template<class Archive> void Unit_Type::serialize(Archive& ar, const unsigned int /* file_version */) {
	ar & unit_type;

}

}

#endif


