#include "Activaciones.h"
#include "../AlgebraLineal/OperacionesMatrices.h"
#include <math.h>

double sigmoide(double input) {
    return 1.0 / (1 + exp(-1 * input));
}

Matriz *sigmoid_derivado(Matriz *m) {
    Matriz *unos = crear_matriz(m->filas, m->cols);
    llenar_matriz(unos, 1);

    Matriz *restada = restar(unos, m);
    Matriz *mult_simple = multiplicacion_simple(m, restada);

    liberar_matriz(unos);
    liberar_matriz(restada);

    return mult_simple;
}

Matriz *softmax(Matriz *m) {
    double total = 0;

    for (int i = 0; i < m->filas; i++) {
        for (int j = 0; j < m->cols; j++) {
            total += exp(m->valores[i][j]);
        }
    }

    Matriz *mat = crear_matriz(m->filas, m->cols);
    for (int i = 0; i < mat->filas; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->valores[i][j] = exp(m->valores[i][j]) / total;
        }
    }

    return mat;
}
