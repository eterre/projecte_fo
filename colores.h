// Este fichero se le da al alumno
#ifndef COLORES_H
#define	COLORES_H

// http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
// http://ascii-table.com/ansi-escape-sequences.php

// Posibles valores del argumento color para la funcion printf_color()
#define RED		0
#define GREEN		1
#define YELLOW		2
#define BLUE		3
#define MAGENTA		4
#define CYAN		5
#define WHITE		6
#define BOLD_RED	7
#define BOLD_GREEN	8
#define BOLD_YELLOW	9
#define BOLD_BLUE	10
#define BOLD_MAGENTA	11
#define BOLD_CYAN	12
#define BOLD_WHITE	13

/*
 * Despues de llamar a printf_color() con un color determinado,
 * todo lo que imprimimamos por pantalla apareceran en ese color.
 */
void printf_color(int color);

/*
 * Despues de llamar a printf_reset_color() todo lo que imprimimamos
 * por pantalla aparecera en el color por defecto del terminal.
 */
void printf_reset_color();

// void clear_screen();

#endif	/* COLORES_H */

