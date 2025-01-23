WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

C_INCLUDES := ${WORK_DIR}/include $(C_INCLUDES)

# complier
CC = gcc
CFLAGS = -g -Wall -Wextra -Wno-unused -ffunction-sections -fdata-sections  \
$(addprefix -I, $(C_INCLUDES))


#directories
vpath %.c $(sort $(dir $(C_SOURCE_FILES)))
APP_SRCS = $(shell find app -name "*.c")
COMMON_SRCS = $(shell find src -name "*.c")
SRCS = $(APP_SRCS) $(COMMON_SRCS)

APP_OBJS = $(APP_SRCS:%.c=build/%.o)
COMMON_OBJS = $(COMMON_SRCS:%.c=build/%.o)
OBJS = $(APP_OBJS) $(COMMON_OBJS)

TARGET = $(APP_SRCS:app/%.c=build/%)

#Memory leaks
ifeq ($(MEMCHECK),1)
MEMORY_CHECK_PROG = valgrind --leak-check=full --error-exitcode=1 -q
else ifeq ($(MEMCHECK),2)
MEMORY_CHECK_PROG = valgrind --leak-check=full --error-exitcode=1 --track-origins=yes
endif


all: build_dir $(TARGET)

build/%: build/%.o $(COMMON_OBJS)
	@echo "Linking $@ from $<"
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c
	@echo "Compiling $@ from $<"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

mem_/build/%:
	@echo "Running $(@:mem_/%=%) with memory check"
	$(MEMORY_CHECK_PROG) build/$(@:mem_/build/%=%)

gdb_/build/%:
	@echo "Running $(@:gdb_/%=%) with gdb"
	gdb build/$(@:gdb_/build/%=%)
build_dir:
	@mkdir -p build

clean:
	-rm -rf build $(TARGETS)


.PHONY: all clean mem_/% gdb_/%
