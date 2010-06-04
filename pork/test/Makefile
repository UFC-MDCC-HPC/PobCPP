# Piglet makefile
#
# Builds an Elsa app without Oink!

topdir = ..

include $(topdir)/config.mk
include $(topdir)/build.mk

.PHONY: check clean

check: checkpatcher

checkpatcher: patchertests
	./patchertests

patchertests: patchertests.o $(PIGLET_OBJS)
	g++ -o $@ $+;

clean:
	-rm *.o
