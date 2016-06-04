#include "server_sockets.h"

socklen_t socksize = sizeof(struct sockaddr_in);
struct sockaddr_in ad;

struct pollfd isocket;
struct pollfd clients[MAXCLIENTS];
int nextc = 0;


char *checkForMessage(){
  if (poll(clients, nextc, 1000)>0){
    for (int i=0; i<MAXCLIENTS; i++){
      if (clients[i].revents & POLLRDNORM){
        char *buffer = malloc(255);
        if (recv(clients[i].fd, buffer, 255, 0) > 0)
          return buffer;
        else
          deleteClient(i);
      }
    }
  }
  return NULL;
}

void closeSockets(){
  for (int i=0; i<MAXCLIENTS; i++)
    if (clients[i].fd != 0)
      close(clients[i].fd);
  close(isocket.fd);
}

void initializeServerSocket(int port){
  if ((isocket.fd = socket(PF_INET, SOCK_STREAM, 0))<0) 
    perror("socket");

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  if (bind(isocket.fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) < 0)
    perror("bind");
  listen(isocket.fd, 0);

  isocket.events = POLLRDNORM;
}

void initializePollFD(){
  for (int i=0; i<MAXCLIENTS; i++){
    clients[i].fd = 0;
    clients[i].events = POLLRDNORM;
  }
}

int checkForNewClients(){
  if (poll(&isocket, 1, 20) != 0){
      if (isocket.revents & POLLRDNORM){
        clients[nextc++].fd = accept4(isocket.fd, (struct sockaddr *)&ad, &socksize, SOCK_NONBLOCK);
        return nextc-1;
      }
    }
  return -1;
}

void deleteClient(int i){
  close(clients[i].fd);
  clients[i].fd = clients[--nextc].fd;
}

void sendMessage(char *buffer, int i){
  send(clients[i].fd, buffer, strlen(buffer), 0);
};