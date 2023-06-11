#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int check_pin(int stage, int is_ok) {
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

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr, client_addr;
    int server_socket;
    int num_clients = atoi(argv[3]);

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
    socklen_t client_addr_len = sizeof(client_addr);

    int selected[num_clients];

    for (int i = 0; i < num_clients; i++) {
        char name;
        recvfrom(server_socket, &name, sizeof(name), 0, (struct sockaddr *) &client_addr, &client_addr_len);

        printf("Processing %d pin...\n", i + 1);
        int first = check_pin(1, 1);
        int second = check_pin(2, first);
        int third = check_pin(3, second);
        if (third) {
            printf("Pin %d is selected\n\n", i + 1);
        }
        selected[i] = third;
    }

    close(server_socket);

    printf("All pins are processed.\n");
    printf("Selected pins: ");
    for (int i = 0; i < num_clients; ++i) {
        if (selected[i]) {
            printf("%d;", i + 1);
        }
    }

    return 0;
}

