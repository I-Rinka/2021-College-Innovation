#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    
    
    int fd = open("MY_PIPE", O_RDONLY);
    if (fd == -1)
    {
        printf("fd less than 0\n");
        return 0;
    }
    char hello[10];
    while (1)
    {
        read(fd, hello, sizeof(hello));
        puts(hello);
    }
    close(fd);
    return 0;
}
