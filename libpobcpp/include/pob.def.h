#include "parallel_object.h"
#include "unit.h"
#include "master_unit.h"
#include "communication.h"
#include "unit_type.h"
#include <typeinfo>

/* Units */

#define unit_master					\
	__Master__

#define unit(name)					\
	__Unit_##name##__

#define unit_generic(name)				\
	__Generic_Unit_##name##__


/* Unit definition */

#define unit_master_def					\
	class __Master__ : public Pobcpp::Master_Unit

#define unit_def(name)					\
	class __Unit_##name##__ : public Pobcpp::Unit

#define unit_generic_def(name,i)			\
	class __Generic_Unit_##name##__  : public Pobcpp::Unit

/* Unit Call */

#define unit_master_call				\
	__Master__

#define unit_call(name)					\
	__Unit_##name##__

#define unit_generic_call(name)				\
	__Generic_Unit_##name##__ 

/* Unit constructor */

#define unit_master_cons(...)				\
	__Master__ (__VA_ARGS__)

#define unit_cons(name,...)				\
	__Unit_##name##__ (__VA_ARGS__)

#define unit_generic_cons(name,...)			\
	__Generic_Unit_##name##__ (__VA_ARGS__)

#define parallel 

#define parallel_class(name)				\
	class name : public Pobcpp::Parallel_Object	

