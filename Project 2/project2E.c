#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
    fprintf(stdout, "Usage: %s <in-filename> <out-filename>\n", argv[0]);
    exit(EXIT_FAILURE);
    }
    char *in_filename = argv[1];
    char *out_filename = argv[2];
    FILE *f_in = fopen(in_filename, "r");
    
    if (f_in == NULL)
    {
        fprintf(stdout, "Couldn't open file \"%s\"\n", in_filename);
        exit(EXIT_FAILURE);
    }
    
    int i;
    int *outp = malloc(25*sizeof(int));
    for (i=0; i<5; i++)
    {
       fseek(f_in, (10*i*sizeof(int)), SEEK_SET);
       fread(&outp[5*i], 5, sizeof(int), f_in);
    }
    fclose(f_in);

    FILE *f_out = fopen(out_filename, "w");
    if (f_out == NULL)
    {
        fprintf(stdout, "Couldn't open file \"%s\"\n", out_filename);
        exit(EXIT_FAILURE);
    }
    
    int k;
    for (k=0; k<25; k++)
    {
        fprintf(f_out, "%d\n", outp[k]);
    }
    fclose(f_out);
    free(outp);

    return 0;
}