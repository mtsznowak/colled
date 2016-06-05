#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void initializeFileAccess(char *);
void saveCloseFile();
void updateFile();
int getLinesCount();
void setLine(int, char*);
char *getLine(int);