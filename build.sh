#!/bin/bash
compiler="clang"
obj="main.o matrix.o module/matrix_hand.o module/matrix_auto.o"
target="matrix.out"

#rm
rm -f $obj $target &&

#compile
$compiler -c main.c -o main.o &&
$compiler -c matrix.c -o matrix.o &&
$compiler -c module/matrix_hand.c -o module/matrix_hand.o &&
$compiler -c module/matrix_auto.c -o module/matrix_auto.o &&

#link
$compiler $obj -o $target &&

echo "OK"
