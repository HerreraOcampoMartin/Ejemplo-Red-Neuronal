#pragma once

#ifndef PRIMERAREDNEURONAL_MATRIZ_H
#define PRIMERAREDNEURONAL_MATRIZ_H

typedef struct matriz {
    double** valores;
    int cols;
    int filas;

} Matriz;

Matriz* crear_matriz(int filas, int cols);
void llenar_matriz(Matriz *m, int n);
void liberar_matriz(Matriz *m);
void imprimir_matriz(Matriz *m);
Matriz* copiar_matriz(Matriz *m);
void guardar_matriz(Matriz* m, char* ruta);
Matriz* cargar_matriz(char* ruta);
void matriz_aleatoria(Matriz* m, int n);
int maximo_matriz(Matriz* m);
Matriz* aplanar_matriz(Matriz* m, int eje);

#endif //PRIMERAREDNEURONAL_MATRIZ_H
