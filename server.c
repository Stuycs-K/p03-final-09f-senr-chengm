#include "networkstructure.h"
#include <signal.h>
//add to seperate file?
void create(){
  //Shared memory
  int shmd;
  int *data;
  shmd = shmget(key, sizeof(int), IPC_CREAT | 0640);
  if(shmd < 0)err();
  data = shmat(shmd,0,0);
  if(data == (void*)-1)err();
  shmdt(data);
  //Semaphore
  int semd = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
  if(semd < 0)err();
  union semun us;
  us.val = 1;
  int r = semctl(semd, 0, SETVAL, us);
  if(r<0)err();

  //file
  int w_file = open("story.txt", O_WRONLY | O_TRUNC | O_CREAT, 0600);
  if(w_file < 0)err();
  close(w_file);
}

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
      close(listen_socket);
      subserver_logic(client_socket);
      close(client_socket);
      exit(0);
    } else {
      close(client_socket);
    }
  }
}
