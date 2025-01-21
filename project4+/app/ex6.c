#include <stdio.h>

int main( int argc, char* argv[])
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char inital = 'A';
    char frist_name[] = "Shu";
    char last_name[] = "Cai";

    printf("You are %d miles away.\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an inital %c.\n", inital);
    printf("I have a first name %s.\n", frist_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c. %s.\n", frist_name, inital, last_name);

    printf("Left aligned test  \"%-10d\"\n", distance); // only Left aligned add -
    printf("Right aligned test \"%10d\"\n", distance);

    printf("Left aligned test double,2   \"%-10.2f\"\n", power); // only Left aligned add -
    printf("Left aligned test double,3   \"%-10.3f\"\n", power); // only Left aligned add -
    printf("Left aligned test double,4   \"%-10.4f\"\n", power); // only Left aligned add -
    printf("Right aligned test double,2  \"%10.2f\"\n", power); // only Left aligned add -

    printf("I am number of DEC %d, OCT %o,  HEX %x\n", distance, distance, distance);
    printf("And My Binary is ");
    for (int i = sizeof(distance) * 8 - 1; i >= 0; i--)
    {
        printf("%d", (distance >> i) & 1);
    }
    printf("\n");
    printf("->");
    printf(""); // nothing
    printf("<-\n");
    return 0;
}