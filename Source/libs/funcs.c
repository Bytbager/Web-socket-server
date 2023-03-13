#include "funcs.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

void parse_http(char *filename, int client_sock) {
    char buffer[BUFSIZ] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
    int readsiz = strlen(buffer);
    send(client_sock, buffer, readsiz, 0);
    FILE *page = fopen(filename, "r");
    while ((readsiz = fread(buffer, sizeof(char), BUFSIZ, page)) != 0) {
        send(client_sock, buffer, readsiz, 0);
    }
    fclose(page);
}

HTTPreq new_http(void) { return (HTTPreq){.method = {0}, .path = {0}, .protocol = {0}}; }

void parse_request(char *request, HTTPreq *req) {
    int i = 0, j = 0;
    for (;; i++, j++) {
        if (request[i] == ' ') break;
        req->method[j] = request[i];
    }
    i++;
    for (j = 0;; i++, j++) {
        if (request[i] == ' ') break;
        req->path[j] = request[i];
    }
    i++;
    for (j = 0;; i++, j++) {
        if (request[i] == '\n') break;
        req->protocol[j] = request[i];
    }
}