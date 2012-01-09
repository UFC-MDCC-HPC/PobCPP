#!/bin/bash
pobcppc=/home/eduardo/projects/mestrado/pobcpp/pork/prepobcppc
libpobcpp=/home/eduardo/projects/mestrado/pobcpp/libpobcpp/include
echo $pobcppc farm.h $libpobcpp
$pobcppc farm.h $libpobcpp
echo $pobcppc integrator.h $libpobcpp
$pobcppc integrator.h $libpobcpp
echo $pobcppc integrator_main.h $libpobcpp
$pobcppc integrator_main.h $libpobcpp
bjam-1_40 -q

