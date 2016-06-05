#include "server_sockets.h"

socklen_t socksize = sizeof(struct sockaddr_in);
struct sockaddr_in ad;

struct pollfd clients[MAXCLIENTS+1];
int nextc = 1;

int getClientsNumber(){
  return nextc - 1;
}

void deleteClient(int i){
  close(clients[i].fd);
  clients[i].fd = clients[--nextc].fd;
}

void closeSockets(){
  for (int i=0; i<MAXCLIENTS+1; i++)
    if (clients[i].fd != 0)
      close(clients[i].fd);
}

void initializeServerSocket(int port){
  if ((clients[0].fd = socket(PF_INET, SOCK_STREAM, 0))<0) 
    perror("socket");

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  if (bind(clients[0].fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) < 0)
    perror("bind");
  listen(clients[0].fd, 0);

  clients[0].events = POLLIN;
}

void initializePollFD(){
  for (int i=1; i<MAXCLIENTS+1; i++){
    clients[i].fd = 0;
    clients[i].events = POLLIN;
  }
}

void sendMessage(char *buffer, int i){
  char q = (char)strlen(buffer)+1;
  send(clients[i].fd, &q, 1, 0);
  if (q!=1)send(clients[i].fd, buffer, strlen(buffer), 0);
};

void sendToAll(char* buffer){
  for (int i=1; i<nextc; i++)
    sendMessage(buffer, i);
}

char* listenForMessages(){
  if (poll(clients, nextc, -1)>0){

    if (clients[0].revents & POLLIN){
      clients[nextc++].fd = accept4(clients[0].fd, (struct sockaddr *)&ad, &socksize, SOCK_NONBLOCK);
      return (char*)1;
    }

    for (int i=1; i<nextc; i++){
      if (clients[i].revents & POLLIN){
        char *buffer = malloc(3);
        if (recv(clients[i].fd, buffer, 3, 0) > 0)
          return buffer;
        else
          deleteClient(i);
      }
    }
  }
  return NULL;
}