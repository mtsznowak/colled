#include "editor.h"

char **content;
int allocated = 0;
int lines = 0;
int lowerbound = 0;
int x=3;
int y=3;

void curses_init(){
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
}

void addLine(char* line){
  if (allocated < lines + 1){
    content = realloc(content, (lines*2+1)*sizeof(char*));
    allocated = lines*2+1;
  }
  content[lines] = malloc(strlen(line)+1);
  strcpy(content[lines],line);
  lines++;
}

void printBuff()
{
  int lc = 0;
  for(int i=lowerbound; lc < LINES-1; i++){
    if(i < lines)
      mvprintw(lc, 0, content[i]);
    clrtoeol();
    lc++;
  }
  move(y, x);
  refresh();
}

void moveCursor(int a, int b){
  y+=a;
  x+=b;
  move(y, x);
  refresh();
}
