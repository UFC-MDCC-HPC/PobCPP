#!/bin/bash
/home/eduardo/projects/mestrado/pobcpp/pork/pobcppc ksp.h ../libpobcpp/include/ -I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/
/home/eduardo/projects/mestrado/pobcpp/pork/pobcppc vec.h ../libpobcpp/include/ -I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/
/home/eduardo/projects/mestrado/pobcpp/pork/pobcppc mat.h ../libpobcpp/include/ -I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/
g++ ksp.cpp mat.cpp vec.cpp main.cpp -I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/ -I ../libpobcpp/include/ ../libpobcpp/bin/gcc-4.3.4/debug/link-static/libpobcpp.a ~/install/petsc-3.1-p5/linux/lib/libpetsc.a  -lX11 ~/install/petsc-3.1-p5/linux/lib/*.a  -L/home/eduardo/install/petsc-3.1-p5/linux/lib -lpetsc   -lX11 -L/home/eduardo/install/petsc-3.1-p5/linux/lib -lf2clapack -lf2cblas -lm -L/usr/lib -lmpi -lm -ldl  -o testee -lmpi -lboost_mpi-mt
