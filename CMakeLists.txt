cmake_minimum_required(VERSION 3.22)
project(PrimeraRedNeuronal C)

set(CMAKE_C_STANDARD 99)

add_executable(PrimeraRedNeuronal main.c AlgebraLineal/Matriz.c AlgebraLineal/Matriz.h AlgebraLineal/OperacionesMatrices.c AlgebraLineal/OperacionesMatrices.h)
