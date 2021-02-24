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
    Dual_PIPE(const char *send_pipe_name, const char *recive_pipe_name);
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
            printf("writing..\n");

            char len[10];
            int write_lengh = strnlen(input, msg_restrict);
            snprintf(len, 10, "%9d", write_lengh);
            write(fd_send_pipe, len, 10);
            write(fd_send_pipe, input, write_lengh);
        }
    }
};

Dual_PIPE::Dual_PIPE(const char *send_pipe_name, const char *recive_pipe_name)
{
    mode_t FIFO_MOD = 0777;

    mkfifo(send_pipe_name, FIFO_MOD);
    mkfifo(recive_pipe_name, FIFO_MOD);
    this->send_pipe_name = (char *)malloc(strnlen(send_pipe_name, name_restrict));
    this->recive_pipe_name = (char *)malloc(strnlen(recive_pipe_name, name_restrict));

    this->fd_recive_pipe = open(recive_pipe_name, O_RDONLY);
    this->fd_send_pipe = open(send_pipe_name, O_WRONLY);


    strncpy(this->send_pipe_name, send_pipe_name, strnlen(send_pipe_name, name_restrict));
    strncpy(this->recive_pipe_name, recive_pipe_name, strnlen(recive_pipe_name, name_restrict));
    // std::thread *thread = new std::thread([this](){});
    std::thread *t = new std::thread([this]() { this->async_Read(); });
}

Dual_PIPE::~Dual_PIPE()
{
    remove(send_pipe_name);
    remove(recive_pipe_name);

    close(this->fd_send_pipe);
    close(this->fd_recive_pipe);

    free(send_pipe_name);
    free(recive_pipe_name);
}
