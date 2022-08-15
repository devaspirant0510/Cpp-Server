#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
     
int main(){
       int sock = socket(AF_INET, SOCK_STREAM, 0);
 //    （   IP   ）    
 struct sockaddr_in serv_addr;
 memset(&serv_addr, 0, sizeof(serv_addr)); //      0  
 serv_addr.sin_family = AF_INET; //  IPv4  
 serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //   IP  
 serv_addr.sin_port = htons(1234); //  
 connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
 char buffer[40];
 while(1){

 read(sock, buffer, sizeof(buffer)-1);
 printf("Message form server: %s\n", buffer);
 }
 char msg[] = "Funck you Man";
 write(sock,msg,sizeof(msg)-1);
 close(sock);
 return 0;
}
