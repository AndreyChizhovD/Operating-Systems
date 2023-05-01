#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int pid; // receiver's pid
    long number; // a number to pass to receiver

    printf("Receiver's PID: ");
    scanf("%d", &pid);
    printf("Number to transmit: ");
    scanf("%ld", &number);

    for (int i = 0; i < 64; ++i) {
        if ((number >> i & 1) == 0) {
            kill(pid, SIGUSR1);
        } else {
            kill(pid, SIGUSR2);
        }
        usleep(1000);
    }

    return 0;
}

