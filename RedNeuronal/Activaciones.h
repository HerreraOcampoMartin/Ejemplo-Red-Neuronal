#pragma once

#include "../AlgebraLineal/Matriz.h"

#ifndef PRIMERAREDNEURONAL_ACTIVACIONES_H
#define PRIMERAREDNEURONAL_ACTIVACIONES_H

double sigmoide(double input);
Matriz *sigmoid_derivado(Matriz *m);
Matriz *sofmax (Matriz *m)

#endif //PRIMERAREDNEURONAL_ACTIVACIONES_H
