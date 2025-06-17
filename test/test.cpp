#include <iostream>

// 

template <class T>
T plusAllHelper() { return T(); }

template <class T,class ...Args>
T plusAllHelper(T&& value, Args&&... args)
{
    return value + plusAllHelper(std::forward<Args>(args)...);
}

template <class T,class ...Args>
T plusAll(Args&&... args)
{
    return plusAllHelper(std::forward<Args>(args)...);
}

int main()
{
    auto t = plusAll<int>(1,2,3);
    std::cout << t << std::endl;
    return 0;
}