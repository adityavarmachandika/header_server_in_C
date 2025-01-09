#include<stdio.h>
#include "Server.h"


void launch(struct Server *server){
    printf("\nServer launched");

    char buffer[1000];
    char *msg="HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 49\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>hello</h1></body></html>";
    int address_len=sizeof(server->address);
    int new_soc;
    while(1){
        new_soc=accept(server->socket_fd,(struct sockaddr *)&server->address,&address_len);
        if(recv(new_soc,buffer,sizeof(buffer),0)<=0){
            printf("failed to recieve data");
            closesocket(new_soc);
            exit(1);
        }
        printf("%s",buffer);
        if(send(new_soc,msg,5,0)==SOCKET_ERROR){
            printf("failed to send the data");
            closesocket(new_soc);
            exit(1);
        }
        closesocket(new_soc);
    }
    closesocket(server->socket_fd);
}


int main(){
    struct Server server= server_constructor(AF_INET,SOCK_STREAM,0,8080,10,INADDR_ANY,launch);
    server.launch(&server);
    return 0;
}