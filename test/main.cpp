#include <iostream>
#include <fcntl.h>
#include <unistd.h>
void setNoBlock(int fd)
{
    // 设置文件描述符为非阻塞
    int fl = ::fcntl(fd,F_GETFL);
    if(fl < 0)
    {
        perror("fcntl error");
        return;
    }
    ::fcntl(fd,F_SETFL,fl | O_NONBLOCK);
}
#include <functional>

bool test(const int& left,const int& right)
{
    return left < right;
}
int main()
{
    auto handler = [](int left,int right)->int { return left + right; };

    handler(1,2);

    auto Div = [](int left,int right)->int { return left - right; };

    const std::string path = R"(C:\Users\Name\file.txt)";
    std::cout << path << std::endl;
    
    Div(12,3);
    // 将 读端设置成为非阻塞
    setNoBlock(0);
    while(true)
    {
        char buffer[126] = { 0 };
        int n = ::read(0,buffer,sizeof(buffer) - 1);
        if(n < 0) std::cout << "啥也没读到" << std::endl;
        else {
            buffer[n] = 0;
            std::cout << buffer << std::endl;
        }
        ::sleep(1);
    }
    // this block need a plus pluguin
    return 0;
}