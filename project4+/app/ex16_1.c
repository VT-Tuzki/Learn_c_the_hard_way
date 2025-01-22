#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

void person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

//ex3
void Print_person(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main (int argc, char *argv[])
{
    //ex1
    struct Person joe = {
        .name = "Joe Alex",
        .age = 32,
        .weight = 72,
        .height = 180,
    };
    struct Person frank = {
        .name = "Frank Blank",
        .age = 20,
        .weight = 70,
        .height = 170,
    };

    printf("Joe is at memory location %p:\n", &joe);
    Print_person(joe);

    printf("Frank is at memory location %p:\n", &frank);
    Print_person(frank);

    //ex2
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Print_person(joe);

    frank.age += 21;
    frank.weight += 20;
    Print_person(frank);

    // 不需要
    // person_destroy(&joe);
    // person_destroy(&frank);

    return 0;
}