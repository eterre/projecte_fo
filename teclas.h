// Este fichero se le da al alumno
// Testeado con Linux, Mac y Windows con DevC++ (que utiliza MinGw)

#ifndef TECLAS_H
#define TECLAS_H
// https://msdn.microsoft.com/en-us/library/aa299374(VS.60).aspx
// http://www.lagmonster.org/docs/DOS7/v-ansi-keys.html

#define UP	1
#define DOWN	2
#define LEFT	3
#define RIGHT	4
#define CANCEL	5
#define RESTART	6
#define CLEAR	7
#define OTHER	-1

#if defined(_WIN32) || defined(_WIN64) // WINDOWS
#define WIN_ARROW	0	// In arrow keyboard (0 and then the arrow)
#define WIN_EXTENDED	224	// In extended keyboard (224 and the arrow)
#define WIN_ESC		1	// ESC
/*
 * Compilando con DevC++ que utiliza MinGw.
 * No con compilador nativo para windows.
 */
#define WIN_C		'c'	// c ClearScreen
#define WIN_R		'r'	// r Restart level
#define WIN_Q		'q'	// q Quit game
#define WIN_O		'o'	// o Right
#define WIN_P		'p'	// p Left
#define WIN_A		'a'	// a Up
#define WIN_Z		'z'	// z Down
/*
 * Se podria dar el caso de que se tubieran que usar estos defines
 * con otro compilador:
#define WIN_C		46	// c ClearScreen
#define WIN_R		19	// r Restart level
#define WIN_Q		16	// q Quit game
*/
#define WIN_UP		72
#define WIN_LEFT	75
#define WIN_RIGHT	77
#define WIN_DOWN	80
#else		// LINUX
#define LINUX_CANCEL	3	// Ctrl+C
#define LINUX_STOP	26	// Ctrl+Z
#define LINUX_ESC	27	// Ctrl+[ because ^[A UP .. ^[D LEFT
#define LINUX_BRACKET	'['	// Not really used
#define LINUX_UP	'A'
#define LINUX_DOWN	'B'
#define LINUX_RIGHT	'C'
#define LINUX_LEFT	'D'
#define LINUX_C		'c'	// c ClearScreen
#define LINUX_Q		'q'	// r Restart level
#define LINUX_R		'r'	// q Quit game
#define LINUX_O		'o'	// o Right
#define LINUX_P		'p'	// p Left
#define LINUX_A		'a'	// a Up
#define LINUX_Z		'z'	// z Down
/*
#define LINUX_CANCEL	3	// Ctrl+C
#define LINUX_STOP	26	// Ctrl+Z
#define LINUX_ESC	27	// ^[A UP .. ^[D LEFT
#define LINUX_BRACKET	91	// Not used
#define LINUX_UP	65
#define LINUX_DOWN	66
#define LINUX_RIGHT	67
#define LINUX_LEFT	68
#define LINUX_Q		113	// r Restart level
#define LINUX_R		114	// q Quit game
*/
#endif // WIN

void borrar_pantalla();
int lee_tecla();

#endif // TECLAS_H

