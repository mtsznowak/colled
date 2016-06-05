#include "server.h"
#include "server_sockets.h"
#include "file_utils.h"

void oexit(){
  closeSockets();
  saveCloseFile();
  exit(0);
}

void normalCharacter(char c, int y, int x){
  char *content = getLine(y);
  int linelen = strlen(content);
  content = realloc(content, linelen + 2);
  if (x < linelen){
    for (int i=linelen+1; i>x; i--)
      content[i] = content[i-1];
    content[x] = c;
  }else{
    content[linelen] = c;
    content[linelen+1] = '\0';
  }
  char* buff = malloc(linelen+3);
  strcpy(buff+2, content);
  buff[0] = 4;
  buff[1] = y;
  sendToAll(buff);
  free(buff);
}

void onPress(char c, int y, int x){
  switch(c){
    case('\n'):
      break;
    case('Y'): //backspace
      break;
    default:
      normalCharacter(c,y,x);
      break;
  }
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
      onPress(message[0], (int)message[1], (int)message[2]);
    }else if (message == (char*)1){
      printf("new client\n");
      int ind = getClientsNumber();
      for (int i=0; i<getLinesCount(); i++){
        char* line = getLine(i);
        char* buff = malloc(strlen(line)+2);
        strcpy(buff+1, line);
        buff[0] = 2;
        sendMessage(buff,ind);
        free(buff);
      }
    }
    fflush(stdout);
  }

  return 0;
}