#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>
#define FIFO_NAME "MY_PIPE"
int main(int argc, char const *argv[])
{
    mode_t FIFO_MOD = 0777;

    mkfifo(FIFO_NAME, FIFO_MOD);

    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1)
    {
        printf("fd less than 0\n");
        return 0;
    }
    char hello[10];
    while (1)
    {
        fgets(hello, sizeof(hello), stdin);
        write(fd, hello, sizeof(hello));
        if (strcmp(hello,"exit\n1")==0)
        {
            break;
        }
        
    }
    close(fd);
    remove(FIFO_NAME);
    return 0;
}
