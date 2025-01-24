#include <stdio.h>
#include <../include/ex22.h>
#include <../include/dbg.h>

int THE_SIZE = 1000;

int get_age()
{
    return THE_SIZE;
}

void set_age(int age)
{
    THE_SIZE = age;
}

double update_ratio(double new_ratio)
{
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

double update_ratio_ex2(double new_ratio, double **test_ratio_ptr)
{
    static double ratio = 1.0;
    *test_ratio_ptr = &ratio;
    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

void print_size()
{
    log_info("I think size is: %d", THE_SIZE);
}
