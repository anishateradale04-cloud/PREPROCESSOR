#include <stdio.h>
#include <string.h>
#include "comment_removal.h"
#include "file_inclusion.h"
#include "macro_handler.h"

int main(int argc, char *argv[])
{
    FILE *in, *temp, *temp2, *out;
    char output[256];
    char *dot;

    if(argc != 2)
    {
        printf("Usage: ./mypreprocessor filename.c\n");
        return 1;
    }

    strcpy(output, argv[1]);

    dot = strrchr(output, '.');

    if(dot != NULL)
        strcpy(dot, ".i");
    else
        strcat(output, ".i");

    in = fopen(argv[1], "r");
    if(in == NULL)
    {
        printf("Input file opening failed\n");
        return 1;
    }

    temp = fopen("temp1.c", "w");
    remove_comments(in, temp);
    fclose(in);
    fclose(temp);

    temp = fopen("temp1.c", "r");
    temp2 = fopen("temp2.c", "w");
    include_files(temp, temp2);
    fclose(temp);
    fclose(temp2);

    temp2 = fopen("temp2.c", "r");
    out = fopen(output, "w");

    macro_substitution(temp2, out);

    fclose(temp2);
    fclose(out);

    remove("temp1.c");
    remove("temp2.c");

    printf("Preprocessing completed successfully!\n");






    printf("Output file generated: %s\n", output);

    return 0;
}
