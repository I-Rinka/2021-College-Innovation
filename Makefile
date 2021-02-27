CC:=g++
PIPE_MODULE:=pipe_wrapper.hpp

test:
	$(CC) client1.cpp $(PIPE_MODULE) -lpthread -o -g client1.out
	$(CC) client2.cpp $(PIPE_MODULE) -lpthread -o -g client2.out