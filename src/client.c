#include "client.h"
#include "client_sockets.h"
#include "editor.h"

static struct termios old, new;
void initTermios(int echo) {
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}


void handle_input(){
  char c;
  switch(c=getchar()){
    case(56):
      moveCursor(-1,0);
      break;
    case(50):
      moveCursor(1,0);
      break;
    case(54):
      moveCursor(0,1);
      break;
    case(52):
      moveCursor(0,-1);
      break;
    default:
      sendMessage(c, getY()+1, getX()+1);
      moveCursor(0,1);
      break;
  }
}

void parse_message(char* message){
  if (message[0] == 2)
    addLine(message+1);
  if (message[0] == 4)
    setLine((int)message[1]-1, message+2);
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

  signal(SIGINT, closeSockets);

  initTermios(0);
  curses_init();
  while(1){
    if (poll(fds, 2, -1) > 0){
      if (fds[0].revents & POLLIN){
        char *message;
        message = getMessage();
        if (message == NULL){
          printf("Error. Exiting.\n");
          exit(1);
        }
        parse_message(message);
        free(message);
      }

      if (fds[1].revents & POLLIN)
        handle_input();
    }
    printBuff();
  }
  return 0;

}