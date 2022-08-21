#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8002

using namespace std;

const int buffer_size = 4096;
char buffer[buffer_size];
bool isExit = false;

int main()
{
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv_sock < 0)
    {
        cout << "socket error " << endl;
        return 0;
    }
    cout << "socket created !! " << endl;
    //     IP、
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;                     //  IPv4
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //   IP
    serv_addr.sin_port = htons(PORT);                   //

    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        cout << "socket bind error " << endl;
        return 0;
    }
    cout << "bind !!" << endl;
    listen(serv_sock, 20);
    cout << "listen !!" << endl;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if(clnt_sock<0){
        cout << "client socket error " << endl;
        return 0;
    }
    cout << "client socket accept !! "<< endl;
    strcpy(buffer,"server connection");
    send(clnt_sock,buffer,sizeof(buffer)-1,0);
    memset(buffer,0,sizeof(buffer));
    do{
        memset(buffer,0,sizeof(buffer));
        recv(clnt_sock,buffer,sizeof(buffer)-1,0);
        if(strlen(buffer)!=0){
            cout << "client : "<< buffer ;
        }
        if(strcmp(buffer,"exit\n")==0){
            cout << "socket disconnect "<< endl;
            close(serv_sock);
            close(clnt_sock);
        }
    }while(!isExit);
        
}
