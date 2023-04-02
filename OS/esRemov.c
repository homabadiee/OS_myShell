#include <stdio.h>

int main()
{
    char *filename = "D://OSproj//text.txt";
    FILE *file = fopen(filename, "r");


    if (file == NULL)
    {
        printf("Error: could not open file");
        return 1;
    }

    char ch;
    
    while ((ch = fgetc(file)) != EOF)
    {
        if(ch != '\n' && ch != '\t' && ch != ' ' )
        {
            printf("%c",ch);
        }
        
    }

    fclose(file);

    return 0;
}
