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

t_plano tab= {"##########",
              "#.       #",
              "#.  $ $  #",
              "#. $@    #",
              "#.  $    #",
              "##########"};

/*t_plano tab= {"    #####",
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
                  ""}; */

void empezar_partida(partida *par, t_plano tablero){
  int i,j;
  par->t.empujones = 0;
  par->t.movimientos = 0;
  par->t.cajas_fuera = 0;
  par->t.cajas_dentro = 0;
  for(i = 0; i < MAX_F;i++){
    for(j = 0; j < MAX_C;j++){
      if(tablero[i][j] == CAJA){
        par->t.c[i][j].tipo = SUELO;
        par->t.c[i][j].contenido = CAJA;
        par->t.c[i][j].caja_en_objetivo = false;
        par->t.cajas_fuera++;
      }
      else if(tablero[i][j] == JUGADOR){      //booleano de caja a false
        par->t.c[i][j].tipo = SUELO;
        par->t.c[i][j].contenido = JUGADOR;
        par->t.c[i][j].jugador_encima_objetivo = false;
        par->jug_x = i;
        par->jug_y = j;
      }
      else if(tablero[i][j] == GOAL){
        par->t.c[i][j].tipo = GOAL;
        par->t.c[i][j].contenido = GOAL;
        par->t.c[i][j].jugador_encima_objetivo = false;
        par->t.c[i][j].caja_en_objetivo = false;
      }
      else if(tablero[i][j] == SUELO){
        par->t.c[i][j].tipo = SUELO;
        par->t.c[i][j].contenido = SUELO;
        par->t.c[i][j].jugador_encima_objetivo = false;
        par->t.c[i][j].caja_en_objetivo = false;
      }
      else if(tablero[i][j] == PARED){
        par->t.c[i][j].tipo = PARED;
        par->t.c[i][j].contenido = PARED;
        par->t.c[i][j].jugador_encima_objetivo = false;
        par->t.c[i][j].caja_en_objetivo = false;
      } 
    }
  }
}

void imprimir_tablero(partida p){
  printf("Pulse las teclas para moverte. Restart 'r'. Quit 'q'.\n");
  printf_color(GREEN);
  printf("Nivel: Nivel Medio.\n");
  printf_color(WHITE);
  p.t.cajas_dentro = 0;
  p.t.cajas_fuera = 0;
  for(int i = 0; i < MAX_F; i++){
    for(int j = 0; j < MAX_C; j++){
      if(p.t.c[i][j].contenido == CAJA) ++p.t.cajas_fuera;
      if(p.t.c[i][j].tipo == GOAL){
        if(p.t.c[i][j].caja_en_objetivo){
           ++p.t.cajas_dentro;
           --p.t.cajas_fuera;
        }
      }
    }
  }

  printf("goles: %d    cajas en goles: %d\nnum_pasos: %d   num_empujes: %d\n",p.t.cajas_fuera,p.t.cajas_dentro,p.t.movimientos,p.t.empujones);
  for(int i = 0; i < MAX_F; i++){
    for(int j = 0; j < MAX_C; j++){
      if(p.t.c[i][j].tipo == PARED){
        printf_color(RED);
        printf("%c", PARED);
      }
      else if(p.t.c[i][j].tipo == GOAL){
        if(p.t.c[i][j].caja_en_objetivo){
           printf_color(YELLOW);
           printf("%c",CAJA_COMPLET);
        }
        else if(p.t.c[i][j].jugador_encima_objetivo){
          printf_color(BOLD_CYAN);
          printf("%c",JUGADOR_CAJA);
        }
        else {
          printf_color(BOLD_CYAN);
          printf("%c",GOAL);
        }
      }
      else if(p.t.c[i][j].tipo == SUELO){
        if(p.t.c[i][j].contenido == JUGADOR){
          printf_color(BOLD_GREEN);
          printf("%c",JUGADOR);
        }
        else if(p.t.c[i][j].contenido == CAJA){
          printf_color(BOLD_YELLOW);
          printf("%c",CAJA);
        }
        else{
          printf_color(WHITE);
          printf("%c",SUELO);
        }
      }
    }
    printf("\n");
  }
  if(p.t.cajas_fuera == 0) printf("HAS GANADO");
}


bool mover(partida *p, int tecla){
  int posx = p->jug_x;
  int posy = p->jug_y;
  bool res;
  


  if(tecla == 1){
    if(p->t.c[posx-1][posy].tipo != PARED){  
      if(p->t.c[posx-1][posy].contenido == SUELO){
        res = mover_jugador(p, tecla);
      }
      if(p->t.c[posx-1][posy].contenido == CAJA && p->t.c[posx-2][posy].contenido == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx-1][posy].contenido == CAJA && p->t.c[posx-2][posy].contenido == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      
      else if(p->t.c[posx-1][posy].contenido == CAJA && p->t.c[posx-1][posy].caja_en_objetivo && p->t.c[posx-2][posy].contenido == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx-1][posy].contenido == CAJA && p->t.c[posx-1][posy].caja_en_objetivo && p->t.c[posx-2][posy].contenido == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
      else if((p->t.c[posx-1][posy].contenido == GOAL && !p->t.c[posx-1][posy].caja_en_objetivo)){
        res = mover_jugador_objetivo(p, tecla);
      }
    }
  }
  else if(tecla == 2){
    if(p->t.c[posx+1][posy].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx+1][posy].contenido == CAJA && p->t.c[posx+2][posy].contenido == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx+1][posy].contenido == CAJA && p->t.c[posx+2][posy].contenido == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx+1][posy].contenido == SUELO){
        res = mover_jugador(p, tecla);
      }
      else if(p->t.c[posx+1][posy].contenido == CAJA && p->t.c[posx+1][posy].caja_en_objetivo && p->t.c[posx+2][posy].contenido == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx+1][posy].contenido == CAJA && p->t.c[posx+1][posy].caja_en_objetivo && p->t.c[posx+2][posy].contenido == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
      else if((p->t.c[posx+1][posy].contenido == GOAL && !p->t.c[posx+1][posy].caja_en_objetivo)){
        res = mover_jugador_objetivo(p, tecla);
      }
    }
  }
  else if(tecla == 3){
    if(p->t.c[posx][posy-1].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx][posy-1].contenido == CAJA && p->t.c[posx][posy-2].contenido == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx][posy-1].contenido == CAJA && p->t.c[posx][posy-2].contenido == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx][posy-1].contenido == SUELO){     //No llegeix el espai
        res = mover_jugador(p, tecla);  //
      }
      else if(p->t.c[posx][posy-1].contenido == CAJA && p->t.c[posx][posy-1].caja_en_objetivo && p->t.c[posx][posy-2].contenido == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx][posy-1].contenido == CAJA && p->t.c[posx][posy-1].caja_en_objetivo && p->t.c[posx][posy-2].contenido == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
      else if((p->t.c[posx][posy-1].contenido == GOAL && !p->t.c[posx][posy-1].caja_en_objetivo)){
        res = mover_jugador_objetivo(p, tecla);
      }
    }
  }
  else if(tecla == 4){
    if(p->t.c[posx][posy+1].tipo != PARED){           //Si hacia arriba no tenemos pared
      if(p->t.c[posx][posy+1].contenido == CAJA && p->t.c[posx][posy+2].contenido == SUELO){  //Si lo de encima es caja y lo siguiente suelo
        res = mover_jugador_caja(p, tecla);
      }
      else if(p->t.c[posx][posy+1].contenido == CAJA && p->t.c[posx][posy+2].contenido == GOAL){
        res = mover_jugador_caja_obj(p, tecla);
      }
      else if(p->t.c[posx][posy+1].contenido == SUELO){
        res = mover_jugador(p, tecla);
      }
      else if(p->t.c[posx][posy+1].contenido == CAJA && p->t.c[posx][posy+1].caja_en_objetivo && p->t.c[posx][posy+2].contenido == SUELO){
        res = mover_caja_fueraobj(p, tecla);
      }
      else if(p->t.c[posx][posy+1].contenido == CAJA && p->t.c[posx][posy+1].caja_en_objetivo && p->t.c[posx][posy+2].contenido == GOAL){
        res = mover_caja_entreobj(p, tecla);
      }
      else if((p->t.c[posx][posy+1].contenido == GOAL && !p->t.c[posx][posy+1].caja_en_objetivo)){
        res = mover_jugador_objetivo(p, tecla);
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
    p->t.c[posx-1][posy].contenido = JUGADOR;
    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->t.c[posx][posy].caja_en_objetivo = false;
    p->jug_x--;
  }
  else if(t == 2){
    p->t.c[posx+1][posy].contenido = JUGADOR;
    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->t.c[posx][posy].caja_en_objetivo = false;
    p->jug_x++;

  }
  else if(t == 3){
    p->t.c[posx][posy-1].contenido = JUGADOR;
    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->t.c[posx][posy].caja_en_objetivo = false;
    p->jug_y--;
  }
  else if(t == 4){
    p->t.c[posx][posy+1].contenido = JUGADOR;
    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->t.c[posx][posy].caja_en_objetivo = false;
    p->jug_y++;
  }
  p->t.movimientos++;
  return true;
}


bool mover_jugador_caja(partida *p, int t){
  int posx = p->jug_x;
  int posy = p->jug_y;

  if(t == 1){
    p->t.c[posx-2][posy].contenido = CAJA;
    p->t.c[posx-2][posy].caja_en_objetivo = false;

    p->t.c[posx-1][posy].caja_en_objetivo = false;
    p->t.c[posx-1][posy].contenido = JUGADOR;
    if(p->t.c[posx-1][posy].tipo == SUELO){
        p->t.c[posx-1][posy].jugador_encima_objetivo = false;
    }
    else p->t.c[posx-1][posy].jugador_encima_objetivo = true;

    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->jug_x--;
  }
  else if(t == 2){
    p->t.c[posx+2][posy].contenido = CAJA;
    p->t.c[posx+2][posy].caja_en_objetivo = false;

    p->t.c[posx+1][posy].caja_en_objetivo = false;
    p->t.c[posx+1][posy].contenido = JUGADOR;
    if(p->t.c[posx+1][posy].tipo == SUELO){
        p->t.c[posx+1][posy].jugador_encima_objetivo = false;
    }
    else p->t.c[posx+1][posy].jugador_encima_objetivo = true;

    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->jug_x++;
  }
  else if(t == 3){
    p->t.c[posx][posy-2].contenido = CAJA;
    p->t.c[posx][posy-2].caja_en_objetivo = false;

    p->t.c[posx][posy-1].caja_en_objetivo = false;
    p->t.c[posx][posy-1].contenido = JUGADOR;
    if(p->t.c[posx][posy-1].tipo == SUELO){
        p->t.c[posx][posy-1].jugador_encima_objetivo = false;
    }
    else p->t.c[posx][posy-1].jugador_encima_objetivo = true;

    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
    p->jug_y--;
  }
  else if(t == 4){
    p->t.c[posx][posy+2].contenido = CAJA;
    p->t.c[posx][posy+2].caja_en_objetivo = false;

    p->t.c[posx][posy+1].caja_en_objetivo = false;
    p->t.c[posx][posy+1].contenido = JUGADOR;
    if(p->t.c[posx][posy+1].tipo == SUELO){
        p->t.c[posx][posy+1].jugador_encima_objetivo = false;
    }
    else p->t.c[posx][posy+1].jugador_encima_objetivo = true;

    p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
    p->t.c[posx][posy].jugador_encima_objetivo = false;
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
      p->t.c[posx-2][posy].contenido = CAJA;
      p->t.c[posx-2][posy].caja_en_objetivo = true;

      p->t.c[posx-1][posy].caja_en_objetivo = false;
      if(p->t.c[posx-1][posy].tipo == GOAL){
          p->t.c[posx-1][posy].jugador_encima_objetivo = true;
      }
      else p->t.c[posx-1][posy].jugador_encima_objetivo = false;
      p->t.c[posx-1][posy].contenido = JUGADOR;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;

      p->jug_x--;

    }
    else if(t == 2){
      p->t.c[posx+2][posy].contenido = CAJA;
      p->t.c[posx+2][posy].caja_en_objetivo = true;

      p->t.c[posx+1][posy].caja_en_objetivo = false;
      if(p->t.c[posx+1][posy].tipo == GOAL){
          p->t.c[posx+1][posy].jugador_encima_objetivo = true;
      }
      else p->t.c[posx+1][posy].jugador_encima_objetivo = false;
      p->t.c[posx+1][posy].contenido = JUGADOR;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;

      p->jug_x++;
 
    }
    else if(t == 3){
      p->t.c[posx][posy-2].contenido = CAJA;
      p->t.c[posx][posy-2].caja_en_objetivo = true;

      p->t.c[posx][posy-1].caja_en_objetivo = false;
      if(p->t.c[posx][posy-1].tipo == GOAL){
          p->t.c[posx][posy-1].jugador_encima_objetivo = true;
      }
      else p->t.c[posx][posy-1].jugador_encima_objetivo = false;
      p->t.c[posx][posy-1].contenido = JUGADOR;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;

      p->jug_y--;

    }
    else if(t == 4){
      p->t.c[posx][posy+2].contenido = CAJA;
      p->t.c[posx][posy+2].caja_en_objetivo = true;

      p->t.c[posx][posy+1].caja_en_objetivo = false;
      if(p->t.c[posx][posy+1].tipo == GOAL){
          p->t.c[posx][posy+1].jugador_encima_objetivo = true;
      }
      else p->t.c[posx][posy+1].jugador_encima_objetivo = false;
      p->t.c[posx][posy+1].contenido = JUGADOR;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->jug_y++;

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
      p->t.c[posx-2][posy].contenido = CAJA;
      p->t.c[posx-2][posy].caja_en_objetivo = true;

      p->t.c[posx-1][posy].contenido = JUGADOR;
      p->t.c[posx-1][posy].jugador_encima_objetivo = true;
      p->t.c[posx-1][posy].caja_en_objetivo = false;

      p->t.c[posx][posy].tipo = p->t.c[posx][posy].contenido;
      p->jug_x--;

      
    }
    else if(t == 2){
      p->t.c[posx+2][posy].contenido = CAJA;
      p->t.c[posx+2][posy].caja_en_objetivo = true;

      p->t.c[posx+1][posy].contenido = JUGADOR;
      p->t.c[posx+1][posy].jugador_encima_objetivo = true;
      p->t.c[posx+1][posy].caja_en_objetivo = false;

      p->t.c[posx][posy].tipo = p->t.c[posx][posy].contenido;
      p->jug_x++;

    }
    else if(t == 3){
      p->t.c[posx][posy-2].contenido = CAJA;
      p->t.c[posx][posy-2].caja_en_objetivo = true;

      p->t.c[posx][posy-1].contenido = JUGADOR;
      p->t.c[posx][posy-1].jugador_encima_objetivo = true;
      p->t.c[posx][posy-1].caja_en_objetivo = false;

      p->t.c[posx][posy].tipo = p->t.c[posx][posy].contenido;
      p->jug_y--;

    }
    else if(t == 4){
      p->t.c[posx][posy+2].contenido = CAJA;
      p->t.c[posx][posy+2].caja_en_objetivo = true;

      p->t.c[posx][posy+1].contenido = JUGADOR;
      p->t.c[posx][posy+1].jugador_encima_objetivo = true;
      p->t.c[posx][posy+1].caja_en_objetivo = false;

      p->t.c[posx][posy].tipo = p->t.c[posx][posy].contenido;
      p->jug_y++;
   
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
      p->t.c[posx-2][posy].contenido = CAJA;
      p->t.c[posx-2][posy].caja_en_objetivo = true;

      p->t.c[posx-1][posy].contenido = JUGADOR;
      p->t.c[posx-1][posy].jugador_encima_objetivo = true;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->t.c[posx][posy].jugador_encima_objetivo = false;
      p->t.c[posx][posy].caja_en_objetivo = false;
      

      p->jug_x--;
    }
    else if(t == 2){
     p->t.c[posx+2][posy].contenido = CAJA;
      p->t.c[posx+2][posy].caja_en_objetivo = true;

      p->t.c[posx+1][posy].contenido = JUGADOR;
      p->t.c[posx+1][posy].jugador_encima_objetivo = true;
      p->t.c[posx+1][posy].caja_en_objetivo = false;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->t.c[posx][posy].jugador_encima_objetivo = false;


      p->jug_x++;
    }
    else if(t == 3){
      p->t.c[posx][posy-2].contenido = CAJA;
      p->t.c[posx][posy-2].caja_en_objetivo = true;

      p->t.c[posx][posy-1].contenido = JUGADOR;
      p->t.c[posx][posy-1].jugador_encima_objetivo = true;
      p->t.c[posx][posy-1].caja_en_objetivo = false;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->t.c[posx][posy].jugador_encima_objetivo = false;

      p->jug_y--;
    }
    else if(t == 4){
       p->t.c[posx][posy+2].contenido = CAJA;
      p->t.c[posx][posy+2].caja_en_objetivo = true;

      p->t.c[posx][posy+1].contenido = JUGADOR;
      p->t.c[posx][posy+1].jugador_encima_objetivo = true;
      p->t.c[posx][posy+1].caja_en_objetivo = false;

      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->t.c[posx][posy].jugador_encima_objetivo = false;

      p->jug_y++;
    }
    p->t.empujones++;
    p->t.movimientos++;
    return true;
}

bool mover_jugador_objetivo(partida *p, int t){
    int posx = p->jug_x;
    int posy = p->jug_y;

    //Tecla hacia arriba

    if(t == 1){
      p->t.c[posx-1][posy].contenido = JUGADOR;
      p->t.c[posx-1][posy].jugador_encima_objetivo = true;

      p->t.c[posx][posy].jugador_encima_objetivo = false;
      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->jug_x--;
      
    }
    else if(t == 2){
      p->t.c[posx+1][posy].contenido = JUGADOR;
      p->t.c[posx+1][posy].jugador_encima_objetivo = true;

      p->t.c[posx][posy].jugador_encima_objetivo = false;
      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->jug_x++;
      

    }
    else if(t == 3){
      p->t.c[posx][posy-1].contenido = JUGADOR;
      p->t.c[posx][posy-1].jugador_encima_objetivo = true;

      p->t.c[posx][posy].jugador_encima_objetivo = false;
      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->jug_y--;
      

    }
    else if(t == 4){
      p->t.c[posx][posy+1].contenido = JUGADOR;
      p->t.c[posx][posy+1].jugador_encima_objetivo = true;

      p->t.c[posx][posy].jugador_encima_objetivo = false;
      p->t.c[posx][posy].contenido = p->t.c[posx][posy].tipo;
      p->jug_y++;
     
      
    }
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
      if(pos == 6){
        empezar_partida(&p, tab);
      }
    }
}
