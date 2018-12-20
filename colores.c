// Este fichero se le da al alumno
#include <stdio.h>
#include "colores.h"

// http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
// http://ascii-table.com/ansi-escape-sequences.php

// #define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BOLD    "\x1b[1m"

void printf_color(int color) {
	switch (color % 14) {
		case RED:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_RED    ); break;
		case GREEN:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_GREEN  ); break;
		case YELLOW:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_YELLOW ); break;
		case BLUE:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_BLUE   ); break;
		case MAGENTA:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_MAGENTA); break;
		case CYAN:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_CYAN   ); break;
		case WHITE:
			printf(ANSI_COLOR_RESET  ); printf(ANSI_COLOR_WHITE  ); break;
		case BOLD_RED:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_RED    ); break;
		case BOLD_GREEN:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_GREEN  ); break;
		case BOLD_YELLOW:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_YELLOW ); break;
		case BOLD_BLUE:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_BLUE   ); break;
		case BOLD_MAGENTA:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_MAGENTA); break;
		case BOLD_CYAN:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_CYAN   ); break;
		case BOLD_WHITE:
			printf(ANSI_COLOR_BOLD   ); printf(ANSI_COLOR_WHITE  ); break;
	}
}

void printf_reset_color() {
	printf(ANSI_COLOR_RESET);
}

/*
void clear_screen() {
	printf("\e[1;1H\e[2J");
}
*/
