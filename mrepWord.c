#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{   
    char *filename = "D:/OSproj/text.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    int count = 0, c = 0, i, j = 0, maxCount = -1;
 
    char line[1000], words[1000][1000];
    int freq[1000];
 
    while (fgets(line,1000,file))
    { 
        for(int k=0; k < strlen(line); k++) 
        {   
            
            if(line[k] != ' ' && line[k] != '\n'  ) // && line[k] != ',' && line[k] != '.'
            {  
                words[i][j] = line[k];  
                j++;
            }  
            else
            {  
                freq[i]++;
                words[i][j] = '\0';      
                j = 0;  
                for (int ii = 0; ii < i; ii++)
                {
                    if(strcmp(words[i], words[ii]) == 0)
                    {
                        freq[i]++;
                        freq[ii]++;
                    }
                }
                i++;
                
            }  
        }  
    }

    int maxIndex;
    for (j = 0; j < i; j++)
    {
        if (freq[j] > maxCount)
        {
            maxCount = freq[j];
            maxIndex = j;
        }
        
    }
      
    printf("Most repeated word: %s", words[maxIndex]);  

    fclose(file);
    
    return 0;
}
