#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "libs/funcs.h"

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
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_address, len) == -1) {
        perror("bind() error!");
        exit(-1);
    }

    if (listen(server_sock, MAX_CONN) == -1) {
        perror("listen() error!");
        exit(-1);
    }
    while (1) {
        if ((client_sock = accept(server_sock, (struct sockaddr *)&server_address, &len)) == -1) {
            perror("accept() error!");
            exit(-1);
        }

        recv(client_sock, recv_msg, sizeof(recv_msg), 0);
        HTTPreq req = new_http();
        parse_request(recv_msg, &req);
        printf("%s %s %s\n", req.method, req.path, req.protocol);
        if (strcmp(req.path, "/") == 0) {
            parse_http("index.html", client_sock);
        } else if (strcmp(req.path, "/about/") == 0) {
            parse_http("about.html", client_sock);
        } else if (strcmp(req.path, "/Books/books.html") == 0) {
            parse_http("Books/books.html", client_sock);
        } else if (strcmp(req.path, "/Books/book1.html") == 0) {
            parse_http("Books/book1.html", client_sock);
        } else if (strcmp(req.path, "/Books/book2.html") == 0) {
            parse_http("Books/book2.html", client_sock);
        } else if (strcmp(req.path, "/images/images.html") == 0) {
            parse_http("images/images.html", client_sock);
        } else if (strcmp(req.path, "/images/image1.html") == 0) {
            parse_http("images/image1.html", client_sock);
        } else if (strcmp(req.path, "/images/image2.html") == 0) {
            parse_http("images/image2.html", client_sock);
        } else if (strcmp(req.path, "/favicon.ico") == 0) {
            char buffer[BUFSIZ] = "HTTP/1.1 200 OK\nContent-Type: image/png\n\n";
            int readsiz = strlen(buffer);
            send(client_sock, buffer, readsiz, 0);
            FILE *page = fopen("images/favicon.png", "r");
            while ((readsiz = fread(buffer, sizeof(char), BUFSIZ, page)) != 0) {
                send(client_sock, buffer, readsiz, 0);
            }
            fclose(page);
        } else {
            char buffer[BUFSIZ] = "HTTP/1.1 404 OK\n\n";
            int readsiz = strlen(buffer);
            send(client_sock, buffer, readsiz, 0);
            FILE *page = fopen("page404.html", "r");
            while ((readsiz = fread(buffer, sizeof(char), BUFSIZ, page)) != 0) {
                send(client_sock, buffer, readsiz, 0);
            }
            fclose(page);
        }
        close(client_sock);
    }
    return 0;
}