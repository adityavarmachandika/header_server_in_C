#include<winsock2.h>


struct Server{
    int domain;
    int service;
    int protocol;
    int port;
    int backlog;
    u_long interfacee;

    SOCKET socket_fd;
    struct sockaddr_in address;

    void (*launch)(void);
};

struct Server server_constructor(int domain,int service,int protocol,int port,int backlog,u_long interfacee,void (*launch)(void));
