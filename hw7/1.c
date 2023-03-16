#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <error.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NMAX 256

int main(int argc, char **argv) {
	key_t key;
	int semid, shmid;
	struct sembuf sops;
	char *shmaddr;
	char str[NMAX];
	int num, count;

	key = ftok("/hw7", 'S');
	semid = semget(key, 1, 0666 | IPC_CREAT);
	shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
	shmaddr = shmat(shmid, NULL, 0);
	semctl(semid,0,SETVAL, (int) 0);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	
	for (count = 0; count < 21; ++count) {
		num = random() % 1000;
		sprintf(str, "%d", num);
		strcpy(shmaddr, str); // copy str to shared memory
		sops.sem_op = 3;
		semop(semid, &sops, 1);
		sops.sem_op = 0;
		semop(semid, &sops, 1);
		++count;
		sleep(1);
	}
	
	shmdt(shmaddr) ;
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID, (int) 0);
	
	return 0;
}

