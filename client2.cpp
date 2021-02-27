#include <iostream>
#include <functional>
#include "pipe_wrapper.hpp"
#define PIPE_W "/tmp/T_PIPE1"
#define PIPE_R "/tmp/T_PIPE2"
int main(int argc, char const *argv[])
{
    Dual_PIPE DP(PIPE_R, PIPE_W);

    std::function<void(const char *)> p = [](const char *get) {
        std::cout << "Recived a message!";
        std::cout << get;
    };

    DP.Recive_Callback = p;

    return 0;
}