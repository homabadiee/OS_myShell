#include <stdio.h>

int main()
{
    char *filename = "text.txt";
    FILE *file = fopen(filename, "r");;

    if (file == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    char ch;
    int countLine = 1;
    while ((ch = fgetc(file)) != EOF)
    {

        if(ch == '\n')
        {
            countLine++;
        }
    }

    printf("count line is %d",countLine);


    fclose(file);

    return 0;
}
