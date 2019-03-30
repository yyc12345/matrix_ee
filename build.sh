#!/bin/bash
compiler="clang"
obj="main.o utility.o matrix.o regular_expression.o module/matrix_hand.o module/matrix_auto.o"
target="matrix.out"
command="-std=c11"

#rm
rm -f $obj $target &&

#compile
$compiler -c main.c -o main.o $command &&
$compiler -c utility.c -o utility.o $command &&
$compiler -c regular_expression.c -o regular_expression.o $command &&
$compiler -c matrix.c -o matrix.o $command &&
$compiler -c module/matrix_hand.c -o module/matrix_hand.o $command &&
$compiler -c module/matrix_auto.c -o module/matrix_auto.o $command &&

#link
$compiler $obj -o $target $command &&

echo "OK"
