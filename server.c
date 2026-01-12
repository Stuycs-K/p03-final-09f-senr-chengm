#include "networkstructure.h"



// void subserver_logic(int client_socket){
//   char buf[1024];
//   while(1) {
//     int n = recv(client_socket, buf, sizeof(buf)-1, 0);
//     if (n <= 0) {
//       close(client_socket);
//       printf("Socket closed\n");
//       exit(0);
//     }
//     buf[n] = '\0';
//     send(client_socket, buf, n, 0);
//   }
// }

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();

  int clients[100];
  int client_count = 0;

  fd_set read_fds;

  char buff[1024];


  while(1) {
    FD_ZERO(&read_fds);
    //add listen_socket and stdin to the set
    FD_SET(listen_socket, &read_fds);
    int fd_max = listen_socket;
    int client_socket = server_tcp_handshake(listen_socket);
    pid_t f = fork();
    if (f == 0) {
      char buf[1024];
      close(listen_socket);
      subserver_logic(client_socket);
      close(client_socket);
      exit(0);
    } else {
      close(client_socket);
    }
  }
}
