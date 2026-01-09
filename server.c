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


// void subserver_logic(int client_socket){
//   char buf[1024];
//   fd_set read_fds;
//   while(1) {
//     int n = recv(client_socket, buf, 1024, 0);
//     if (n == 0) {
//       close(client_socket);
//       printf("Socket closed\n");
//       exit(0);
//     }
//     int fd = open("messages.txt",O_WRONLY);
//     write(fd, buf, n);
//     close(fd);
//     buf[n-1] = '\0';
//     printf("'%s'\n", buf);
//     send(client_socket, buf, n, 0);
//   }
// }

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();
  fd_set read_fds, cons;
  FD_ZERO(&cons);
  //add listen_socket and stdin to the set
  FD_SET(listen_socket, &cons);
  int fd_max = listen_socket;

  char buff[1024];
  //listen socket is larger than STDIN_FILENO, so listen_socket+1 is the 1 larger than max fd value.

  while(1) {
    read_fds = master;
    select(fd_max + 1, &read_fds, NULL, NULL, NULL);
    for(int fd = 0; fd < fd_max; fd++){
      if (!FD_ISSET(fd, &read_fds)) {
        continue;
      }
      if(fd == listen_socket){
        int client_socket = server_tcp_handshake(listen_socket);
        FD_SET(client_socket, &master);
        if(client_socket > fd_max){
          fd_max = client_socket;
        }
      }
      else{
        int n = recv(fd, buff, 1024, 0);
        if(n <= 0){
          close(fd);
        }
        else{
          buff[n-1] = '\0';
          printf("'%d': %s\n", fd, buff);
        }
      }
    }
  }
}
