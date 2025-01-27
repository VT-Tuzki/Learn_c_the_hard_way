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

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void Print_person(struct Person *who)
{
    assert(who != NULL);
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main (int argc, char *argv[])
{
    struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
    struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

    printf("Joe is at memory location %p:\n", joe);
    Print_person(joe);

    printf("Frank is at memory location %p:\n", frank);
    Print_person(frank);

    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Print_person(joe);

    frank->age += 21;
    frank->weight += 20;
    Print_person(frank);

    person_destroy(joe);
    person_destroy(frank);

    return 0;
}