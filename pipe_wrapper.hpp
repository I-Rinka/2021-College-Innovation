#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <functional>
#include <thread>
#include <iostream>

class Dual_PIPE
{
private:
    const int name_restrict = 100;
    const int msg_restrict = 1000000;
    /* data */
    int fd_send_pipe = 0;
    int fd_recive_pipe = 0;
    char *send_pipe_name;
    char *recive_pipe_name;

    void async_Read()
    {
        if (this->fd_send_pipe <= -1)
        {
            perror("PIPE NOT OPEN!\n");
        }
        else
        {
            char len[10];
            read(fd_recive_pipe, len, 10);
            std::cout << len << std::endl;
            int read_len = atoi(len);

            char *buffer = (char *)malloc(read_len);
            read(fd_recive_pipe, buffer, read_len);

            this->Recive_Callback(buffer);

            free(buffer);
        }
        async_Read();
    }

public:
    Dual_PIPE(int send_pipe_fd, int recive_pipe_fd);
    ~Dual_PIPE();
    std::function<void(const char *)> Recive_Callback;
    void Write(const char *input)
    {
        if (this->fd_send_pipe <= -1)
        {
            perror("PIPE NOT OPEN!\n");
        }
        else
        {

            char len[10];
            int write_lengh = strnlen(input, msg_restrict);
            snprintf(len, 10, "%9d", write_lengh);
            // printf("writing..%s\n",len);
            write(fd_send_pipe, len, 10);
            write(fd_send_pipe, input, write_lengh);
        }
    }
};

Dual_PIPE::Dual_PIPE(int send_pipe_fd, int recive_pipe_fd)
{

    this->fd_send_pipe = send_pipe_fd;
    this->fd_recive_pipe = recive_pipe_fd;

    std::thread *t = new std::thread([this]() { this->async_Read(); });
}

Dual_PIPE::~Dual_PIPE()
{
    close(this->fd_send_pipe);
    close(this->fd_recive_pipe);

}
