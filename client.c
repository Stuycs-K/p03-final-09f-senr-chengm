#include "networkstructure.h"


// void clientLogic(int server_socket){
//   char buf[1024];
//   printf("Enter a message: \n");
//   if (fgets(buf, 1024, stdin) == NULL) {
//     close(server_socket);
//     printf("Client closed\n");
//     exit(0);
//   }
//   send(server_socket, buf, strlen(buf), 0);
//   int n = recv(server_socket, buf, 1024, 0);
//   if (n==0) {
//     close(server_socket);
//     printf("Client closed\n");
//     exit(0);
//   }
//   buf[n] = '\0';
//   printf("recieved: '%s'\n", buf);
// }

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");

  fd_set read_fds;
  char buf[1024];
  // printf("Enter a username: \n");
  // if (fgets(buf, 1024, stdin) == NULL) {
  //   close(server_socket);
  //   printf("Client closed\n");
  //   exit(0);
  // }
  // send(server_socket, buf, strlen(buf), 0);
  while(1) {
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket, &read_fds);

    int maxfd = STDIN_FILENO;
    if(server_socket > maxfd){
      maxfd = server_socket;
    }

    select(maxfd + 1, &read_fds, NULL, NULL, NULL);
    if(FD_ISSET(STDIN_FILENO, &read_fds)){
      if(fgets(buf, sizeof(buf), stdin) == NULL)break;
      send(server_socket, buf, strlen(buf), 0);
    }

    if(FD_ISSET(server_socket, &read_fds)){
      int n = recv(server_socket, buf, sizeof(buf), 0);
      if(n <= 0){
        printf("Server disconnected\n");
        break;
      }
      buf[n] = '\0';
      printf("%s", buf);
    }
  }
  close(server_socket);
  return 0;
}
