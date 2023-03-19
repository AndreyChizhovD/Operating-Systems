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
#include <fcntl.h>
#include "32.c"

#define NMAX 5000
#define m_size 5000

int main(int argc, char **argv) {
    char buf[m_size];

    int fs[2]; // 1 --> 2
    int st[2]; // 2 --> 3
    pipe(fs);
    pipe(st);

    int size;
    int process1 = fork();
    if (process1 == -1) {
        printf("fork() failed\n");
        exit(-1);
    } else if (process1 == 0) {
        int process2 = fork();

        if (process2 == -1) {
            printf("fork() failed\n");
            exit(-1);
        } else if (process2 == 0) {
        
            if (close(st[1]) < 0) {
                printf("Child: error closing pipe W\n");
                exit(-1);
            }

            size = read(st[0], buf, m_size);
            
            if (close(st[0]) < 0) {
                printf("Child: error closing pipe R\n");
                exit(-1);
            }

            int out = open(argv[2], O_WRONLY | O_CREAT, 0666);

            if (out < 0) {
                printf("Error opening file\n");
                exit(-1);
            }
            
            size = write(out, buf, strlen(buf));
            if (size != strlen(buf)) {
                printf("Error writing\n");
                exit(-1);
            }

            if (close(out) < 0) {
                printf("Error closing file\n");
                exit(-1);
            }
        } else {
            if (close(fs[1] < 0)) {
                printf("Child: error closing pipe W\n");
                exit(-1);
            }
            
            size = read(fs[0], buf, m_size);

            if (size < 0) {
                printf("Error pipe R\n");
                exit(-1);
            }

	    char *token, *last;
       	    token = strtok(buf, "\n");
	    char *buf1 = token;
	    token = strtok(NULL, "\n");
	    buf[0] = *buf1;
            str_diff(buf, token);
            
            if (close(fs[0]) < 0) {
                printf("Child: error closing pipe R\n");
                exit(-1);
            }

            size = write(st[1], buf, m_size);

            if (size != m_size) {
                printf("Error writing to pipe\n");
                exit(-1);
            }

            if (close(st[1]) < 0) {
                printf("Child: error closing pipe W\n");
                exit(-1);
            }
        }       
    } else {
    
        if (close(fs[0]) < 0) {
            printf("Child: error closing pipe R\n");
            exit(-1);
        }
      
        int input = open(argv[1], O_RDONLY, 0666);
        if (input < 0) {
            printf("Error opening file\n");
            exit(-1);
        }
        size = read(input, buf, m_size);

        if (close(input) < 0) {
            printf("Error closing file\n");
        }

        size = write(fs[1], buf, m_size);

        if (size != m_size) {
            printf("Error writing to pipe");
            exit(-1);
        }

        if (close(fs[1]) < 0) {
            printf("Child: error closing pipe W\n");
            exit(-1);
        }
    }
    return 0;
}

