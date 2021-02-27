import os
import threading
import time

pipe_name_W = "/tmp/T2"
pipe_name_R = "/tmp/T1"


def async_thread():
    fd_R = os.open(pipe_name_R, os.O_RDONLY)
    while True:
        #数据包格式：字符串大小 + 本体
        #需要通过如下骚操作解析包头的大小，并最终读出本体
        len = os.read(fd_R, 10)
        len=len.decode('ascii').lstrip().strip(b'\x00'.decode())
        len=int(len)


        msg=os.read(fd_R,len)#这里的msg类型是byte

        utf8_msg=msg.decode('utf8')#正常处理
        print(utf8_msg)

        #在这里实现回调函数之类的
        

#主函数

#先开异步线程再开同步线程的管道，否则会死锁
th=threading.Thread(target=async_thread)
th.start()
fdW = os.open(pipe_name_W, os.O_WRONLY)

#主线程
print("other thread")

while True:
    time.sleep(3)
    print("hello")

th.join()

