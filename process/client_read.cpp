#include <iostream>
#include <functional>
#include "pipe_wrapper.hpp"
#define PIPE_W "/tmp/T1"
#define PIPE_R "/tmp/T2"
int main(int argc, char const *argv[])
{
    Dual_PIPE DP(PIPE_R, PIPE_W);

    //接受信息的回调函数注册
    DP.Recive_Callback = [](const char *get, int size) {
        // std::cout << "Recived a message!";
        std::cout << "recive size:" << strlen(get) << " " << size << '\n';
        std::cout << get << std::endl;
    };

    while (1)
    {
        //do something 因为不能让进程提前return0，因此这边套了个循环
    }

    return 0;
}