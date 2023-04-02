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
    char string[2000];
    int countLine = 1;
    while ((fgets(string,2000,file)))
    {
        if(countLine > 10)
        {
            break;
        }

        countLine++;
        printf("%s",string);
    }

    fclose(file);

    return 0;
}
