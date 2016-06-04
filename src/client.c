#include "client.h"
#include "client_sockets.h"

void handle_input(){
  
}

int main(int argc, char **argv){
  if (argc != 3){
    printf("Usage: ./colled_client address port\n");
    exit(1);
  }

  struct pollfd fds[2];

  fds[0].fd = initializeClientSocket(argv[1], atoi(argv[2]));
  fds[0].events = POLLIN;

  fds[1].fd = 0;
  fds[1].events = POLLIN;

  atexit(closeSockets);

  while(1){
    if (poll(fds, 2, -1) > 0){

      if (fds[0].revents & POLLIN){
        char *message;
        message = getMessage();
        if (message == NULL){
          printf("Error. Exiting.\n");
          exit(1);
        }
      }

      if (fds[1].revents & POLLIN)
        handle_input();
    }
  }
  return 0;

}