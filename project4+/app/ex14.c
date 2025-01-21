#include <stdio.h>
#include <ctype.h>
#include <string.h>

int can_print_it(char ch);
void print_arguments(int argc, char *argv[]);
void print_letters(char arg[]);

int can_print_it(char ch) {
    return isalpha(ch) || isblank(ch);
}

void print_arguments(int argc, char *argv[]) {
    int i = 0;

    for(i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
}

void print_letters(char arg[]) {
    //ex2
    int length = strlen(arg);
    for (int i = 0; i < length; i++) {
        char ch = arg[i];
        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
        //ex1
        // if (isalpha(ch) || isblank(ch)) {
        //     printf("'%c' == %d ", ch, ch);
        // }
        //ex3
        // if ((ch >= 'a' && ch <= 'z') || (ch>='A' && ch<='Z') || (ch == ' ') ) {
        //     printf("'%c' == %d ", ch, ch);
        // }
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}