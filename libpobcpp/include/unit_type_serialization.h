#ifndef __UNIT_TYPE_SERIALIZATION__
#define __UNIT_TYPE_SERIALIZATION__

#include "unit_type.h"
#include <boost/serialization/serialization.hpp>
namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive & ar, Pobcpp::Unit_Type & g, const unsigned int version) {
			ar & g.unit_type;
			ar & g.enumerators;
			ar & g.enums;
		}

	} // namespace serialization
} // namespace boost

struct Unit_Type_Pack {
	Unit_Type_Pack(Pobcpp::Unit_Type unit_type,
								 unsigned int rank) :
	               unit_type(unit_type),
								 rank(rank) { }
	Unit_Type_Pack() { }
	Pobcpp::Unit_Type unit_type;
	unsigned int rank;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & unit_type;
		ar & rank;
	}

};

#endif

