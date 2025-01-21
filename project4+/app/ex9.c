#include <stdint.h>
#include <stdio.h>

#define LEN(x) (sizeof(x) / sizeof(x[0]))

int main(int argc, char *argv[])
{

    int number[4] = {0};
    char name[4] = {'a'};

    for(int i = 0; i < LEN(number); i++) {
        printf("%d ", number[i]);
    }
    printf("\n");

    for(int i = 0; i < LEN(name); i++) {
        printf("%c ", name[i]);
    }
    printf("\n");
    printf("name: %s\n", name);
    for(int i = 1; i <= LEN(number); i++) {
        number[i - 1] = i;
    }

    name[0] = 'C';
    name[1] = 'a';
    name[2] = 'i';
    name[3] = '\0';

    for(int i = 0; i < LEN(number); i++) {
        printf("%d ", number[i]);
    }
    printf("\n");

    for(int i = 0; i < LEN(name); i++) {
        printf("%c ", name[i]);
    }
    printf("\n");
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Cai";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1],
            another[2], another[3]);


    printf("------------------\n");
    //ex1
    number[0] = '1';
    printf("number[0]: %d\n", number[0]);
    //ex2
    name[0] = 100;
    printf("name[0]: %c\n", name[0]);
    //ex3
    printf("name: %s\n", name);
    puts(name);
    for(int i = 0; i < LEN(name); i++) {
        printf("%c ", name[i]);
    }
    printf("\n");
    //ex4
    char number_[4] = {'1', '2', '3', '4'};

    int char_number = 0;
    for(int i = 0; i<(LEN(number_)); i++) {
        char_number = char_number * 10 + (number_[i] - '0');
    }
    printf("char_number: %d\n", char_number);
    //ex6

    for(int i = 0; i < LEN(name); i++) {
        printf("%d ", name[i]);
    }
    printf("\n");


    return 0;
}