#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "Matriz.h"

#define __TAM_MAXIMO__ 100

Matriz *crear_matriz(int filas, int cols) {
    Matriz *mat = (Matriz *) malloc(sizeof (Matriz));

    if(mat == NULL){
        printf("No hay suficiente memoria.");
        exit(-1);
    }

    mat->filas = filas;
    mat->cols = cols;
    mat->valores = (double **) malloc(filas * sizeof (double*));

    if(mat->valores == NULL){
        printf("no hay suficiente memoria.");
        exit(-1);
    }

    for (int i = 0; i < filas; ++i) {
        mat->valores[i] = malloc(cols * sizeof (double));

        if(mat->valores[i] == NULL){
            printf("No hay suficiente memoria.");
            exit(-1);
        }
    }

    return mat;
}

void llenar_matriz(Matriz *m, int n) {
    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            m->valores[i][j] = n;
        }
    }
}

void liberar_matriz(Matriz *m) {
    for (int i = 0; i < m->filas; ++i) {
        free(m->valores[i]);
    }
    free(m);
    m = NULL;
}

void imprimir_matriz(Matriz *m) {
    printf("Nro de filas: %d. Nro de columnas: %d.\n", m->filas, m->cols);
    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            printf("%1.3f ", m->valores[i][j]);
        }
        printf("\n");
    }
}

Matriz *copiar_matriz(Matriz *m) {
    Matriz *copia = crear_matriz(m->filas, m->cols);

    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            copia->valores[i][j] = m->valores[i][j];
        }
    }

    return copia;
}

void guardar_matriz(Matriz *m, char *ruta) {
    FILE *archivo = fopen(ruta, "w");
    fprintf(archivo, "%d\n", m->filas);
    fprintf(archivo, "%d\n", m->cols);

    for (int i = 0; i < m->filas; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            fprintf(archivo, "%.6f\n", m->valores[i][j]);
        }
    }

    printf("Matriz guardada en %s.\n", ruta);
    fclose(archivo);

}

Matriz *cargar_matriz(char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    char entrada[__TAM_MAXIMO__];

    fgets(entrada, __TAM_MAXIMO__, archivo);
    int filas = atoi(entrada);
    fgets(entrada, __TAM_MAXIMO__, archivo);
    int cols = atoi(entrada);

    Matriz *mat = crear_matriz(filas, cols);
    for (int i = 0; i < mat->filas; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            fgets(entrada, __TAM_MAXIMO__, archivo);
            mat->valores[i][j] = strtod(entrada, NULL);
        }
    }

    printf("Matriz cargada exitosamente del archivo %s.\n", ruta);
    fclose(archivo);

    return mat;
}

double distribucion_uniforme(double menor, double maximo) {
    double diferencia = maximo - menor; // La diferencia entre los dos
    int escala = 10000;
    int diferencia_escalada = (int)(diferencia * escala);
    return menor + (1.0 * (rand() % diferencia_escalada) / escala);
}

void matriz_aleatoria(Matriz* m, int n) {
    // Distribucion aleatoria a partir de
    // Min: -1 / sqrt(n)
    // Max: 1 / sqrt(n)
    double min = -1.0 / sqrt(n);
    double max = 1.0 / sqrt(n);
    for (int i = 0; i < m->filas; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->valores[i][j] = distribucion_uniforme(min, max);
        }
    }
}

int maximo_matriz(Matriz *m) {
    // Se espera una matriz de Mx1
    double puntaje_max = 0;
    int max_idx = 0;
    for (int i = 0; i < m->filas; i++) {
        if (m->valores[i][0] > puntaje_max) {
            puntaje_max = m->valores[i][0];
            max_idx = i;
        }
    }
    return max_idx;
}

Matriz *aplanar_matriz(Matriz *m, int eje) {
    // Eje = 0 -> Vector columna, Eje = 1 -> Vector fila
    Matriz* mat;
    if (eje == 0) {
        mat = crear_matriz(m->filas * m->cols, 1);
    } else if (eje == 1) {
        mat = crear_matriz(1, m->filas * m->cols);
    } else {
        printf("El argumento para aplanar la matriz debe ser 0 o 1");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m->filas; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (eje == 0) mat->valores[i * m->cols + j][0] = m->valores[i][j];
            else mat->valores[0][i * m->cols + j] = m->valores[i][j];
        }
    }

    return mat;
}
