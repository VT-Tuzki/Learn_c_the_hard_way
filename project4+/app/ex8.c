#include <stdio.h>

int main(int argc, char* argv[])
{

    int areas[] = {10, 12, 13, 14, 20};
    //areas[3] = 100;
    char name[] = "Cai";
    char full_name[] = {
        'C', 'a', 'i',
        ' ', '.', ' ', ' ',
        'S', 'h', 'u', '\0'
    };
    char full_name_test[] = {
        'C', 'a', 'i',
        ' ', '.', ' ', ' ',
        'S', 'h', 'u'
    };
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

    printf("The size of a char: %ld\n", sizeof(char));
    printf("The size of name (char[]): %ld\n", sizeof(name));
    printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
    printf("The number of chars: %ld\n", sizeof(full_name) / sizeof(char));
    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);



    printf("TEST: name=\"%s\" and full_name=\"%s\"\n", name, full_name_test);

    printf("-----------\n");
    name[1] = areas[2];
    printf("TEST: name=\"%s\" and full_name=\"%s\"\n", name, full_name_test);

    return 0;
}
