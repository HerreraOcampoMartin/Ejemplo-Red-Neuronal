cmake_minimum_required(VERSION 3.22)
project(PrimeraRedNeuronal C)

set(CMAKE_C_STANDARD 99)

add_executable(PrimeraRedNeuronal main.c AlgebraLineal/Matriz.c AlgebraLineal/Matriz.h AlgebraLineal/OperacionesMatrices.c AlgebraLineal/OperacionesMatrices.h util/Imagen.c util/Imagen.h RedNeuronal/Activaciones.c RedNeuronal/Activaciones.h RedNeuronal/Redes.c RedNeuronal/Redes.h)
target_link_libraries(PrimeraRedNeuronal m)