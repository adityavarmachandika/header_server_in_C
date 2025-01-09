#include<stdio.h>
#include "Server.h"
#include<winsock2.h>

struct Server server_constructor(int domain,int service,int protocol,int port,int backlog,u_long interfacee,void (*launch)(struct Server *server)){
     WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
 
    struct Server server;
    server.domain=domain;
    server.service=service;
    server.protocol=protocol;
    server.port=port;
    server.backlog=backlog;
    server.interfacee=interfacee;

    server.address.sin_family=domain;
    server.address.sin_port=htons(port);
    server.address.sin_addr.s_addr=htonl(interfacee);
    server.socket_fd=socket(domain,service,protocol);
    if(server.socket_fd == INVALID_SOCKET){
        printf("socket failed to connect");
        exit(1);
    }

    if(bind(server.socket_fd, (struct sockaddr *)&server.address,sizeof(server.address))<0){
        printf("socket failed to bind");
        exit(1);
    }
    printf("Socket ID is: %d", server.socket_fd);

    if(listen(server.socket_fd,server.backlog)){
        printf("socket failed to listen");
        exit(1);
    }
    server.launch=launch;
    return server;
}

