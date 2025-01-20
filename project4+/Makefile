
CC = gcc
CFLAGS = -Wall -g
vpath %.c app src
APP_SRCS = $(shell find app -name "*.c")
COMMON_SRCS = $(shell find src -name "*.c")
SRCS = $(APP_SRCS) $(COMMON_SRCS)

APP_OBJS = $(APP_SRCS:%.c=build/%.o)
COMMON_OBJS = $(COMMON_SRCS:%.c=build/%.o)
OBJS = $(APP_OBJS) $(COMMON_OBJS)

TARGET = $(APP_SRCS:app/%.c=build/%)

all: build_dir $(TARGET)

build/%: build/%.o $(COMMON_OBJS)
	@echo "Linking $@ from $<"
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c
	@echo "Compiling $@ from $<"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

build_dir:
	@mkdir -p build

clean:
	-rm -rf build $(TARGETS)


.PHONY: all clean
