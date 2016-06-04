#include "client_sockets.h"

int csocket;
struct sockaddr *address;

char *getMessage(){
  char *buffer = malloc(256);
  if (recv(csocket, buffer, 255, 0) > 0)
    return buffer;
  return NULL;
}

int initializeClientSocket(char* ip, int port){
  if ((csocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    perror("socket");

  struct sockaddr_in addr, client_addr;
  addr.sin_family = AF_INET;
  inet_aton(ip, (struct in_addr *)&addr.sin_addr.s_addr);
  addr.sin_port = htons(port);
  address = (struct sockaddr *)&addr;

  memset(&client_addr, 0, sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = INADDR_ANY;
  client_addr.sin_port = 0;
  bind(csocket, (struct sockaddr *) &client_addr, sizeof(client_addr));

  if (connect(csocket, address, sizeof(struct sockaddr_in))<0)
    perror("connectINET");
  return csocket;
}

void sendMessage(char *buffer){
  send(csocket, buffer, strlen(buffer), 0);
}

void closeSockets(){
  close(csocket);
}