#include "pipe_module.hpp"
#define in_pipe "OP"
#define out_pipe "IP"
#include <iostream>
void printl(const char *line)
{
    std::cout << line << std::endl;
}
int main(int argc, char const *argv[])
{

    mode_t FIFO_MOD = 0777;

    mkfifo(in_pipe, FIFO_MOD);
    mkfifo(out_pipe, FIFO_MOD);

    Dual_PIPE P(in_pipe, out_pipe);

    P.Recive_Callback = [](const char *line) {
        std::cout << line;
    };
    char *buffer = (char *)malloc(10000);

    while (1)
    {
        // std::cin >> buffer;
        scanf("%s", buffer);
        printf("%s", buffer);
        P.Write(buffer);
        memset(buffer, 1, 10000);
    }

    return 0;
}