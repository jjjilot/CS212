#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *in_filename = argv[1];
    FILE *f_in = fopen(in_filename, "r");
    if (f_in == NULL)
    {
        fprintf(stdout, "Couldn't open file \"%s\"\n", in_filename);
        exit(EXIT_FAILURE);
    }

    /* Create buffer of size equal to file size */
    fseek(f_in, 0, SEEK_END);
    int numBytesToRead = ftell(f_in);
    fseek(f_in, 0, SEEK_SET);
    char *buffer = malloc(numBytesToRead*sizeof(char));
    fread(buffer, numBytesToRead, sizeof(char), f_in);
    fclose(f_in);

    /* Create array of length argc - 2 */
    int numWordsToCheck = argc-2;
    int *wordsToCheck = malloc(numWordsToCheck*sizeof(int));
    for (int i=0; i<numWordsToCheck; i++)
        wordsToCheck[i] = 0;

    /* Iterate through chracters in buffer until terminating character */
    int i=0;
    int start_i = 0;
    while (i<numBytesToRead)
    {
        if (buffer[i] == 32 || buffer[i] == 44 || buffer[i] == 46 || buffer[i] == 10)
        {
            buffer[i] = '\0';
            char *word = buffer+start_i;
            /* Compare buffer section to each argv and increment new array */
            int k;
            for (k=0; k<numWordsToCheck; k++)
                if (strcmp(argv[k+2],word)==0)
                    wordsToCheck[k]++;
            start_i = i+1;
        }
        i++;
    }
    free(buffer);

    /* Profit! */
    int j;
    for (j=0; j<numWordsToCheck; j++)
    {
        printf("The word \"%s\" occurs %d times.\n", argv[j+2], wordsToCheck[j]);
    }
    free(wordsToCheck);
}