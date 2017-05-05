srcs := $(wildcard *.cpp)
objects := $(patsubst %.cpp, %.o, $(srcs))
CC = g++
main: $(objects)
	$(CC) -o main $(objects)
.PHONY: clean
clean:
	-rm $(objects) main
