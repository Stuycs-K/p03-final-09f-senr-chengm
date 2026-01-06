#include "networking.h"
#include <signal.h>

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
      close(listen_socket);
      subserver_logic(client_socket);
      close(client_socket);
      exit(0);
    } else {
      close(client_socket);
    }
  }
}
