#include <stdio.h>
#include <stdlib.h>
#include "OperacionesMatrices.h"

int verificar_tamano(Matriz *m1, Matriz *m2){
    if(m1->filas == m2->filas && m1->cols == m2->cols){
        return 1;
    }
    return 0;
}

Matriz *multiplicacion_simple(Matriz *m1, Matriz *m2) {
    if(verificar_tamano(m1, m2)) {
        Matriz *resultado = crear_matriz(m1->filas, m1->cols);

        for (int i = 0; i < m1->filas; ++i) {
            for (int j = 0; j < m1->cols; ++j) {
                resultado->valores[i][j] = m1->valores[i][j] * m2->valores[i][j];
            }
        }

        return resultado;
    }
    printf("Las matrices no tienen exactamente el mismo tamaño.");
    exit(-1);
}

Matriz *sumar(Matriz *m1, Matriz *m2) {
    if(verificar_tamano(m1, m2)){
        Matriz *resultado = crear_matriz(m1->filas, m2->cols);

        for (int i = 0; i < m1->filas; ++i) {
            for (int j = 0; j < m1->cols; ++j) {
                resultado->valores[i][j] = m1->valores[i][j] + m2->valores[i][j];
            }
        }
        
        return resultado;
    }
    printf("Las matrices no tienen exactamente el mismo tamaño.");
    exit(-1);
}

Matriz *restar(Matriz *m1, Matriz *m2) {
    if(verificar_tamano(m1, m2)){
        Matriz *resultado = crear_matriz(m1->filas, m2->cols);

        for (int i = 0; i < m1->filas; ++i) {
            for (int j = 0; j < m1->cols; ++j) {
                resultado->valores[i][j] = m1->valores[i][j] - m2->valores[i][j];
            }
        }

        return resultado;
    }
    printf("Las matrices no tienen exactamente el mismo tamaño.");
    exit(-1);
}

Matriz *multiplicar(Matriz *m1, Matriz *m2) {
    if(m1->cols == m2->filas){
        Matriz *resultado = crear_matriz(m1->filas, m2->cols);

        for (int i = 0; i < m1->filas; ++i) {
            for (int j = 0; j < m2->cols; ++j) {

                double suma = 0;
                for (int k = 0; k < m2->filas; ++k) {
                    suma += m1->valores[i][k] * m2->valores[k][j];
                }
                resultado->valores[i][j] = suma;

            }
        }

        return resultado;
    }
    printf("Las matrices no tienen exactamente el mismo tamaño.");
    exit(-1);
}

Matriz *aplicar(double (*func)(double), Matriz *m) {
    Matriz *resultado = copiar_matriz(m);

    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            resultado->valores[i][j] = (*func) (m->valores[i][j]);
        }
    }

    return resultado;
}

Matriz *escalar(double n, Matriz *m) {
    Matriz *resultado = copiar_matriz(m);

    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            resultado->valores[i][j] *= n;
        }
    }

    return resultado;
}

Matriz *sumar_escalar(double n, Matriz *m) {
    Matriz *resultado = copiar_matriz(m);

    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            resultado->valores[i][j] += n;
        }
    }

    return resultado;
}

Matriz *transponer(Matriz *m) {
    Matriz *resultado = crear_matriz(m->cols, m->filas);

    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            resultado->valores[i][j] = m->valores[j][i];
        }
    }

    return resultado;
}
