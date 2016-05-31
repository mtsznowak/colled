#include "client.h"
#include "client_sockets.h"

int main(int argc, char **argv){
  if (argc != 3){
    printf("Usage: ./colled_client address port\n");
    exit(1);
  }

  initializeClientSocket(argv[1], atoi(argv[2]));
  atexit(closeSockets);


  while(1){
    char *message = checkForMessage();
    if (message != NULL) 
      printf("%s\n", message);
  }
  return 0;

}