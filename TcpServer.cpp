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

class TcpServer
{
public:
    TcpServer(uint16_t port) : _port(port)
    {
        _sockfd = ::socket(AF_INET,SOCK_STREAM,0); // 
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
        // 监听

        
    }

    bool listen()
    {
        int n = ::listen(_sockfd,8);
        if(n < 0)
        {
            std::cout << "listen error:" << strerror(errno) << std::endl;
            return -1;
        }
        else std::cout << "listen sucessfully" << std::endl;
        return n;
    }
    
    void start()
    {
        // 开始监听
        listen();
        while(_is_running)
        {
            int sockfd = ::accept(_sockfd,)
            char buffer[1024] = { 0 };
            accept(sock_communicate,buffer,)
        }
        
    }
private:
    std::atomic<bool> _is_running;    
    uint16_t _port;
    int _sockfd;
};