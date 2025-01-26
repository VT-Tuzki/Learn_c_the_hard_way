WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
PREFIX_DIR ?= /usr/local

C_INCLUDES := ${WORK_DIR}/include $(C_INCLUDES)
C_INCLUDES := ${PREFIX_DIR}/apr/include/apr-1 $(C_INCLUDES)
C_INCLUDES := ${PREFIX_DIR}/apr/include/apr-util-1 $(C_INCLUDES)
C_DEFINES := NDEBUG
# complier
CC = gcc
CFLAGS = -g -Wall -Wextra -Wno-unused -ffunction-sections -fdata-sections  \
$(addprefix -I, $(C_INCLUDES)) \
$(addprefix -D, $(C_DEFINES)) \

LDFLAGS = -L$(PREFIX_DIR)/apr/lib -lapr-1 -laprutil-1


#directories
vpath %.c $(sort $(dir $(C_SOURCE_FILES)))
APP_SRCS = $(shell find app -name "*.c")
COMMON_SRCS = $(shell find src -name "*.c")
SRCS = $(APP_SRCS) $(COMMON_SRCS)

APP_OBJS = $(APP_SRCS:%.c=build/obj/%.o)
COMMON_OBJS = $(COMMON_SRCS:%.c=build/obj/%.o)
OBJS = $(APP_OBJS) $(COMMON_OBJS)

TARGET = $(APP_SRCS:app/%.c=build/bin/%)


all: build_dir $(TARGET)

build/bin/%: build/obj/%.o $(COMMON_OBJS)
	@echo "Linking $@ from $<"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

build/obj/%.o: %.c | build_dir
	@echo "Compiling $@ from $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

build_dir:
	@mkdir -p build
	@mkdir -p build/bin
	@mkdir -p build/obj
clean:
	@-rm -rf build

.PHONY: all clean
# 保存中间文件
.SECONDARY: