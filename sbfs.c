#include <stdio.h>

int main()
{
    char *filename = "D://OSproj//text.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    char line[1000];

    while (fgets(line,1000,file))
    {
        for (int i = 0; line[i] != '\n'; i++)
        {
            if (line[i] == ' ')
            {
                break;
            }

            printf("%c",line[i]);
            
        }

        printf("\n");
        
    }
    
    fclose(file);

    return 0;
}
