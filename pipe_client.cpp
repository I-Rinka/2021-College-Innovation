#include "pipe_module.hpp"
#define in_pipe "IP"
#define out_pipe "OP"
#include <iostream>

int main(int argc, char const *argv[])
{
    Dual_PIPE P(in_pipe, out_pipe);
    P.Recive_Callback = [](const char *line) {
        std::cout << line;
    };
    char *buffer = (char *)malloc(10000);
    while (1)
    {
        std::cin >> buffer;
        memset(buffer,1,10000);
        P.Write(buffer);
    }

    return 0;
}
