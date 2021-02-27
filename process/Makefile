CC:=g++
PIPE_MODULE:=pipe_wrapper.hpp

demo:
	$(CC) client_read.cpp $(PIPE_MODULE) -g -lpthread -o client_read.out
	$(CC) client_write.cpp $(PIPE_MODULE) -g -lpthread -o client_write.out