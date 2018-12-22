#include <stdio.h>
#include <stdbool.h>
#include "juego.h"
#include "casilla.h"
#include "teclas.h"
#include "tablero.h"
#include "colores.h"


#define MAX_F 12
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
  printf("Pulse las teclas para moverte. Restart 'r'. Quit 'q'.\n");
  printf_color(GREEN);
  printf("Nivel: Nivel Medio.\n");
  printf_color(WHITE);

  printf("goles: %d    cajas en goles: %d\nnum_pasos: %d   num_empujes: %d\n",p.t.cajas_fuera,p.t.cajas_dentro,p.t.movimientos,p.t.empujones);
  for(int i = 0; i < MAX_F; i++){
    for(int j = 0; j < MAX_C; j++){
      if(p.t.c[i][j].tipo == JUGADOR){
        printf_color(GREEN);
        printf("%c",p.t.c[i][j].tipo);
      }
      else if(p.t.c[i][j].tipo == PARED){
        printf_color(RED);
        printf("%c",p.t.c[i][j].tipo);
      }
      else if(p.t.c[i][j].tipo == CAJA){
        printf_color(YELLOW);
        printf("%c",p.t.c[i][j].tipo);
      }
      else if(p.t.c[i][j].tipo == GOAL){
        printf_color(BOLD_BLUE);
        printf("%c",p.t.c[i][j].tipo);
      }
      else if(p.t.c[i][j].tipo == SUELO){
        printf_color(WHITE);
        printf("%c",p.t.c[i][j].tipo);
      }
      else if(p.t.c[i][j].tipo == CAJA_COMPLET){
        printf_color(BOLD_CYAN);
        printf("%c",p.t.c[i][j].tipo);
      }
      else if(p.t.c[i][j].tipo == JUGADOR_CAJA){
        printf_color(BOLD_CYAN);
        printf("%c",p.t.c[i][j].tipo);
            }
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
      }
      else if(p->t.c[posx-1][posy].tipo == CAJA && p->t.c[posx-2][posy].tipo == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx-1][posy].tipo == SUELO){
        res = mover_jugador(p, tecla);
      }
      else if(p->t.c[posx-1][posy].tipo == CAJA_COMPLET && p->t.c[posx-2][posy].tipo == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx-1][posy].tipo == CAJA_COMPLET && p->t.c[posx-2][posy].tipo == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
    }
  }
  else if(tecla == 2){
    if(p->t.c[posx+1][posy].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx+1][posy].tipo == CAJA && p->t.c[posx+2][posy].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx+1][posy].tipo == CAJA && p->t.c[posx+2][posy].tipo == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx+1][posy].tipo == SUELO){
        res = mover_jugador(p, tecla);
      }
      else if(p->t.c[posx+1][posy].tipo == CAJA_COMPLET && p->t.c[posx+2][posy].tipo == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx+1][posy].tipo == CAJA_COMPLET && p->t.c[posx+2][posy].tipo == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
    }
  }
  else if(tecla == 3){
    if(p->t.c[posx][posy-1].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx][posy-1].tipo == CAJA && p->t.c[posx][posy-2].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx][posy-1].tipo == CAJA && p->t.c[posx][posy-2].tipo == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx][posy-1].tipo == SUELO){     //No llegeix el espai
        res = mover_jugador(p, tecla);  //
      }
      else if(p->t.c[posx][posy-1].tipo == CAJA_COMPLET && p->t.c[posx][posy-2].tipo == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx][posy-1].tipo == CAJA_COMPLET && p->t.c[posx][posy-2].tipo == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
    }
  }
  else if(tecla == 4){
    if(p->t.c[posx][posy+1].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx][posy+1].tipo == CAJA && p->t.c[posx][posy+2].tipo == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx][posy+1].tipo == CAJA && p->t.c[posx][posy+2].tipo == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx][posy+1].tipo == SUELO){
        res = mover_jugador(p, tecla);
      }
      else if(p->t.c[posx][posy+1].tipo == CAJA_COMPLET && p->t.c[posx][posy+2].tipo == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx][posy+1].tipo == CAJA_COMPLET && p->t.c[posx][posy+2].tipo == GOAL){
        res = mover_caja_entreobj(p, tecla);
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
  else if(t == 2){
    p->t.c[posx+1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_x++;

  }
  else if(t == 3){
    p->t.c[posx][posy-1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y--;
  }
  else if(t == 4){
    p->t.c[posx][posy+1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y++;
  }
  p->t.movimientos++;
  return true;
}
void empezar_partida(partida *par, t_plano tablero){
  int i,j;
  par->t.empujones = 0;
  par->t.movimientos = 0;
  par->t.cajas_fuera = 0;
  par->t.cajas_dentro = 0;
  for(i = 0; i < MAX_F;i++){
    for(j = 0; j < MAX_C;j++){
      if(tablero[i][j] == CAJA){
        par->t.c[i][j].tipo = CAJA;
        par->t.cajas_fuera++;
      }
      else if(tablero[i][j] == JUGADOR){      //booleano de caja a false
        par->t.c[i][j].tipo = JUGADOR;
        par->jug_x = i;
        par->jug_y = j;
      }
      else if(tablero[i][j] == GOAL){
        par->t.c[i][j].tipo = GOAL;
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

  if(t == 1){
    p->t.c[posx-2][posy].tipo = p->t.c[posx-1][posy].tipo;
    p->t.c[posx-1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_x--;
  }
  else if(t == 2){
    p->t.c[posx+2][posy].tipo = p->t.c[posx+1][posy].tipo;
    p->t.c[posx+1][posy].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_x++;
  }
  else if(t == 3){
    p->t.c[posx][posy-2].tipo = p->t.c[posx][posy-1].tipo;
    p->t.c[posx][posy-1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y--;
  }
  else if(t == 4){
    p->t.c[posx][posy+2].tipo = p->t.c[posx][posy+1].tipo;
    p->t.c[posx][posy+1].tipo = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].tipo = SUELO;
    p->jug_y++;
  }
  p->t.empujones++;
  p->t.movimientos++;
  return true;
}

bool mover_jugador_caja_obj(partida *p, int t){
    int posx = p->jug_x;
    int posy = p->jug_y;

    //Tecla hacia arriba

    if(t == 1){
      p->t.c[posx-2][posy].tipo = CAJA_COMPLET;
      p->t.c[posx-1][posy].tipo = JUGADOR;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_x--;
      p->t.cajas_dentro++;
      p->t.cajas_fuera--;
    }
    else if(t == 2){
      p->t.c[posx+2][posy].tipo = CAJA_COMPLET;
      p->t.c[posx+1][posy].tipo = JUGADOR;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_x++;
      p->t.cajas_dentro++;
      p->t.cajas_fuera--;
    }
    else if(t == 3){
      p->t.c[posx][posy-2].tipo = CAJA_COMPLET;
      p->t.c[posx][posy-1].tipo = JUGADOR;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_y--;
      p->t.cajas_dentro++;
      p->t.cajas_fuera--;
    }
    else if(t == 4){
      p->t.c[posx][posy+2].tipo = CAJA_COMPLET;
      p->t.c[posx][posy+1].tipo = JUGADOR;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_y++;
      p->t.cajas_dentro++;
      p->t.cajas_fuera--;
    }
    p->t.empujones++;
    p->t.movimientos++;
    return true;
}


bool mover_caja_fueraobj(partida *p, int t){
    int posx = p->jug_x;
    int posy = p->jug_y;

    //Tecla hacia arriba

    if(t == 1){
      p->t.c[posx-2][posy].tipo = CAJA;
      p->t.c[posx-1][posy].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_x--;
      p->t.cajas_dentro--;
      p->t.cajas_fuera++;
    }
    else if(t == 2){
      p->t.c[posx+2][posy].tipo = CAJA;
      p->t.c[posx+1][posy].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_x++;
      p->t.cajas_dentro--;
      p->t.cajas_fuera++;
    }
    else if(t == 3){
      p->t.c[posx][posy-2].tipo = CAJA;
      p->t.c[posx][posy-1].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_y--;
      p->t.cajas_dentro--;
      p->t.cajas_fuera++;
    }
    else if(t == 4){
      p->t.c[posx][posy+2].tipo = CAJA;
      p->t.c[posx][posy+1].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_y++;
      p->t.cajas_dentro--;
      p->t.cajas_fuera++;
    }
    p->t.empujones++;
    p->t.movimientos++;
    return true;
}

bool mover_caja_entreobj(partida *p, int t){
    int posx = p->jug_x;
    int posy = p->jug_y;

    //Tecla hacia arriba

    if(t == 1){
      p->t.c[posx-2][posy].tipo = CAJA_COMPLET;
      p->t.c[posx-1][posy].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_x--;
    }
    else if(t == 2){
      p->t.c[posx+2][posy].tipo = CAJA_COMPLET;
      p->t.c[posx+1][posy].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_x++;
    }
    else if(t == 3){
      p->t.c[posx][posy-2].tipo = CAJA_COMPLET;
      p->t.c[posx][posy-1].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_y--;
    }
    else if(t == 4){
      p->t.c[posx][posy+2].tipo = CAJA_COMPLET;
      p->t.c[posx][posy+1].tipo = JUGADOR_CAJA;
      p->t.c[posx][posy].tipo = SUELO;
      p->jug_y++;
    }
    p->t.empujones++;
    p->t.movimientos++;
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
      borrar_pantalla();
      ok = mover(&p, pos);
      imprimir_tablero(p);
      pos = lee_tecla();
    }
}
