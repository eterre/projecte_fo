#include <stdio.h>
#include <stdbool.h>
#include "juego.h"
#include "casilla.h"
#include "teclas.h"
#include "tablero.h"

#define MAX_F 24
#define MAX_C 20

#define JUGADOR '@'
#define CAJA '$'
#define PARED '#'
#define CAJA_COMPLET '*'
#define JUGADOR_CAJA '+'
#define GOAL '.'
#define SUELO ' '

/*t_plano tab= {"##########",
              "#        #",
              "#   $ $  #",
              "#  $@    #",
              "#   $    #",
              "##########"};
*/
t_plano tab= {"    #####",
                  "    #   #",
                  "    #$  #",
                  "  ###  $##",
                  "  #  $ $ #",
                  "### # ## #   ######",
                  "#   # ## #####  ..#",
                  "# $  $  @       ..#",
                  "##### ### # ##  ..#",
                  "    #     #########",
                  "    #######",
                  "; Nivel medio",
                  ""};
void imprimir_tablero(partida p){
  printf("Pulsa las flechas para moverte. Restart 'r'. Quit 'q'.\nGoles: %d    Cajas_en_goles: %d\n num_pasos: %d    num_empujes: %d\n",p.t.goles,p.t.cajas_en_goles,p.t.num_pasos,p.t.num_empujes);
  for(int i = 0; i < MAX_F; i++){
    for(int j = 0; j < MAX_C; j++){
      printf("%c",p.t.c[i][j].tipo);
    }
    printf("\n");
  }
}


bool mover(partida *p, int tecla){
  int posx = p->jug_x;
  int posy = p->jug_y;
  bool res;

  if(tecla == 1){
    if(p->t.c[posx-1][posy].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx-1][posy].tipo == CAJA && p->t.c[posx-2][posy].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
        p->t.num_empujes++;
      }
      else if(p->t.c[posx][posy+1].tipo == CAJA && p->t.c[posx][posy+2].tipo == GOAL){
        //res = mover_jugador_caja_obj(p, tecla);
        //p->t.num_empujes++;
      }
      else if(p->t.c[posx-1][posy].tipo == SUELO){
        res = mover_jugador(p, tecla);
      }
    }
  }
  else if(tecla == 2){
    if(p->t.c[posx+1][posy].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx+1][posy].tipo == CAJA && p->t.c[posx+2][posy].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
        p->t.num_empujes++;
      }
      else if(p->t.c[posx][posy-1].tipo == CAJA && p->t.c[posx][posy-2].tipo == GOAL){
        //res = mover_jugador_caja_obj(p, tecla);
        //p->t.num_empujes++;
      }
      else if(p->t.c[posx+1][posy].tipo == SUELO){
        res = mover_jugador(p, tecla);
      }
    }
  }
  else if(tecla == 3){
    if(p->t.c[posx][posy-1].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx][posy-1].tipo == CAJA && p->t.c[posx][posy-2].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
        p->t.num_empujes++;
      }
      else if(p->t.c[posx-1][posy].tipo == CAJA && p->t.c[posx+2][posy].tipo == GOAL){
        //res = mover_jugador_caja_obj(p, tecla);
        //p->t.num_empujes++;
      }
      else if(p->t.c[posx][posy-1].tipo == SUELO){     //No llegeix el espai
        res = mover_jugador(p, tecla);  //
      }
    }
  }
  else if(tecla == 4){
    if(p->t.c[posx][posy+1].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx][posy+1].tipo == CAJA && p->t.c[posx][posy+2].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
        p->t.num_empujes++;
      }
      else if(p->t.c[posx-1][posy].tipo == CAJA && p->t.c[posx-2][posy].tipo == GOAL){
        //res = mover_jugador_caja_obj(p, tecla);
        //p->t.num_empujes++;
      }
      else if(p->t.c[posx][posy+1].tipo == SUELO){
        res = mover_jugador(p, tecla);
      }
    }
  }
  else if(tecla == 5){
    printf("Puta\n");
  }
  return res;
}

bool mover_jugador(partida *p, int t){
  //Pre: Ya sabemos que podemos moverlo hacia donde queremos
  int posx = p->jug_x;
  int posy = p->jug_y;
  if(t == 1){
    p->t.c[posx-1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;

    p->jug_x--;
  }
  if(t == 2){
    p->t.c[posx+1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_x++;

  }
  if(t == 3){
    p->t.c[posx][posy-1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y--;
  }
  if(t == 4){
    p->t.c[posx][posy+1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y++;
  }
  return true;
}
void empezar_partida(partida *par, t_plano tablero){
  int i,j;
  par->t.num_pasos = 0;
  par->t.num_empujes = 0;
  par->t.cajas_en_goles = 0;
  par->t.goles= 0;
  for(i = 0; i < MAX_F;i++){
    for(j = 0; j < MAX_C;j++){
      if(tablero[i][j] == CAJA){
        par->t.c[i][j].tipo = CAJA;
      }
      else if(tablero[i][j] == JUGADOR){      //booleano de caja a false
        par->t.c[i][j].tipo = JUGADOR;
        par->jug_x = i;
        par->jug_y = j;
        printf("\nx: %d y: %d\n", par->jug_x, par->jug_y);
      }
      else if(tablero[i][j] == GOAL){
        par->t.c[i][j].tipo = GOAL;
        par->t.goles++;
      }
      else if(tablero[i][j] == SUELO){
        par->t.c[i][j].tipo = SUELO;
      }
      else if(tablero[i][j] == PARED) par->t.c[i][j].tipo = PARED;
    }
  }
}

bool mover_jugador_caja(partida *p, int t){
  int posx = p->jug_x;
  int posy = p->jug_y;
  char aux1;
  char aux2;
  if(t == 1){
    p->t.c[posx-2][posy].tipo = p->t.c[posx-1][posy].tipo;
    p->t.c[posx-1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_x--;
  }
  if(t == 2){
    p->t.c[posx+2][posy].tipo = p->t.c[posx+1][posy].tipo;
    p->t.c[posx+1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_x++;
  }
  if(t == 3){
    p->t.c[posx][posy-2].tipo = p->t.c[posx][posy-1].tipo;
    p->t.c[posx][posy-1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y--;
  }
  if(t == 4){
    p->t.c[posx][posy+2].tipo = p->t.c[posx][posy+1].tipo;
    p->t.c[posx][posy+1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y++;
  }
  return true;
}


int main(){
  partida p;
  empezar_partida(&p, tab);

  imprimir_tablero(p);
  //tablero inicializado correctamente
  int pos = lee_tecla();
  bool ok;
  //scanf("%d%*c", &pos);
    while(pos != 5){
      p.t.num_pasos++;
      borrar_pantalla();
      ok = mover(&p, pos);
      imprimir_tablero(p);
      pos = lee_tecla();
    }
}
