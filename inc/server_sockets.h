#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/types.h>  
#include <stdlib.h>

#define MAXCLIENTS 50

void colseSockets();
void initializeServerSocket(int);
void initializePollFD();
void checkForNewClients();
char *checkForMessage();