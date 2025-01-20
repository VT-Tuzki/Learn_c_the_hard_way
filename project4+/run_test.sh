# sh run_test.sh $1 $2 $3
# $1: 1 - build all apps, other -> build app/$1.c
# $2: 1 - use MEMCHECK lite, 2 - use MEMCHECK full, other -> no MEMCHECK
# $3: 1 - use GDB, other -> no GDB

WORK_DIR=$(pwd)
APP_DIR=$WORK_DIR/app
BUILD_DIR=$WORK_DIR/build
MAKE_RULES=""
DISPLAY_MAKE_TARGET=""
MEMCHECK=""
DISPLAY_MEMCHECK="MEMCHECK: none"
GDB=""
GDB_RULES=""
DISPLAY_GDB="GDB: none"

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
        MAKE_RULES="build/$1"
        DISPLAY_MAKE_TARGET="app/$1.c"
    fi
}

make_() {
    echo "\033[33m [BUILD] "$DISPLAY_MAKE_TARGET"\033[0m"
    make clean
    make $MAKE_RULES || exit 1
    echo "\033[33m [BUILD] "$DISPLAY_MAKE_TARGET" done.\033[0m"
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
        echo "\033[33m [MEMCHECK] none memcheck \033[0m"
        return
    fi
    echo "\033[33m [MEMCHECK] "$DISPLAY_MEMCHECK"\033[0m"
    make_mem_or_gdb $MAKE_RULES $MEMCHECK "mem_"|| exit 1
    echo "\033[33m [MEMCHECK] "$DISPLAY_MEMCHECK" done.\033[0m"
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
        echo "\033[33m  gdb: It is best to open only one program\033[0m"
        exit 1
    fi

}

gdb_() {
    if [ -z "$GDB_RULES" ]; then
        echo "\033[33m [GDB] none gdb \033[0m"
        return
    fi
    echo "\033[33m [GDB] "$DISPLAY_GDB"\033[0m"
    make_mem_or_gdb $MAKE_RULES $GDB_RULES "gdb_"|| exit 1
}

# $1: make rules(target) $2: other rules
make_mem_or_gdb() {
    if [ "$1" = "all" ]; then
        for file in $(ls $BUILD_DIR); do
            echo "\033[33m [$3] "build/$file "\033[0m"
            make -B $3/build/$file $2
            MAKE_RETVAL=$?
            if [ $MAKE_RETVAL -ne 0 ]; then
                echo "\033[31m [$3] "build/$file "failed\033[0m"
                exit 1
            fi
        done
    else
        echo "\033[33m [$3] "$1"\033[0m"
            make -B $3/$1 $2
            MAKE_RETVAL=$?
            if [ $MAKE_RETVAL -ne 0 ]; then
                echo "\033[31m [$3] "$1 "failed\033[0m"
                exit 1
        fi
    fi
}

run_check() {
    make_target $1
    mem_check $2
    gdb_check $3
}

run_test() {
    #echo "\033[33m [$1] "$2" "$3"\033[0m"
    make_
    mem_
    gdb_
    echo
    echo ALL test done.
    exit 0
}

run_check "$1" "$2" "$3"
run_test "$DISPLAY_GDB" "$DISPLAY_MAKE_TARGET" "$DISPLAY_MEMCHECK"


