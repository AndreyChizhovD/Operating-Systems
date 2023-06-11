#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    int client_socket;

    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    char* name = argv[3];
    if (sendto(client_socket, &name, sizeof(name), 0, (struct sockaddr *) &server_addr,
               sizeof(server_addr)) < 0) {
        perror("Connecting error. The limit of pins is reached or server is closed.");
        exit(-1);
    }

    printf("Pin was processed");
    close(client_socket);
    return 0;
}

