#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <atomic>
#include <cstring>

#define SOCKINTOSCOK(PTR) (struct sockaddr*)(PTR)
#define TYPETOCHAR(PTR) (char*)(PTR)


class UdpServer
{
public:

    UdpServer(uint16_t port) : _port(port)
    {
        _sockfd = ::socket(AF_INET,SOCK_DGRAM,0); // 
        if(_sockfd < 0)
        {
            perror("socket create error:");
            ::exit(1);
        }
        // bind套接字
        struct sockaddr_in sock;
        sock.sin_addr.s_addr = INADDR_ANY;
        sock.sin_family = AF_INET;
        sock.sin_port = ::htons(port);

        int n = ::bind(_sockfd,SOCKINTOSCOK(&sock),sizeof(sock));
        if(n < 0){
            perror("bind error:");
            ::exit(1);
        }
        else std::cout << "bind success" << std::endl;
        //
    }

    // 启动UDP客户端
    void start()
    {
        _is_running = true;
        while(_is_running)
        {
            // 不断的接受数据
            struct sockaddr_in peer;
            ::bzero(TYPETOCHAR(&peer),sizeof(peer));
            char buffer[1024] = { 0 };
            socklen_t len = sizeof(peer);
            int n = ::recvfrom(_sockfd,buffer,sizeof(buffer) - 1,0,SOCKINTOSCOK(&peer),&len);
            if(n < 0)
            {
                std::cout << "recv error";
            }
            else
            {
                buffer[n] = 0;
                std::cout << "received message:" << buffer << std::endl;
            }
        }
    }
private:
    uint16_t _port;
    std::atomic<bool> _is_running;
    int _sockfd;
};


int main()
{
    uint16_t port = 8080;
    UdpServer server(port);
    server.start();
    return 0;
}