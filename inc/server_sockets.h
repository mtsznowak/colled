#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/types.h>  
#include <stdlib.h>
#include <string.h>

#define MAXCLIENTS 50

void closeSockets();
void initializeServerSocket(int);
void initializePollFD();
int checkForNewClients();
char *checkForMessage();
void deleteClient(int);
void sendMessage(char *, int);
void sendMassageToAll(char *);