#ifndef juego_h
#define juego_h

#define MAX_F 12
#define MAX_C 20
#include "tablero.h"



typedef char t_plano[MAX_F+2][MAX_C];


typedef struct{
  tablero t;
  int jug_x;
  int jug_y;
}partida;


void empezar_partida(partida *p, t_plano t);
void imprimir_tablero(partida p);
bool mover(partida *p, int tecla);
bool mover_jugador(partida *p, int tecla);
bool mover_jugador_caja(partida *p, int tecla);
bool mover_jugador_caja_obj(partida *p, int tecla);
bool mover_caja_fueraobj(partida *p,int tecla);
bool mover_caja_entreobj(partida *p, int tecla);
bool mover_jugador_objetivo(partida *p, int tecla);
#endif
