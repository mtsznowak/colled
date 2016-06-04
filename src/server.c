#include "server.h"
#include "server_sockets.h"
#include "file_utils.h"

void oexit(){
  closeSockets();
  saveCloseFile();
  exit(0);
}

int main(int argc, char **argv){
  if (argc != 3){
    printf("Usage: ./colled_server file_path port\n");
    exit(1);
  }
  initializeFileAccess(argv[1]);
  initializeServerSocket(atoi(argv[2]));
  initializePollFD();
  signal(SIGINT, oexit);
  
  while(1){
    int q;
    if ((q = checkForNewClients())!= -1)
      {}//sendMessage(file, q);

    char *message = checkForMessage();
    if (message != NULL){
      printf("%s\n", message);
    }
  }

  return 0;
}