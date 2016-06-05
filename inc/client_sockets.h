#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/types.h>  
#include <stdlib.h>
#include <string.h>

int initializeClientSocket(char*, int);
void sendMessage(char c, int y, int x);
void closeSockets();
char *getMessage();