#include "rank.h"

namespace Pobcpp {

Rank::Rank(int _rank) : rank(_rank) { }

Rank::operator int(void) {
	return rank;
}

Rank& Rank::operator=(const int _rank) {
	rank = _rank;
	return *this;
}

Rank& Rank::operator=(const Rank& _rank) {
	if(this != &_rank) {
		rank = _rank.rank;
	}
	return *this;
}

bool Rank::operator==(const Rank& _rank) const {
	if(_rank.rank == rank)
		return true;
	else
		return false;
}
bool Rank::operator==(const int _rank) const {
	if(_rank == rank)
		return true;
	else
		return false;
}

void Rank::operator++(void) {
	rank++;
}

std::ostream& operator<<(std::ostream& ostream, const Rank& _rank) {
	ostream << _rank.rank;
	return ostream;
}

}


