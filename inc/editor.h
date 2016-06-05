#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


void addLine(char*);
char* getLine(int);
void setLine(int, char*);
void curses_init();
void printBuff();
void moveCursor(int, int);
int getX();
int getY();
