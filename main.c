
#include <stdio.h>
#include "util/Imagen.h"
#include "RedNeuronal/Redes.h"

int main() {
    // ENTRENAMIENTO
    int numero_imagenes = 10000;
    Imagen** imgs = csv_a_imagen("data/mnist_test.csv", numero_imagenes);
    RedNeuronal* red = crear_red(784, 300, 10, 1);
    entrenar_red_multiples_imgs(red, imgs, numero_imagenes);
    guardar_red(red, "red_prueba");

    // PREDICTING
    //int numero_imagenes = 3000;
    //Imagen ** imgs = csv_a_imagen("data/mnist_test.csv", numero_imagenes);
    //RedNeuronal *red = cargar_red("red_prueba");
    //double puntaje = red_predecir_imgs(red, imgs, 1000);
    //printf("Puntaje: %1.5f", puntaje);

    liberar_imagenes(imgs, numero_imagenes);
    liberar_red(red);

    return 0;
}
