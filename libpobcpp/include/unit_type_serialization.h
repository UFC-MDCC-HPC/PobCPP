#include "unit_type.h"
#include <boost/serialization/serialization.hpp>
namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive & ar, Pobcpp::Unit_Type & g, const unsigned int version) {
			ar & unit_type;
			ar & enumerators;
			ar & enums;
		}

	} // namespace serialization
} // namespace boost

