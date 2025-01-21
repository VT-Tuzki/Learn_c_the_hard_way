#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }


    int i = 0;
    for (char letter = argv[1][0],i = 0 ; argv[1][i] != '\0'; i++) {
        letter = argv[1][i];
        if(letter >= 'A' && letter <= 'Z') {
            letter = letter + 32;
        }
        switch (letter) {
            case 'a':
                printf("%d: 'A'\n", i);
                break;

            case 'e':
                printf("%d: 'E'\n", i);
                break;

            case 'i':
                printf("%d: 'I'\n", i);
                break;

            case 'o':
                printf("%d: 'O'\n", i);
                break;

            case 'u':
                printf("%d: 'U'\n", i);
                break;

            case 'y':
                if(i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                    printf("begin if break\n");
                    break;
                    printf("end if break\n");
                }
                printf("end if break\n");
                break;
                printf("end case break\n");
            default:
                printf("%d: %c is not a vowel\n", i, letter);
        }

    }
    return 0;
}