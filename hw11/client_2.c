#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in server_address;

    char buffer[1024];

    int client_2 = socket(PF_INET, SOCK_STREAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));

    if (connect(client_2, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("Perror: connect() -1");
        exit(-1);
    }

    while (1) {
        int size = read(client_2, buffer, 1024);
        buffer[size] = '\0';
        printf("from Client_1 : %s\n", buffer);
        if (strcmp(buffer, "The End") == 0) {
            close(client_2);
            printf("Client_2 terminated.\n");
            break;
        }

    }

    return 0;
}
