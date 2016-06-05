#include "client_sockets.h"

int csocket;
struct sockaddr *address;

char *getMessage(){
  char r = 0;
  recv(csocket, &r, 1, 0);
  char *buffer = malloc(r+2);
  r--;
  if (r == 0){
    buffer[0] = 0;
    return buffer;
  }
  if ((recv(csocket, buffer, (int)r, 0)) > 0){
    buffer[(int)r] = 0;
    return buffer;
  }
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

void sendMessage(char c, int y, int x){
  char buffer[3];
  buffer[0] = c;
  buffer[1] = (char)y;
  buffer[2] = (char)x;
  if (send(csocket, buffer, 3, 0) < 0)
    perror("send");
}

void closeSockets(){
  close(csocket);
  exit(0);
}