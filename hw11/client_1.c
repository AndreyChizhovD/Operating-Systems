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

    int client_1 = socket(PF_INET, SOCK_STREAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));

    if (connect(client_1, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("Perror: connect() -1");
        exit(-1);
    }

    while (1) {
        printf("to Client_2 : ");
        fgets(buffer, 1024, stdin);
        buffer[strlen(buffer) - 1] = '\0'; // to be able to read The End
        write(client_1, buffer, strlen(buffer));
        if (strcmp(buffer, "The End") == 0) {
            close(client_1);
            printf("Client_1 terminated.\n");
            break;
        }
    }

    return 0;
}



