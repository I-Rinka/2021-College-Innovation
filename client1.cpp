#include <iostream>
#include <string.h>
#include "pipe_wrapper.hpp"
#define PIPE_W "/tmp/T_PIPE1"
#define PIPE_R "/tmp/T_PIPE2"
int main(int argc, char const *argv[])
{
    Dual_PIPE DP(PIPE_W, PIPE_R);

    char buffer[100];
    while (1)
    {
        scanf("%s", buffer);
        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        DP.Write(buffer);
    }

    return 0;
}
