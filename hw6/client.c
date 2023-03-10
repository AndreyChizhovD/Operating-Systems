#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>

int main(){
  int shm_id;
  int *share;
  int num;
  int count;

  srand(time(NULL));
  shm_id = shmget (0x2FF, getpagesize(), 0666 | IPC_CREAT);
  printf("shm_id = %d\n", shm_id);
  if(shm_id < 0){
    perror("shmget()");
    exit(1);
  }

  share = (int *)shmat(shm_id, 0, 0);
  if(share == NULL){
    perror("shmat()");
    exit(2);
  }
  printf("share = %p\n", share);

  count = 0;
  while(count < 21){
    num = random() % 1000;
    *share = num;
    printf("write a random number %d\n", num);
    sleep(1);
    count += 1;
  }
  
  shmdt(share);
  if (shmctl (shm_id, IPC_RMID, (struct shmid_ds *) 0) < 0) {
    puts("client: shared memory remove error");
    exit(1);
  }
  
  exit (0);
}

