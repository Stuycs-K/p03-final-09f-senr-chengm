#include "networkstructure.h"

int main(int argc, char *argv[] ) {
  int listen_socket;
  if (argc > 1) {
    listen_socket = server_setup(argv[1]);
  } else {
    listen_socket = server_setup(NULL);
  }
  int clients[100];
  int client_count = 0;

  fd_set read_fds;

  char buff[1024];
  char buff2[1024];


  while(1) {
    FD_ZERO(&read_fds);
    //add listen_socket and stdin to the set
    FD_SET(listen_socket, &read_fds);
    int fd_max = listen_socket;

    for(int i = 0; i < client_count; i++){
      FD_SET(clients[i], &read_fds);
      if(clients[i] > fd_max){
        fd_max = clients[i];
      }
    }

    //select Code
    select(fd_max + 1, &read_fds, NULL, NULL, NULL);

    if(FD_ISSET(listen_socket, &read_fds)){
      int client_socket = server_tcp_handshake(listen_socket);
      clients[client_count] = client_socket;
      client_count++;
      printf("Client connected \n");

      char msg[1024];
      sprintf(msg,"A new client has connected, %d clients online.\n", client_count);
      for(int j = 0; j < client_count - 1; j++){
        send(clients[j], msg, strlen(msg), 0);
      }
    }

    for(int i = 0; i < client_count; i++){
      if(FD_ISSET(clients[i], &read_fds)){
        int n = recv(clients[i], buff, sizeof(buff)-1,0);

        if(n <= 0){
          close(clients[i]);


          client_count--;
          clients[i] = clients[client_count];
          i--;

          char leave_msg[1024];
          sprintf(leave_msg,"A client has disconnected, %d clients still online.\n", client_count);
          for(int j = 0; j < client_count; j++){
            send(clients[j], leave_msg, strlen(leave_msg), 0);
          }
          printf("Client disconnected\n");
          continue;
        }
        buff[n] = '\0';

        //send code
        for(int j = 0; j < client_count; j++){
          send(clients[j], buff, n, 0);
        }
      }
    }

    // pid_t f = fork();
    // if (f == 0) {
    //   char buf[1024];
    //   close(listen_socket);
    //   subserver_logic(client_socket);
    //   close(client_socket);
    //   exit(0);
    // } else {
    //   close(client_socket);
    // }
  }
}
