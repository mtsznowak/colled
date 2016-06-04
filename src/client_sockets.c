#include "client_sockets.h"

struct pollfd csocket;
struct sockaddr *address;

char *checkForMessage(int len){
  if (poll(&csocket, 1, 1000)>0){
    char *buffer = malloc(len+1);
    if (recv(csocket.fd, buffer, len, 0) > 0)
      return buffer;
  }
  return NULL;
}

void initializeClientSocket(char* ip, int port){
  if ((csocket.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
  bind(csocket.fd, (struct sockaddr *) &client_addr, sizeof(client_addr));

  if (connect(csocket.fd, address, sizeof(struct sockaddr_in))<0)
    perror("connectINET");

  csocket.events = POLLRDNORM;
}

void sendMessage(char *buffer){
  send(csocket.fd, buffer, strlen(buffer), 0);
}

void closeSockets(){
  close(csocket.fd);
}