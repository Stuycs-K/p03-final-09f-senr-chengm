#include "networkstructure.h"

void save_to_file(char * msg) {
  int f = open("msg.txt",O_APPEND | O_WRONLY | O_CREAT, 0644);
  write(f, msg, strlen(msg));
  write(f, "\n", 1);
  close(f);
}

void send_chat(int socket) {
  int f = open("msg.txt",O_RDONLY, 0644);
  char buf[1024];
  while ((read(f, buf, sizeof(buf)))>0) {
    send(socket, buf, strlen(buf), 0);
  }
  close(f);
}

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
  char usernames[100][128];
  int user[100] = {0};

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
      send_chat(client_socket);
    }

    for(int i = 0; i < client_count; i++){
      if(FD_ISSET(clients[i], &read_fds)){
        int n = recv(clients[i], buff, sizeof(buff)-1,0);

        if(n <= 0){
          printf("Client disconnected \n");
          char leave_msg[1024];
          if(user[i]){
            snprintf(leave_msg,sizeof(leave_msg), "%s has disconnected, %d clients still online.", usernames[i], client_count-1);
            save_to_file(leave_msg);
          }
          else{
            snprintf(leave_msg,sizeof(leave_msg),"A user has disconnected, %d clients still online.\n",client_count-1);
          }
          client_count--;
          clients[i] = clients[client_count];
          strcpy(usernames[i], usernames[client_count]);
          user[i] = user[client_count];
          i--;
          for(int j = 0; j < client_count; j++){
            send(clients[j], leave_msg, strlen(leave_msg), 0);
          }
          continue;
        }
        buff[n] = '\0';

        if(!user[i]){
          strncpy(usernames[i],buff,sizeof(usernames[i])-1);
          usernames[i][sizeof(usernames[i])-1] = '\0';
          user[i] = 1;

          char msg[1024];
          snprintf(msg, sizeof(msg),"%s has connected, %d clients online.", usernames[i], client_count);
          for(int j = 0; j < client_count; j++){
            send(clients[j], msg, strlen(msg),0);
          }
          continue;
        }

        //send code

        char other[1024+129];
        snprintf(other,sizeof(other),"%s: %s", usernames[i], buff);
        save_to_file(other);
        for(int j = 0; j < client_count; j++){
          send(clients[j], other,strlen(other), 0);
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
