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
    char contenido;          //imprimir de objeto en la casilla
    char tipo;
    bool jugador_encima_objetivo;
    bool caja_en_objetivo;
}casilla;


#endif
