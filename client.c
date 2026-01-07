#include "networkstructure.h"

void view(){
  FILE* r_file = fopen("messages.txt", "r");
  char buff[128];
  while(fgets(buff, sizeof(buff), r_file) != NULL){
    buff[strcspn(buff,"\n")] = '\0';
    printf("%s ", buff);
  }
  printf("\n");
  fclose(r_file);
}


void clientLogic(int server_socket){
  char buf[1024];
  printf("Enter a message: \n");
  if (fgets(buf, 1024, stdin) == NULL) {
    close(server_socket);
    printf("Client closed\n");
    exit(0);
  }
  send(server_socket, buf, strlen(buf), 0);
  int n = recv(server_socket, buf, 1024, 0);
  if (n==0) {
    close(server_socket);
    printf("Client closed\n");
    exit(0);
  }
  buf[n] = '\0';
  printf("recieved: '%s'\n", buf);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  while(1) {
    view();
    clientLogic(server_socket);
  }
}
