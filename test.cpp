#include <iostream>
#include <tuple>
enum 
{
    INT_1,
    INT_2,
};
int main()
{
    std::tuple<int,int> t = std::make_tuple(1,1);
    std::get<INT_1>(t);
    return 0;
}