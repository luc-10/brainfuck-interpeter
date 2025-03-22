#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "stack.h"

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    // Reading parameters
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./a.out <inputFile>\n");
        return 1;
    }

    // Opening file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 2;
    }

    int ptr = 0;
    unsigned char buffer[BUFFER_SIZE] = {0};
    int fileOffset = 0;

    // Reading characters from file
    ssize_t bytesRead;
    char c;
    while ((bytesRead = read(fd, &c, 1)) > 0)
    {
        switch (c)
        {
        case '+':
            // If + we increase the value
            ++buffer[ptr];
            break;
        case '-':
            // If - we decrease the value
            --buffer[ptr];
            break;
        case '>':
            // If > we move to the right
            ++ptr;

            // Make sure that we are stil in the buffer
            ptr %= BUFFER_SIZE;
            break;
        case '<':

            // If < we move to the left
            --ptr;

            // Make sure that we are still in the buffer
            ptr += BUFFER_SIZE;
            ptr %= BUFFER_SIZE;
            break;
        case '[':
            // If [ we are possibly entering a loop

            // If we are on a cell with value 0 we exit the loop
            if (buffer[ptr] == 0)
            {
                int openBrackets = 1;
                while (openBrackets > 0)
                {
                    read(fd, &c, 1);
                    if (c == '[')
                        openBrackets++;
                    else if (c == ']')
                        openBrackets--;
                }
            }
            // Otherwise we save the position
            else
            {
                push(fileOffset);
            }
            break;
        case ']':
            // If ] we are going back to the closest [ unless the cell's value is 0
            if (buffer[ptr] != 0)
            {
                fileOffset = top();
                lseek(fd, fileOffset, SEEK_SET);
            }
            else
            {
                if (!empty())
                {
                    // If we are exiting the loop we remove the saved position
                    pop();
                }
            }
            break;
        case '.':
            // If . we print
            printf("%c", buffer[ptr]);
            break;
        case ',':
            // If , we read
            scanf("%c", &buffer[ptr]);
            break;
        }

        ++fileOffset;
    }
    printf("\n");

    // Freeing stack
    freeStack();

    // Closing file
    close(fd);

    return 0;
}
