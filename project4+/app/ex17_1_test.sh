#!/bin/sh




compile_test() {
    echo "Compile the $1 program"
    pwd
    ./run_test.sh $1

    if [ $? -ne 0 ]; then
        echo "$1 program failed to compile"
        exit 1
    fi
}

run_test_times() {
    echo "Test start , this time max_rows is $1, max_data is $2, and db_file is $3"

    echo "./build/$4 $3 c $1 $2"
    ./build/$4 $3 c $1 $2
    if [ $? -ne 0 ]; then
        echo "$1 program failed to run"
        exit 1
    fi
    tmp=$(($1 - 1))
    for i in $(seq 1 $tmp); do
        echo "./build/$4 $3 s $i $i $i"
        ./build/$4 $3 s $i $i $i
        if [ $? -ne 0 ]; then
            echo "$1 program failed to run"
            exit 1
        fi
    done

    ./build/$4 $3 l
    if [ $? -ne 0 ]; then
        echo "$1 program failed to run"
        exit 1
    fi

    for i in $(seq $tmp 1); do
        ./build/$4 $3 d $i
        if [ $? -ne 0 ]; then
            echo "$1 program failed to run"
            exit 1
        fi
    done

    ./build/$4 $3 l
    if [ $? -ne 0 ]; then
        echo "$1 program failed to run"
        exit 1
    fi
}

run_test() {
    echo "Test start"

    for i in $(seq 10 100); do
        run_test_times $i $i "./build/db_$i.dat" ex17_1
    done
}


compile_test ex17_1

echo "Test start"

run_test
