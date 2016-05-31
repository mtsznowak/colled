#include "server.h"
#include "server_sockets.h"


int main(int argc, char **argv){
  if (argc != 3){
    printf("Usage: ./colled_server file_path port\n");
    exit(1);
  }

  initializeServerSocket(atoi(argv[2]));
  initializePollFD();
  atexit(colseSockets);

  while(1){
    checkForNewClients();
    
    char *message = checkForMessage();
    if (message != NULL){
      printf("%s\n", message);
    }
  }

  return 0;
}