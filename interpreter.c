#include <stdio.h>

int main(int argc, char *argv[])
{

    // Reading parameters
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./a.out <inputFile>\n");
        return 1;
    }

    // Opening file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return 2;
    }

    // Reading characters from file
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
    }

    // Closing file
    fclose(file);
    return 0;
}