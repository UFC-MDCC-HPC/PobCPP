#!/bin/bash
pobcppc=/home/eduardo/projects/mestrado/pobcpp/pork/prepobcppc
libpobcpp=/home/eduardo/projects/mestrado/pobcpp/libpobcpp/include
echo $pobcppc hello.cpp $libpobcpp
$pobcppc hello.cpp $libpobcpp
bjam-1_40 -q

