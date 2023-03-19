#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <error.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include "32.c"

#define NMAX 5000
#define m_size 5000

int main(int argc, char **argv) {
	char *pipe1 = "1.fifo";
	char *pipe2 = "2.fifo";
    mknod(pipe1, S_IFIFO | 0666, 0);	
    mknod(pipe2, S_IFIFO | 0666, 0);

    char buf[m_size];
    int st, fs, size;

    int process1 = fork();
    if (process1 == -1) {
        printf("Fork failed\n");
        exit(-1);
    } else if (process1 == 0) {
        int process2 = fork();
        if (process2 == -1) {
            printf("Fork failed\n");
            exit(-1);
        } else if (process2 == 0) {
            st = open(pipe2, O_RDONLY);
            size = read(st, buf, m_size);
            if (close(st) < 0) {
                printf("Error closing FIFO\n");
                exit(-1);
            }
            int output_file =  open(argv[2], O_WRONLY | O_CREAT, 0666);
            if (output_file < 0) {
                printf("Error opening file\n");
                exit(-1);
            }
            size = write(output_file, buf, strlen(buf));
            if (size != strlen(buf)) {
                printf("Error writing\n");
                exit(-1);
            }
            if (close(output_file) < 0) {
                printf("Error closing file\n");
                exit(-1);
            }
            //
            unlink(pipe1);
            unlink(pipe2);
            //
        } else {
            if ((fs = open(pipe1, O_RDONLY)) < 0) {
                printf("Error opening FIFO W\n");
                exit(-1);
            }
            size = read(fs, buf, m_size);
            if (size < 0) {
                printf("Error reading from FIFO\n");
                exit(-1);
            }
            
			char *token, *last;
			token = strtok(buf, "\n");
			char *buf1 = token;
			token = strtok(NULL, "\n");
			buf[0] = *buf1;
			str_diff(buf, token);
			
            if (close(fs) < 0) {
                printf("Child: error closing FIFO\n");
                exit(-1);
            }
            if ((st = open(pipe2, O_WRONLY)) < 0) {
                printf("Error opening FIFO W\n");
                exit(-1);
            }
            size = write(st, buf, m_size);
            if (size != m_size) {
                printf("Error writing FIFO\n");
                exit(-1);
            }
            if (close(st) < 0) {
                printf("Parent: error closing FIFO \n");
                exit(-1);
            }
        }       
    } else {
        int input_file = open(argv[1], O_RDONLY, 0666);
        if (input_file < 0) {
            printf("Error opening file\n");
            exit(-1);
        }
        size = read(input_file, buf, m_size);
        if (close(input_file) < 0) {
            printf("Error closing file\n");
        }
        if ((fs = open(pipe1, O_WRONLY)) < 0) {
            printf("Error opening FIFO W\n");
            exit(-1);
        }
        size = write(fs, buf, m_size);
        if (close(fs) < 0) {
            printf("Parent: error FIFO W\n");
            exit(-1);
        }
    }
    return 0;
}
	
