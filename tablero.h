#ifndef tablero_h
#define tablero_h

#define MAX_F 24
#define MAX_C 20
#include "casilla.h"

typedef struct{
  casilla c[MAX_F][MAX_C];
  int num_pasos;
  int num_empujes;
  int cajas_en_goles;
  int goles;
}tablero;
#endif
