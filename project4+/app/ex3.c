#include <stdio.h>

int main(int argc, char* argv[])
{
	int age = 10;
	//int age;	// 随机数在21000~ 22500之间
	int height = 72;


	printf("I am %d years old\n", age); //

	// printf("I am %d years old\n", &age); //
	// printf("I am %d years old\n");	// formate %d no value

	printf("I am %d inches tall\n", height);

	return 0;
}
