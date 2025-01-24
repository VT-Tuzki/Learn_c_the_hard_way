#!/bin/bash
# sh run_test.sh $1 $2 $3
# $1: 1 - build all apps, other -> build app/$1.c
# $2: 1 - use MEMCHECK lite, 2 - use MEMCHECK full, other -> no MEMCHECK
# $3: 1 - use GDB, other -> no GDB

# Golbal variables
WORK_DIR=$(pwd)
APP_DIR=$WORK_DIR/app
BUILD_DIR=$WORK_DIR/build
BIN_DIR=$BUILD_DIR/bin
# make rules
MAKE_RULES=""
DISPLAY_MAKE_TARGET=""

# MEMCHECK
MEMCHECK=""
DISPLAY_MEMCHECK="MEMCHECK: none"
ERRORS=()
# GDB
GDB=""
GDB_RULES=""
DISPLAY_GDB="GDB: none"


print_color() {
    local color=$1
    local text=$2
    echo -e "\033[${color}m${text}\033[0m"
}

make_target() {
    if [ -z "$1" ]; then
        echo "No file. \$1 is a *.c name from directory "app" or 1"
        exit 1
    fi

    if [ "$1" = "1" ]; then
        MAKE_RULES="all"
        DISPLAY_MAKE_TARGET="all apps"
    else
        find $APP_DIR -type d -name $1
            if [ $? -ne 0 ]; then
                echo "No file. \$1 is a *.c name from directory "app""
                exit 1
            fi
        MAKE_RULES="build/bin/$1"
        DISPLAY_MAKE_TARGET="app/$1.c"
    fi
}

make_() {
    print_color 33 "[BUILD] "$DISPLAY_MAKE_TARGET
    make clean
    make –debug=basic $MAKE_RULES || exit 1
    print_color 32 "[BUILD] "$DISPLAY_MAKE_TARGET" done."
}

mem_check() {
    if [ -z "$1" ]; then
        MEMCHECK=""
        DISPLAY_MEMCHECK="[MEMCHECK] none"
        return
    fi

    if [ "$1" = "1" ]; then
        MEMCHECK="MEMCHECK=1"
        DISPLAY_MEMCHECK="[MEMCHECK] less"
    elif [ "$1" = "2" ]; then
        MEMCHECK="MEMCHECK=2"
        DISPLAY_MEMCHECK="[MEMCHECK] full"
    else
        echo "\$2 is only 1 or 2 or nothing"
        exit 1
    fi
}

mem_() {
    if [ -z "$MEMCHECK" ]; then
        print_color 33 "[MEMCHECK] none memcheck"
        return
    fi
    print_color 33 "$DISPLAY_MEMCHECK start."
    mkdir -p $BUILD_DIR/valgrind

    make_mem_or_gdb $MAKE_RULES $MEMCHECK "mem_"

    print_color 32 "$DISPLAY_MEMCHECK done."
}

gdb_check() {
    if [ -z "$1" ]; then
        GDB_RULES=""
        DISPLAY_GDB="BUILD"
        return
    fi

    if [ "$1" = "1" ]; then
        GDB_RULES="GDB=1"
        DISPLAY_GDB="GDB"
    else
        echo "\$3 is only 1 or nothing"
        exit 1
    fi

    if [ $MAKE_RULES = "all" ]; then
        print_color 33 "gdb: It is best to open only one program"
        exit 1
    fi

}

gdb_() {
    if [ -z "$GDB_RULES" ]; then
        print_color 33 "[GDB] none gdb"
        return
    fi
    print_color 33 "[GDB] "$DISPLAY_GDB
    make_mem_or_gdb $MAKE_RULES $GDB_RULES "gdb_"|| exit 1
}



mem_error_print() {
    if [ "$1" = "gdb_" ]; then
        return
    fi

    if [ ${#ERRORS[@]} -ne 0 ]; then
        print_color 31 "[MEMCHECK] error list"
        for error in ${ERRORS[@]}; do
            print_color 31 "$error-->   $BUILD_DIR/valgrind/$error.log"
        done
    fi
}

# $1: make rules(target) $2: other rules
make_mem_or_gdb() {
    if [ "$1" = "all" ]; then
        for file in $(ls $BIN_DIR); do
            print_color 33 "[$3] bin/$file"
            make -B $3/build/bin/$file $2
            MAKE_RETVAL=$?
            if [ $MAKE_RETVAL -ne 0 ]; then
                print_color 31 "[$3] bin/$file failed"
                ERRORS+=("$file")
            fi
        done
    else
        print_color 33 "[$3] "$1
        make -B $3/$1 $2
        MAKE_RETVAL=$?
        if [ "$3" = "gdb_" ]; then
            return
        fi
        if [ $MAKE_RETVAL -ne 0 ]; then
            print_color 31 "[$3] "$1" failed"
            print_color 31 "[$3]  $BUILD_DIR/valgrind/${1##*/}.log"
        else
            print_color 32 "[$3]  $BUILD_DIR/valgrind/${1##*/}.log"
        fi
    fi

    mem_error_print $3
}

run_check() {
    make_target $1
    mem_check $2
    gdb_check $3
}

run_test() {
    make_
    mem_
    gdb_
    echo
    print_color 32 "ALL test done."
    exit 0
}

run_check "$1" "$2" "$3"
run_test "$DISPLAY_GDB" "$DISPLAY_MAKE_TARGET" "$DISPLAY_MEMCHECK"


