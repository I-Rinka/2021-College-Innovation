CC:=g++
PIPE_MODULE:=pipe_wrapper.hpp

test:
	$(CC) client1.cpp $(PIPE_MODULE) -g -lpthread -o client1.out
	$(CC) client2.cpp $(PIPE_MODULE) -g -lpthread -o client2.out