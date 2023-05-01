#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// transmitted number
volatile long number = 0;
// number of bits
volatile uint curr_bit = 0;

void handler1() {
    ++curr_bit;
}

void handler2() {
    number = number | (1 << curr_bit);
    ++curr_bit;
}

int main() {
    struct sigaction sig1;
    struct sigaction sig2;

    sig1.sa_handler = handler1;
    sig2.sa_handler = handler2;
    sig1.sa_flags = sig2.sa_flags = 0;

    if (sigaction(SIGUSR1, &sig1, NULL) < 0 || sigaction(SIGUSR2, &sig2, NULL) < 0) {
        perror("SIGACTION");
        exit(-1);
    }

    printf("PID for transmitter: %d\n", getpid());
    while (curr_bit < 64) {
        pause();
    }
    printf("Transmitted number: %ld\n", number);

    return 0;
}

