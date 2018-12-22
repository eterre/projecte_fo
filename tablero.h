#ifndef tablero_h
#define tablero_h

#define MAX_F 12
#define MAX_C 20
#include "casilla.h"

typedef struct{
  casilla c[MAX_F][MAX_C];
  int movimientos;
  int empujones;
  int cajas_fuera;
  int cajas_dentro;
}tablero;
#endif
