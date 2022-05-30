#pragma once

#include "Matriz.h"

#ifndef PRIMERAREDNEURONAL_OPERACIONESMATRICES_H
#define PRIMERAREDNEURONAL_OPERACIONESMATRICES_H

Matriz *multiplicacion_simple (Matriz *m1, Matriz *m2);
Matriz *sumar (Matriz *m1, Matriz *m2);
Matriz *restar (Matriz *m1, Matriz *m2);
Matriz *multiplicar (Matriz *m1, Matriz *m2);
Matriz *aplicar (double (*func) (double ),Matriz *m);
Matriz *escalar (double n, Matriz *m);
Matriz *sumar_escalar (double n, Matriz *m);
Matriz *transponer (Matriz *m);


#endif //PRIMERAREDNEURONAL_OPERACIONESMATRICES_H
