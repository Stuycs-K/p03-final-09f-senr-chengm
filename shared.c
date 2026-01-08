#include <signal.h>

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};
//int semd = semget(key, 1, 0);
//   struct sembuf hold;
//   hold.sem_num = 0;
//
//   hold.sem_flg = SEM_UNDO; // Necessary???
//
//   hold.sem_op = -1;
//   printf("Attempting to access story\n");
//   semop(semd,&hold,1);
//   printf("Semaphore found!\n");
//   char line_buff[256];
//   char line_buff2[256];
//   int fd = open("story.txt", O_RDWR);
//   if(fd<0)err();
//   int shmd = shmget(key, sizeof(int), 0);
//   int *data = shmat(shmd, 0, 0);
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
  int w_file = open("messages.txt", O_WRONLY | O_TRUNC | O_CREAT, 0600);
  if(w_file < 0)err();
  close(w_file);
}

void rem(){
  union semun us;
  int semd = semget(key, 1, 0 );
  if(semd >= 0){
    semctl(semd, 0, IPC_RMID, us);
  }

  int shmd = shmget(key, sizeof(int), 0);
  if(shmd >= 0){
    shmctl(shmd, IPC_RMID, 0);
  }

}
