#include <iostream>
#include <string.h>
#include "pipe_wrapper.hpp"
#define PIPE_W "/tmp/T1"
#define PIPE_R "/tmp/T2"
int main(int argc, char const *argv[])
{
    //使用两个管道（读，写），输入地址后类会自动创建与销毁管道
    Dual_PIPE *DP = new Dual_PIPE(PIPE_W, PIPE_R);

    char buffer[100];
    
    while (1)
    {
        scanf("%s", buffer);
        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        DP->Write(buffer);
    }

    delete DP;
    printf("exit process");
    return 0;
}
