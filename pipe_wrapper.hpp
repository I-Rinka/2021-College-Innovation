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
#ifndef PIPE_WRAPPER_HPP
#define PIPE_WRAPPER_HPP

#define PIPEMODE (S_IRUSR | S_IWUSR)
class Dual_PIPE
{
private:
    const int name_restrict = 100;
    const int msg_restrict = 1000000;
    /* data */
    int fd_send_pipe = 0;
    int fd_recive_pipe = 0;
    char *send_pipe_path;
    char *recive_pipe_path;

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

            //debug

            int read_len = atoi(len);
            std::cout << read_len << std::endl;

            char *buffer = (char *)malloc(read_len);
            read(fd_recive_pipe, buffer, read_len);
            // std::cout <<  << std::endl;

            printf("it will call back!\n");
            free(buffer);
            this->Recive_Callback(buffer);
        }
        async_Read();
    }

    void async_thread()
    {
        //这个切忌不能换位置！
        std::cout << this->recive_pipe_path << std::endl;
        this->fd_recive_pipe = open(this->recive_pipe_path, O_RDONLY);

        if (this->fd_recive_pipe <= -1)
        {
            perror("PIPE NOT OPEN!\n");
        }
        async_Read();
    }

public:
    Dual_PIPE(int send_pipe_fd, int recive_pipe_fd);
    Dual_PIPE(const char *send_pipe_path, const char *recive_pipe_path);
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
            // write(fd_send_pipe, "hello", sizeof("hello"));
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

    if (this->send_pipe_path != NULL)
    {
        unlink(this->send_pipe_path);
        free(this->send_pipe_path);
    }
    if (this->recive_pipe_path != NULL)
    {
        unlink(this->recive_pipe_path);
        free(this->recive_pipe_path);
    }
}

Dual_PIPE::Dual_PIPE(const char *send_pipe_path, const char *recive_pipe_path)
{
    mode_t FIFO_MOD = PIPEMODE;

    if (access(send_pipe_path, R_OK) < 0)
    {
        // 创建一个pipe
        mkfifo(send_pipe_path, FIFO_MOD);
    }

    if (access(recive_pipe_path, R_OK) < 0)
    {
        // 创建一个pipe
        mkfifo(recive_pipe_path, FIFO_MOD);
    }

    this->send_pipe_path = (char *)malloc(strnlen(send_pipe_path, name_restrict));
    this->recive_pipe_path = (char *)malloc(strnlen(recive_pipe_path, name_restrict));

    strncpy(this->send_pipe_path, send_pipe_path, strnlen(send_pipe_path, name_restrict));
    strncpy(this->recive_pipe_path, recive_pipe_path, strnlen(recive_pipe_path, name_restrict));
    // std::thread *thread = new std::thread([this](){});

    std::thread *t = new std::thread([this]() { this->async_thread(); });
    this->fd_send_pipe = open(send_pipe_path, O_WRONLY); //因为写是同步的，因此先把写端开了
}

#endif