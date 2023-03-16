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
	int count;
	char str[NMAX];
	
	key = ftok("/hw7",'S');
	semid = semget(key, 1, 0666 | IPC_CREAT);
	shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
	shmaddr = shmat(shmid, NULL, 0);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	
	for (count = 0; count < 21; ++count) {
		printf("Waiting on semaphore... \n");
		sops.sem_op = -2;
		semop(semid, &sops, 1);
		strcpy(str, shmaddr);
		if (count == 21) {
			shmdt(shmaddr); // free shared memory
		}
		sops.sem_op=-1;
		semop(semid, &sops, 1);
		printf("That's what's read from shared memory: %s\n", str);
		++count;
		sleep(1.04);
	}

	return 0;
}

