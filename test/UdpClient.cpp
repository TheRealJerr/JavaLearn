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


class UdpClient
{
public:
    UdpClient(const std::string& ip,uint16_t port) : 
        _ip(ip) , _port(port)
    {
        _sockfd = ::socket(AF_INET,SOCK_DGRAM,0); // 
        if(_sockfd < 0)
        {
            perror("socket create error:");
            ::exit(1);
        }
        // // bind套接字
        // struct sockaddr_in sock;
        // sock.sin_addr.s_addr = inet_addr(_ip.c_str());
        // sock.sin_family = AF_INET;
        // sock.sin_port = ::htons(port);

        // int n = ::bind(_sockfd,SOCKINTOSCOK(&sock),sizeof(sock));
        // if(n < 0){
        //     perror("bind error:");
        //     ::exit(1);
        // }
        // else std::cout << "bind success" << std::endl;
    }

    void start()
    {
        _is_running = true;
        struct sockaddr_in sock;
        sock.sin_addr.s_addr = inet_addr(_ip.c_str());
        sock.sin_family = AF_INET;
        sock.sin_port = ::htons(_port);
        while(_is_running)
        {
            std::string message;
            std::cout << "what do you want to send:";
            std::cin >> message;
            int n = ::sendto(_sockfd,(void*)(message.c_str()),message.size(),0,SOCKINTOSCOK(&sock),sizeof(sock));
            if(n < 0) std::cout << "发送失败" << std::endl;
        }
    }
private:
    const std::string _ip;
    uint16_t _port;
    std::atomic<bool> _is_running;
    int _sockfd;
};

int main()
{
    UdpClient client("127.0.0.1",8080);
    client.start();
    return 0;
}