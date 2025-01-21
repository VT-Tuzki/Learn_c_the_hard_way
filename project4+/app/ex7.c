#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int main (int argc, char *argv[])
{
    int bugs = 100;
    double bug_rate = 1.2;

    printf("%d bugs ,rate of %f\n", bugs, bug_rate);

    unsigned long universe_of_defects = UINT32_MAX;
    printf("%ld bugs\n",universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    printf("%f bugs\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    printf("a %e portion\n", part_of_universe);

    char nul_byte = '\0';
    int care_percentage = bugs * nul_byte;
    printf("%d %%\n", care_percentage);

    printf("%%c:%d %%\n", nul_byte);
    printf("%%c:%c %%\n", nul_byte);
    printf("%%s:%s %%\n", nul_byte);
    return 0;
}