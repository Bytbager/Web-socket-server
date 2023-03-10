#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 1234
#define MAX_CONN 3

int main(void) {
    int server_sock, client_sock;
    unsigned int len = sizeof(struct sockaddr_in);
    char recv_msg[65536];

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket() error!");
        exit(-1);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_address, len) == -1){
        perror("bind() error!");
        exit(-1);
    }

    if (listen(server_sock, MAX_CONN) == -1){
        perror("listen() error!");
        exit(-1);
    }
    while (1) {
    if ((client_sock = accept(server_sock, (struct sockaddr*)&server_address, &len)) == -1) {
        perror("accept() error!");
        exit(-1);
    }
    recv(client_sock, recv_msg, sizeof(recv_msg), 0);
    printf("%s\n",recv_msg);
    char msg[] = "Web hello!!!";
    send(client_sock, msg, sizeof(msg), 0);
    close(client_sock);
    }
    return 0;
}