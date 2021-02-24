#include "pipe_wrapper.hpp"
#define in_pipe "send_pipe"
#define out_pipe "get_pipe"
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

    // open(in_pipe, O_WRONLY);
    // open(in_pipe, O_WRONLY);
    int fd1 = open(in_pipe, O_WRONLY);//必须要有另一个打开这个管道才行
    // int fd2 = open(in_pipe, O_RDONLY|O_NONBLOCK);

    Dual_PIPE P(fd1, fd1);

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