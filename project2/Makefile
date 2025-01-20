
CC = gcc
CFLAGS=-Wall -g

TARGET = build/ex1
SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:%.c=build/%.o)


all:build_dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


build/%.o: %.c | build_dir
	$(CC) $(CFLAGS) -c -o $@ $<

build_dir:
	@mkdir -p build

clean:
	-rm -rf build


.PHONY: all clean
