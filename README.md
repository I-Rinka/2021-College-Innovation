# 2021-College-Innovation

## 进程异步通信

在`/process`目录中，为进程异步通信模块

其中`/process/pipe_wrapper.hpp`实现了对读写双工管道的封装，`/process/client_read.cpp`为读端的异步调用的demo，`/process/client_write.cpp`为写端异步调用的demo

在`/process`文件夹下使用如下命令编译得到demo：

```c++
make demo
```

### python实现

为了灵活起见，python目前并没有实现类的封装

`/process/pipe_demo.py`为python与C++进程间管道异步通信的demo，使用python解码了管道包头和数据体

运行进程间交互demo的具体流程如下：

1. `make demo`编译C++程序
2. `client_write.out`运行C++程序的进程
3. `python3 /process/pipe_demo.py`运行python进程
4. 在C++的`client_write.out`进程的终端进行输入，再在`python`的终端中查看输出

其整体实现想法与地空通信的network部分相似：接收线程阻塞，进行异步通信；写线程总是同步写入数据
