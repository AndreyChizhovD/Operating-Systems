#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<error.h>

int main() {
  int shmid;
  int *share;
  int count;

  if((shmid = shmget (0x2FF, getpagesize(), 0666 | IPC_CREAT)) == -1){
    perror("shmget()");
    exit(1);
  }

  if((share = (int *)shmat(shmid, 0, 0)) == NULL){
    perror("shmat()");
    exit(2);
  }

  count = 0;
  while(count < 21) {
    sleep(1);
    printf("%d\n", *share);
    count++;
  }

  return 0;
}

