CC=g++
CFLAGS=-Wall
all: exe lib

exe: hello.h main.cpp lib
	$(CC) $(CFLAGS) main.cpp -fPIC -L. -lHello -o hello

lib: hello.h hello.cpp
	$(CC) $(CFLAGS) -shared hello.cpp -fPIC -o libHello.so

clean:
	- rm hello libHello.so 2>/dev/null
