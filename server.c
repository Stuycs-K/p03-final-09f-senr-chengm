#include "networkstructure.h"
#include "shared.h"
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


void subserver_logic(int client_socket){
  char buf[1024];
  while(1) {
    int n = recv(client_socket, buf, 1024, 0);
    if (n == 0) {
      close(client_socket);
      printf("Socket closed\n");
      exit(0);
    }
    buf[n-1] = '\0';
    printf("'%s'\n", buf);
    send(client_socket, buf, n, 0);
  }
}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();
  while(1) {
    int client_socket = server_tcp_handshake(listen_socket);
    pid_t f = fork();
    if (f == 0) {
      char buf[1024];
      close(listen_socket);
      int n = recv(client_socket, buf, 1024, 0);
      if (n == 0) {
        close(client_socket);
        printf("Socket closed\n");
        exit(0);
      }
      int fd = open("messages.txt", O_WRONLY );
      write(fd, buf, n);
      buf[n-1] = '\0';
      printf("'%s'\n", buf);
      subserver_logic(client_socket);
      close(client_socket);
      exit(0);
    } else {
      close(client_socket);
    }
  }
}
