#include <stdio.h>

int main()
{
    char *filename = "text.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    char ch;
    int comment = 0; //boolean comment
    while ((ch = fgetc(file)) != EOF)
    {
        if(ch == '#')
        {
            comment = 1;
        }
        
        if(!comment)
        {
            printf("%c",ch);

        }

        if(ch == '\n')
        {
            comment = 0;
        }

    }


    fclose(file);

    return 0;
}
