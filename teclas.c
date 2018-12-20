// Este fichero se le da al alumno
// Testeado con Linux, Mac y Windows con DevC++ (que utiliza MinGw)
 
// Si dice algo como "conio.h no such header file" mirar:
	// https://helloacm.com/modern-getch-implementation-on-windows-cc/
// https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
#include <stdio.h>	// for getchar();
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>	// for getch();
#else // LINUX
#include <stdlib.h>	// for system("/bin/stty raw");
#endif
#include "teclas.h"

void borrar_pantalla() {
// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
#if defined(__linux__)
	// This will work on ANSI terminals, demands POSIX
	printf("\e[1;1H\e[2J");
	// seguro que es mas rapido que una llamada a sistema. Me pregunto si
	// tambien funcionaria para "defined(__unix__) || defined(__APPLE__)"
#endif

#if defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}

int lee_tecla() {
	int res;

#if defined(_WIN32) || defined(_WIN64)
	// printf("[WINDOWS]\n");
	unsigned char tecla;

	tecla = getch();
	if (tecla == WIN_ARROW || tecla == WIN_EXTENDED) {
		tecla = getch();
		switch (tecla) {
			case WIN_UP:
				res = UP;
				break;
			case WIN_DOWN:
				res = DOWN;
				break;
			case WIN_LEFT:
				res = LEFT;
				break;
			case WIN_RIGHT:
				res = RIGHT;
				break;
			default:
				// printf("[WIN_OTHER1 %u]", tecla);
				res = OTHER;
		}
	} else {
		switch (tecla) {
			case WIN_C:
				res = CLEAR;
				break;
			case WIN_R:
				res = RESTART;
				break;
			case WIN_ESC:
			case WIN_Q:
				res = CANCEL;
				break;
			case WIN_A:
				res = UP;
				break;
			case WIN_Z:
				res = DOWN;
				break;
			case WIN_O:
				res = LEFT;
				break;
			case WIN_P:
				res = RIGHT;
				break;
			default:
				// printf("[WIN_OTHER2 %u]", tecla);
				res = OTHER;
		}
	}
#else // !WIN
	// printf("[LINUX]\n");
	int input;

	system("/bin/stty raw");
	input = getchar();
	// printf("[%d]", input);
	switch (input) {
		case LINUX_ESC:
			getchar();
			input = getchar();
			switch (input) {
				case LINUX_UP:		// ^[A
					res = UP;
					break;
				case LINUX_DOWN:	// ^[B
					res = DOWN;
					break;
				case LINUX_RIGHT:	// ^[C
					res = RIGHT;
					break;
				case LINUX_LEFT:	// ^[D
					res = LEFT;
					break;
				default:
					// printf("[LINUX_OTHER1 %d]", input);
					res = OTHER;
			}
			break;
		case LINUX_C:
			res = CLEAR;
			break;
		case LINUX_R:
			res = RESTART;
			break;
		case LINUX_Q:
		case LINUX_CANCEL:
		case LINUX_STOP:
			res = CANCEL;
			break;
		case LINUX_A:
			res = UP;
			break;
		case LINUX_Z:
			res = DOWN;
			break;
		case LINUX_P:
			res = RIGHT;
			break;
		case LINUX_O:
			res = LEFT;
			break;
		default:
			// printf("[LINUX_OTHER2 %d]", input);
			res = OTHER;
	}
	system("/bin/stty cooked");
#endif // WIN

	// printf("\n");
	return res;
}

