#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void initialize_file_access(char *);
void save_close_file();
void update_file();
void set_line(int, char*);