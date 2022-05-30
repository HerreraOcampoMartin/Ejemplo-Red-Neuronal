#pragma once

#include "../AlgebraLineal/Matriz.h"

#ifndef PRIMERAREDNEURONAL_IMAGEN_H
#define PRIMERAREDNEURONAL_IMAGEN_H

typedef struct img{
    Matriz *datos;
    int etiqueta;
} Imagen;

Imagen **csv_a_imagen(char *ruta, int cant_imagenes);
void imprimir_imagen(Imagen *img);
void liberar_imagen(Imagen *img);
void liberar_imagenes(Imagen **imgs, int n);

#endif //PRIMERAREDNEURONAL_IMAGEN_H
