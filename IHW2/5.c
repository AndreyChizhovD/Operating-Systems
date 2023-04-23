#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>

#define NAME_SEM "/semaphore_workers"
#define NUM_WORKERS 3
#define NUM_PINS 8

typedef struct {
    sem_t sem;
    int left_to_create;
    int count;
} shared_data;

shared_data *create_shared_data() {
    shared_data *data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    data->left_to_create = NUM_PINS;
    data->count = 1;
    return data;
}

void free_shared_data(shared_data *data) {
    munmap(data, sizeof(shared_data));
}

void signal_handler(int sigint) {
    printf("Exiting program %d...\n\n", sigint);
    exit(sigint);
}

int check_pin(int stage, int is_ok, shared_data *data) {
    if (is_ok == 0) {
        return 0;
    }
    if (stage == 1) {
        printf("FIRST WORKER checking curvature...\n");
        if (rand() % 3 + 1 == 3) {
            printf("Pin is no good. On to the next.\n\n");
            return 0;
        }
    } else if (stage == 2) {
        printf("SECOND WORKER checking the pin...\n");
        if (rand() % 4 + 1 == 4) {
            printf("Pin is no good. On to the next.\n\n");
            return 0;
        }
    } else {
        printf("THIRD WORKER checking the pin...\n");
        if (rand() % 5 + 1 == 5) {
            printf("Pin is no good. On to the next.\n\n");
            return 0;
        }
    }
    return 1;
}

int main() {
    signal(SIGINT, signal_handler);
    srand(time(NULL));
    shared_data *data = create_shared_data();
    pid_t children[NUM_PINS];
    sem_unlink(NAME_SEM);
    sem_t *sem = sem_open(NAME_SEM, O_CREAT, S_IRUSR | S_IWUSR, 1);

    for (int i = 0; i < NUM_PINS; ++i) {
        children[i] = fork();
        if (children[i] == 0) {
            printf("Processing %d pin...\n", data->count);
            int first = check_pin(1, 1, data);
            int second = check_pin(2, first, data);
            int third = check_pin(3, second, data);
            if (third) {
                printf("Pin %d is selected\n\n", data->count++);
            }
            exit(0);
        }
    }

    for (int i = 0; i < NUM_WORKERS + NUM_PINS; i++) {
        wait(NULL);
    }

    printf("All pins are processed!\n");
    sem_close(sem);
    sem_unlink(NAME_SEM);

    free_shared_data(data);

    return 0;
}

