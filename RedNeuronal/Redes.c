#include "Redes.h"
#include "../AlgebraLineal/OperacionesMatrices.h"
#include "Activaciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define __TAM_MAXIMO__ 1000

// 784, 300, 10
RedNeuronal *crear_red(int input, int ocultas, int salida, double aprendizaje) {
    RedNeuronal *red = (RedNeuronal*) malloc(sizeof (RedNeuronal));

    if(red == NULL){
        printf("No hay suficiente memoria.");
        exit(-1);
    }

    red->input = input;
    red->ocultas = ocultas;
    red->salida = salida;
    red->aprendizaje = aprendizaje;

    Matriz *capa_oculta = crear_matriz(ocultas, input);
    Matriz *capa_salida = crear_matriz(salida, ocultas);

    matriz_aleatoria(capa_oculta, ocultas);
    matriz_aleatoria(capa_salida, salida);

    red->pesos_ocultos = capa_oculta;
    red->pesos_salida = capa_salida;

    return red;
}

void entrenar_red(RedNeuronal *red, Matriz *datos_entrada, Matriz *datos_salida) {
    // Alimentar red
    Matriz* entradas_ocultas = multiplicar(red->pesos_ocultos, datos_entrada);
    Matriz* salidas_ocultas = aplicar(sigmoide, entradas_ocultas);
    Matriz* entradas_finales = multiplicar(red->pesos_salida, salidas_ocultas);
    Matriz* salidas_finales = aplicar(sigmoide, entradas_finales);

    // Encontrar errores
    Matriz* errores_salida = restar(datos_salida, salidas_finales);
    Matriz *errores_ocultos = multiplicar(transponer(red->pesos_salida), errores_salida);

    //Propagación hacia atrás
    // pesos_salida = sumar(
    //		 pesos_salidas,
    //     escalar(
    // 			  red->aprendizaje,
    //			  multiplicar(
    // 		 			multiplicacion_simple(
    // 						errores_salida,
    //				  	sigmoide_derivado(salidas_finales)
    //					),
    //					transponer(salidas_ocultas)
    // 				)
    //		 )
    // )
    Matriz *mat_sigmoide_derivado = sigmoid_derivado(salidas_finales);
    Matriz *mat_mult_simple = multiplicacion_simple(errores_salida, mat_sigmoide_derivado);
    Matriz *mat_transpuesta = transponer(salidas_ocultas);
    Matriz *mat_multiplicada = multiplicar(mat_mult_simple, mat_transpuesta);
    Matriz *mat_escalada = escalar(red->aprendizaje, mat_multiplicada);
    Matriz *mat_sumada = sumar(red->pesos_salida, mat_escalada);
    liberar_matriz(red->pesos_salida); // Liberar los pesos antiguos antes de reemplazar
    red->pesos_salida = mat_sumada;

    liberar_matriz(mat_sigmoide_derivado);
    liberar_matriz(mat_mult_simple);
    liberar_matriz(mat_transpuesta);
    liberar_matriz(mat_multiplicada);
    liberar_matriz(mat_escalada);

    // pesos_salida = sumar(
    // 	 red->pesos_salida,
    // 	 escalar (
    //	    	red->aprendizaje
    //    	multiplicar (
    //				multiplicacion_simple(
    //					errores_ocultos,
    //					sigmoide_derivado(salidas_ocultas)
    //				)
    //				transpose(datos_entrada)
    //      )
    // 	 )
    // )
    //Reusar variables después de liberar memoria
    mat_sigmoide_derivado = sigmoid_derivado(salidas_ocultas);
    mat_mult_simple = multiplicacion_simple(errores_ocultos, mat_sigmoide_derivado);
    mat_transpuesta = transponer(datos_entrada);
    mat_multiplicada = multiplicar(mat_mult_simple, mat_transpuesta);
    mat_escalada = escalar(red->aprendizaje, mat_multiplicada);
    mat_sumada = sumar(red->pesos_ocultos, mat_escalada);
    liberar_matriz(red->pesos_ocultos);
    red->pesos_ocultos = mat_sumada;

    liberar_matriz(mat_sigmoide_derivado);
    liberar_matriz(mat_mult_simple);
    liberar_matriz(mat_transpuesta);
    liberar_matriz(mat_multiplicada);
    liberar_matriz(mat_escalada);

    // Liberar matrices
    liberar_matriz(entradas_ocultas);
    liberar_matriz(salidas_ocultas);
    liberar_matriz(entradas_finales);
    liberar_matriz(salidas_finales);
    liberar_matriz(errores_salida);
    liberar_matriz(errores_ocultos);


}

void entrenar_red_multiples_imgs(RedNeuronal *red, Imagen **imgs, int tamano) {
    for (int i = 0; i < tamano; i++) {
        if(i % 100 == 0) printf("Imagen numero %d\n", i);

        Imagen *imagen_actual = imgs[i];
        Matriz *datos_img = aplanar_matriz(imagen_actual->datos, 0); // Aplanar la matriz a vector columna
        Matriz *salida = crear_matriz(10, 1);
        salida->valores[imagen_actual->etiqueta][0] = 1; // Poner el resultado
        entrenar_red(red, datos_img, salida);
        liberar_matriz(salida);
        liberar_matriz(datos_img);
    }
}

Matriz *red_predecir_imagen(RedNeuronal *red, Imagen *img) {
    Matriz *datos_img = aplanar_matriz(img->datos, 0);
    Matriz *res = red_predecir(red, datos_img);
    liberar_matriz(datos_img);

    return res;
}

double red_predecir_imgs(RedNeuronal *red, Imagen **imgs, int n) {
    int n_correctos = 0;
    for (int i = 0; i < n; i++) {
        Matriz *prediccion = red_predecir_imagen(red, imgs[i]);

        if(maximo_matriz(prediccion) == imgs[i]->etiqueta){
            n_correctos++;
        }

        liberar_matriz(prediccion);
    }
    return 1.0 * n_correctos / n;
}

Matriz *red_predecir(RedNeuronal *red, Matriz *datos) {
    Matriz *entradas_ocultas = multiplicar(red->pesos_ocultos, datos);
    Matriz *salidas_ocultas = aplicar(sigmoide, entradas_ocultas);
    Matriz *entradas_finales = multiplicar(red->pesos_salida, salidas_ocultas);
    Matriz *salidas_finales = aplicar(sigmoide, entradas_finales);
    Matriz *resultado = softmax(salidas_finales);

    return resultado;
}

void guardar_red(RedNeuronal *red, char *ruta) {
    mkdir(ruta, 0777);
    // Escribir archivo descriptivo
    chdir(ruta);

    FILE *descriptor = fopen("descriptor", "w");
    fprintf(descriptor, "%d\n", red->input);
    fprintf(descriptor, "%d\n", red->ocultas);
    fprintf(descriptor, "%d\n", red->salida);
    fclose(descriptor);

    guardar_matriz(red->pesos_ocultos, "oculto");
    guardar_matriz(red->pesos_salida, "salida");

    printf("Red guardada exitosamente en '%s'.\n", ruta);
    chdir("-"); //Volver al directorio anterior
}

RedNeuronal *cargar_red(char *ruta) {
    RedNeuronal *red = (RedNeuronal*) malloc(sizeof (RedNeuronal));
    char entrada[__TAM_MAXIMO__];
    chdir(ruta);

    FILE *descriptor = fopen("descriptor", "r");
    fgets(entrada, __TAM_MAXIMO__, descriptor);
    red->input = atoi(entrada);
    fgets(entrada, __TAM_MAXIMO__, descriptor);
    red->ocultas = atoi(entrada);
    fgets(entrada, __TAM_MAXIMO__, descriptor);
    red->salida = atoi(entrada);
    fclose(descriptor);

    red->pesos_ocultos = cargar_matriz("oculto");
    red->pesos_salida = cargar_matriz("salida");

    printf("Red cargada exitosamente del directorio '%s'\n", ruta);
    chdir("-");

    return red;
}

void imprimir_red(RedNeuronal *red) {
    printf("# de Inputs: %d\n", red->input);
    printf("# de Ocultas: %d\n", red->ocultas);
    printf("# de Salida: %d\n", red->salida);
    printf("Pesos ocultos: \n");
    imprimir_matriz(red->pesos_ocultos);
    printf("Pesos salida: \n");
    imprimir_matriz(red->pesos_salida);
}

void liberar_red(RedNeuronal *red) {
    liberar_matriz(red->pesos_ocultos);
    liberar_matriz(red->pesos_salida);
    free(red);
    red = NULL;
}
