#!/bin/bash
pobcppc=/home/eduardo/projects/mestrado/pobcpp/pork/prepobcppc 
#libpetsc="-I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/"
libpetsc="-I /home/eduardo/install/petsc-3.1-p5/linux/include/ -I /home/eduardo/install/petsc-3.1-p5/include/"
libpobcpp=/home/eduardo/projects/mestrado/pobcpp/libpobcpp/include

$pobcppc vec.h $libpobcpp $libpetsc
$pobcppc vec.cpp $libpobcpp $libpetsc
$pobcppc mat.h $libpobcpp $libpetsc
$pobcppc mat.cpp $libpobcpp $libpetsc
$pobcppc ksp.h $libpobcpp $libpetsc
$pobcppc ksp.cpp $libpobcpp $libpetsc

#g++ vec.pob.cpp -I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/ -I ../libpobcpp/include/ ../libpobcpp/bin/gcc-4.3.4/debug/link-static/libpobcpp.a ~/install/petsc-3.1-p5/linux/lib/libpetsc.a  -lX11 ~/install/petsc-3.1-p5/linux/lib/*.a  -L/home/eduardo/install/petsc-3.1-p5/linux/lib -lpetsc   -lX11 -L/home/eduardo/install/petsc-3.1-p5/linux/lib -lf2clapack -lf2cblas -lm -L/usr/lib -lmpi -lm -ldl  -o testee -lmpi -lboost_mpi-mt
g++ ksp.pob.cpp mat.pob.cpp vec.pob.cpp main.cpp -I ~/install/petsc-3.1-p5/linux/include/ -I ~/install/petsc-3.1-p5/include/ -I ../libpobcpp/include/ ../libpobcpp/bin/gcc-4.4.5/debug/libpobcpp.so ~/install/petsc-3.1-p5/linux/lib/libpetsc.a  -lX11 ~/install/petsc-3.1-p5/linux/lib/*.a  -L/home/eduardo/install/petsc-3.1-p5/linux/lib -lpetsc   -lX11 -L/home/eduardo/install/petsc-3.1-p5/linux/lib -lf2clapack -lf2cblas -lm -L/usr/lib -lmpi -lm -ldl  -o testee -lmpi -lboost_mpi-mt
