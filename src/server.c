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
    char* message = listenForMessages();
    if (message > (char*)1){
      printf("message\n");
    }else if (message == (char*)1){
      printf("new client\n");
      int ind = getClientsNumber();
      for (int i=0; i<getLinesCount(); i++)
        sendMessage(getLine(i),ind);
    }
    fflush(stdout);
  }

  return 0;
}