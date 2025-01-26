WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
LIB_DIR ?= $(BUILD_DIR)/lib

C_INCLUDES := ${WORK_DIR}/include $(C_INCLUDES)
C_DEFINES := NDEBUG
# complier
CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -Wno-unused -ffunction-sections -fdata-sections -rdynamic \
$(addprefix -I, $(C_INCLUDES)) \
$(addprefix -D, $(C_DEFINES))


#directories
vpath %.c $(sort $(dir $(C_SOURCE_FILES)))
TEST_SRCS = $(wildcard test/*_test.c)
LIB_SRCS = $(wildcard src/**/*.c src/*.c)
#SRCS = $(APP_SRCS) $(COMMON_SRCS) $(TEST_SRCS)

LIB_OBJS = $(patsubst %.c,%.o,$(LIB_SRCS))
TESTS_TARGET = $(patsubst %.c,%,$(TEST_SRC))

TARGET_LIB = $(LIB_DIR)/libvtuzki.a
SO_TARGET_LIB = $(patsubst %.a,%.so,$(TARGET_LIB))


lib_all: build_lib_dir $(TARGET_LIB) $(SO_TARGET_LIB) tests

lib_dev: CFLAGS=-g -Wall -Wall -Wextra $(OPTFLAGS)
lib_dev: lib_all

$(TARGET_LIB): CFLAGS += -fPIC
$(TARGET_LIB): build_lib_dir $(LIB_OBJS)
	ar rcs $@ $(LIB_OBJS)
	ranlib $@

$(SO_TARGET_LIB): $(TARGET_LIB) $(LIB_OBJS)
	$(CC) -shared -o $@ $(LIB_OBJS)


tests: CFLAGS += $(TARGET_LIB)
tests: $(TESTS_TARGET)
	sh ./tests/runtests.sh

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET_LIB) $(DESTDIR)/$(PREFIX)/lib/

build_lib_dir:
	@mkdir -p build
	@mkdir -p build/lib
	@mkdir -p build/obj
	@mkdir -p build/bin
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'

check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(LIB_SRCS) || true

.PHONY: tests
# 保存中间文件
.SECONDARY: