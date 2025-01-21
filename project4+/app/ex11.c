#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    while(i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }

    int number = 4;
    i = 0;
    while(i < number) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }

    //ex1
    i = argc - 1;
    while(i >= 0) {
        printf("arg %d: %s\n", i, argv[i]);
        //ex3
        if(i < 4) {
        //ex2
            states[i] = argv[i];
        }
        i--;
    }

    i = 0;
    while(i < number) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }
    return 0;
}