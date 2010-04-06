#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include "unit_type.h"
#include <typeinfo>

namespace Pobcpp {

class Environment;

template<typename Derived>
class Communicator {
public:

	template<typename Type, typename Data>
	void send(Data data, const int tag) {
		Type* unit;
		Unit_Type unit_type(typeid(unit).name());	
		static_cast<Derived*>(this)->sync_send(unit_type, data, tag);
	}

	template<typename Type, typename Data>
	Data receive(const int tag) {
		Type* unit;
		Unit_Type unit_type(typeid(unit).name());	
		return static_cast<Derived*>(this)->sync_receive(unit_type, tag, Data());
	}

	void set_environment(Environment* _env);

protected:
	Communicator();
	virtual ~Communicator();

	Environment* env;
};
	
template<typename Derived>
Communicator<Derived>::Communicator() : env(0) { }

template<typename Derived>
void Communicator<Derived>::set_environment(Environment* _env) { 
	env = _env;
	static_cast<Derived*>(this)->env_setted();
}

template<typename Derived>
Communicator<Derived>::~Communicator() {
//	delete env;
}

}

#endif

