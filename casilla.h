#ifndef casilla_h
#define casilla_h

#define JUGADOR '@'
#define CAJA '$'
#define PARED '#'
#define CAJA_COMPLET '*'
#define JUGADOR_CAJA '+'
#define GOAL '.'
#define SUELO ' '

typedef struct{
    char tipo;          //tipo de objeto en la casilla
}casilla;


#endif
