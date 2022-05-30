#include "Imagen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __TAM_MAXIMO__ 10000

Imagen **csv_a_imagen(char *ruta, int cant_imagenes) {
    FILE *archivo;

    Imagen **imgs = malloc(cant_imagenes * sizeof (Imagen *));
    char fila[__TAM_MAXIMO__];

    archivo = fopen(ruta, "r");

    fgets(fila, __TAM_MAXIMO__, archivo);
    int i = 0;

    while (feof((archivo)) != 1 && i < cant_imagenes){
        imgs[i] = malloc(sizeof (Imagen));

        int j = 0;
        fgets(fila, __TAM_MAXIMO__, archivo);

        char *token = strtok(fila, ",");
        imgs[i]->datos = crear_matriz(28, 28);
        while (token != NULL){
            if(j == 0){
                imgs[i]->etiqueta = atoi(token);
            } else {
                imgs[i]->datos->valores[(j-1) / 28][(j-1) % 28] = atoi(token) / 256.0;
            }

            token = strtok(NULL, ",");
            j++;
        }

        i++;
    }

    fclose(archivo);
    return imgs;
}

void imprimir_imagen(Imagen *img) {
    imprimir_matriz(img->datos);
    printf("Etiqueta de la imagen: %d\n", img->etiqueta);
}

void liberar_imagen(Imagen *img) {
    liberar_matriz(img->datos);
    free(img);
    img = NULL;
}

void liberar_imagenes(Imagen **imgs, int n) {
    for (int i = 0; i < n; ++i) {
        liberar_imagen(imgs[i]);
    }
}
