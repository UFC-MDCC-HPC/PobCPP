SHELL=/bin/sh
BENCHMARK=is
BENCHMARKU=IS

include ../config/make.def

include ../sys/make.common

libpobcpp=/home/eduardo/projects/mestrado/pobcpp/libpobcpp/include

OBJS = is.o ${COMMON}/c_print_results.o ${COMMON}/c_timers.o


${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${CMPI_LIB}

.c.o:
	${CCOMPILE} $<

is.o:             is.cpp  npbparams.h is.pob.h


clean:
	- rm -f *.o *~ mputil*
	- rm -f is npbparams.h core
