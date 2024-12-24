#include<stdio.h>
#include "Server.h"


void launch(){
    printf("\nServer launched");
}


int main(){
    struct Server server= server_constructor(AF_INET,SOCK_STREAM,0,8080,10,INADDR_ANY,launch);
    server.launch();
    return 0;
}