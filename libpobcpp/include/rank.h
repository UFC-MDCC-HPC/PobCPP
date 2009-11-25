#ifndef __RANK_H__
#define __RANK_H__

#include <boost/serialization/serialization.hpp>

namespace Pobcpp {

struct Rank {
public:
	Rank(int _rank = -1);

	operator int(void);
	Rank& operator=(const int _rank);
	Rank& operator=(const Rank& _rank);

	bool operator==(const Rank& _rank) const;
	bool operator==(const int _rank) const;

	void operator++(void);

	friend std::ostream& operator<<(std::ostream& ostream, const Rank& _rank);

	int rank;

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive&, const unsigned int);		
};
template<class Archive> void Rank::serialize(Archive& ar, const unsigned int /* file_version */) {
	ar & rank;
}

}

#endif

