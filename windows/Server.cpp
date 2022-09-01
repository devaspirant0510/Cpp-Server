#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <pthread.h>

using namespace std;
/*
 * 소켓 서버와 클라이언트
 * 서버에서 소켓을 열고 listen 을 하면 클라이언트가 서버에 conncet
 * --서버단
 * 1. 소켓 생성
 * 2. 소켓 바인드 (어떤 ip,port,protcol) 등을 설정해  바인드
 * 3. 소켓 listen : client 를 기다림 여기서 만약 client 가 접속을 했다면 4. 의 accept
 * 4. 소켓 accept : client connect 허용
 * 이후 send recv 를 하여 데이터 통신
 *
 * --클라단
 * 1 소켓 생성, 서버의 생성과 마찬가지로 ip port protocol 등을 설정
 * 2. connect 를 서버에 하면 서버에선 listen 상태에서 클라 접속을 확인하고 경우에따라 연결을 허용(accept) 해주거나 막을수 있음
 *
 */
int main(int argc, char **argv){
    /*
     * ipv4 127.12.32.1
     * 경우의 수는 255^4 예전에는 ipv4 주소 개수많으로도 충분하지만 인테넷 기계가 증가함에따라
     * ipv4 많으로는 부족하게 됨
     * ipv6 2001:0DB8:1000:0000:0000:0000:1111:2222
     * ipv4 보다 훨씬더 많은 경우의수를 가짐 세상이 종말할떄까지 써도 절대 못씀
     * 그러나 안쓰는 이유... 공유기의 등장! -> 공유기라는 ip 하나로 여러 기기가 접속 가능
     * 결국 ipv4 로도 문제없이 작동가능
     * 유동 IP
     */
    cout <<  "argc : " << argc << endl;
    cout << "argv [ 0 ] : " << argv[0] << endl;
    cout << "argv [ 1 ] : " << argv[1] << endl;
    cout << "argv [ 1 ] : " << atoi(argv[1]) << endl;
    // [0] 네트워크 주소체계
    //PF_INET   ipv4
    //PF_INET6  ipv6
    /*=*/
    // [1] 소켓 타입
    // SOCK_STREAM 스트림, TCP 프로토콜 방식
    // SOCK_DGRAM 데이터그램, UDP 프로토콜 방식
    // SOCK_RAW RAW 소켓, 가공하지 않은 소켓 밑에단 만질떄 사용
    /*=*/
    // [2] 프로토콜
    // 프로토콜 파라미터도 지정할수 있지만 0 을 입력하면 소켓타입을 보고 tcp로 할건지
    // udp로 할건지 알아서 결정
    WSADATA  wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
        cout << "wsaStartup failure" << endl;
    }
    struct sockaddr_in serv_addr,clnt_addr;
    int clnt_addr_size;
    int serv_sock,clnt_sock;
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1){
        cout << "socket error "<< endl;
        exit(1);
    }
    cout << "socket create !! "<< endl;

    // ===================== bind =============================
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4311);
    serv_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    cout << htonl(INADDR_ANY) << endl;
    // 바이트 오더 : 데이터를 저장하는 방식
    // 리틀베디안
    // 빅엔디언  : 네트워크 오더

    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        cout << "bind error "<< endl;
        exit(1);
    }
    cout << "bind !!" << endl;
    if(listen(serv_sock,5)==-1){
        cout <<  "listen error" << endl;
        exit(1);
    }
    cout << "listen !! "<< endl;
    char buffer[1300];
    int recv_len = 0;
    while(1){
        clnt_addr_size = sizeof(clnt_addr);
        // 서버소켓에 클라 소켓(접속하는 소켓을 연결)
        // 즉 클라이언트를 받는 작업은 서버소켓에서 하고 recv send 작업은 클라 소켓에서 함
        // accept 을 할경우 clnt_addr 에 클라이언트 소켓 정보를 가져옴
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);

        recv_len = recv(clnt_sock,buffer,sizeof(buffer),0);
        if(recv_len>0){
            cout << "client port : " << clnt_addr.sin_port << endl;
            cout << "client family : " << clnt_addr.sin_family << endl;
            cout << "client sin zero : " << clnt_addr.sin_zero << endl;
            cout << "client S_addr: " << clnt_addr.sin_addr.S_un.S_addr << endl;
            cout << "client S_addr: " << clnt_addr.sin_addr.S_un.S_un_b.s_b1 << endl;

            cout << "size : " << recv_len << endl << "message : " << buffer << endl;
        }

    }

    return 0;
}