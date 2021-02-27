#include <iostream>
#include "pipe_wrapper.hpp"
#define PIPE_W "/tmp/T_PIPE1"
#define PIPE_R "/tmp/T_PIPE2"
int main(int argc, char const *argv[])
{
    Dual_PIPE DP(PIPE_W, PIPE_R);

    DP.Write("hello!\n\0");
    return 0;
}
