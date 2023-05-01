#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int client_1, client_2; // sockets

    int server = socket(PF_INET, SOCK_STREAM, 0); // server socket
    if (server == -1) {
        exit(1);
    }

    char message[1024];
    struct sockaddr_in server_adress, client_adress;
    socklen_t adress_size;
    memset(&server_adress, 0, sizeof(server_adress));

    server_adress.sin_family = AF_INET;
    server_adress.sin_addr.s_addr = htonl(INADDR_ANY);
    server_adress.sin_port = htons(atoi(argv[1]));

    if (bind(server, (struct sockaddr *) &server_adress, sizeof(server_adress)) == -1) {
        perror("Perror: bind() -1");
        exit(-1);
    }
    if (listen(server, 2) == -1) {
        perror("Perror: listen() -1");
        exit(-1);
    }

    adress_size = sizeof(client_adress);
    client_1 = accept(server, (struct sockaddr *) &client_adress, &adress_size);
    client_2 = accept(server, (struct sockaddr *) &client_adress, &adress_size);

    while (1) {
        int size = read(client_1, message, 1024);
        message[size] = '\0';
        write(client_2, message, size);
        if (strcmp(message, "The End") == 0) {
            close(client_1);
            close(client_2);
            close(server);
            break;
        }
    }
    printf("Clients terminated.\nServer is closed.\n");
    return 0;
}
