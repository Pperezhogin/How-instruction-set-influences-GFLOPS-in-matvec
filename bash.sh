#!/bin/bash

lscpu

echo ""

icpc --version

echo ""

n0=1 # "iterations" for O0
n1=10 # "iterations" for O3

icpc main.cpp -O0
echo "icpc main.cpp -O0"
./a.out $n0
echo ""
echo ""

icpc main.cpp -O1
echo "icpc main.cpp -O1"
./a.out $n0
echo ""
echo ""

icpc main.cpp -O2
echo "icpc main.cpp -O2"
./a.out $n1
echo ""
echo ""

icpc main.cpp
echo "icpc main.cpp"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3
echo "icpc main.cpp -O3"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -msse4.1 -xSSE4.1
echo "icpc main.cpp -O3 -msse4.1 -xSSE4.1"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -msse4.2 -xSSE4.2
echo "icpc main.cpp -O3 -msse4.2 -xSSE4.2"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -mavx -xAVX
echo "icpc main.cpp -O3 -mavx -xAVX"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -march=core-avx2 -xcore-avx2
echo "icpc main.cpp -O3 -march=core-avx2 -xcore-avx2"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -xcommon-avx512
echo "icpc main.cpp -O3 -xcommon-avx512"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -AVX512
echo "icpc main.cpp -O3 -AVX512"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -xhost
echo "icpc main.cpp -O3 -xhost"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -xhost -restrict -alias-const -funroll-loops -no-ansi-alias
echo "icpc main.cpp -O3 -xhost -restrict -alias-const -funroll-loops -no-ansi-alias"
./a.out $n1
echo ""
echo ""

icpc main.cpp -O3 -xhost -parallel
echo "icpc main.cpp -O3 -xhost -parallel"
./a.out $n1
echo ""
echo ""