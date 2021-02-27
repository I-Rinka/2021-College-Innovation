#include <iostream>
#include <functional>
#include "pipe_wrapper.hpp"
#define PIPE_W "/tmp/T_PIPE1"
#define PIPE_R "/tmp/T_PIPE2"
int main(int argc, char const *argv[])
{
    Dual_PIPE DP(PIPE_R, PIPE_W);

    DP.Recive_Callback = [](const char *get) {
        std::cout << "Recived a message!";
        std::cout << get;
    };

    return 0;
}