#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEM_NAME "/my_sem"

int main() {
    int pipefd[2];
    int status;

    if (pipe(pipefd) == -1) {
        perror("Can't create named pipe");
        exit(1);
    }

    sem_t *semaphore = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (semaphore == SEM_FAILED) {
        perror("Can't create semaphore");
        exit(1);
    }

    pid_t child = fork();

    if (child == -1) {
        perror("Can't create child");
        exit(1);
    }

    int count = 0;
    if (child == 0) {
        close(pipefd[1]);

        while (count < 10) {
            char message[256];
            read(pipefd[0], message, sizeof(message));
            printf("Child got a message from parent : %s", message);
            sem_post(semaphore);
            ++count;
        }

        sem_close(semaphore);
        close(pipefd[0]);
        exit(0);

    } else {
        close(pipefd[0]);

        while (count < 10) {
            char message[256];
            printf("Enter a message : ");
            fgets(message, sizeof(message), stdin);
            write(pipefd[1], message, strlen(message));
            sem_wait(semaphore);
            printf("Parent successfully passed the message on.\n");
            ++count;
        }

        sem_close(semaphore);
        close(pipefd[1]);
        waitpid(child, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child was terminated with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child was terminated with signal %d\n", WTERMSIG(status));
        }
        sem_unlink(SEM_NAME);
        exit(0);
    }

    return 0;
}

