#pragma once

#include "../AlgebraLineal/Matriz.h"
#include "../util/Imagen.h"

#ifndef PRIMERAREDNEURONAL_REDES_H
#define PRIMERAREDNEURONAL_REDES_H

typedef struct red {
    int input;
    int ocultas;
    int salida;
    double aprendizaje;
    Matriz *pesos_ocultos;
    Matriz *pesos_salida;
} RedNeuronal;

RedNeuronal *crear_red(int input, int ocultas, int salida, double aprendizaje);
void entrenar_red(RedNeuronal *red, Matriz *datos_entrada, Matriz* datos_salida);
void entrenar_red_multiples_imgs(RedNeuronal *red, Imagen** imgs, int tamano);
Matriz* red_predecir_imagen(RedNeuronal *red, Imagen* img);
double red_predecir_imgs(RedNeuronal * red, Imagen ** imgs, int n);
Matriz* red_predecir(RedNeuronal * red, Matriz* datos);
void guardar_red(RedNeuronal * red, char* ruta);
RedNeuronal * cargar_red(char* ruta);
void imprimir_red(RedNeuronal * red);
void liberar_red(RedNeuronal * red);

#endif //PRIMERAREDNEURONAL_REDES_H
