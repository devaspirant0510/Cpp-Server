#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8009

const int buffer_size = 4096;
char buffer[buffer_size];
     
using namespace std;

int main(){
      int sock = socket(AF_INET, SOCK_STREAM, 0);
      struct sockaddr_in serv_addr;
      memset(&serv_addr, 0, sizeof(serv_addr)); //      0  
      serv_addr.sin_family = AF_INET; //  IPv4  
      serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //   IP  
      serv_addr.sin_port = htons(PORT); //  
      connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
      recv(sock,buffer,sizeof(buffer)-1,0);
      cout << "server : " << buffer << endl;
      char msg[] = "Funck you Man";
      while(1){
            fgets(buffer,sizeof(buffer),stdin);
            write(sock,buffer,sizeof(buffer)-1);      
      }
      close(sock);
      return 0;
}
