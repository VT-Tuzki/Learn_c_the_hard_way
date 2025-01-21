#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    argv[0] = states[0];
    for(i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }



    int number = 4;
    states[0] = NULL;
    for(int i = 0; i < number; i++) {
        printf("state %d: %s\n", i, states[i]);
    }



    return 0;
}