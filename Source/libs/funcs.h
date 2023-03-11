#ifndef LIBS_FUNCS_H
#define LIBS_FUNCS_H

typedef struct {
    char method[16];
    char path[2048];
    char protocol[16];
} HTTPreq;

void parse_http(char *filename, int client_sock);
void parse_request(char *request, HTTPreq *req);
HTTPreq new_http(void);

#endif
