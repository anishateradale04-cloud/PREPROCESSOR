#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "file_inclusion.h"

int parse_include(char *line, char *filename)
{
    char *p = line;
    char end;
    int i = 0;

    while (isspace((unsigned char)*p))
        p++;

    if (strncmp(p, "#include", 8) != 0)
        return 0;

    p += 8;

    while (isspace((unsigned char)*p))
        p++;

    if (*p == '"')
        end = '"';
    else if (*p == '<')
        end = '>';
    else
        return 0;

    p++;

    while (*p && *p != end && i < 499)
        filename[i++] = *p++;

    if (*p != end || i == 0)
        return 0;

    filename[i] = '\0';
    return 1;
}

FILE *open_header(char *filename, int system_header)
{
    FILE *header;
    char path[1024];

    header = fopen(filename, "r");

    if (header != NULL)
        return header;

    if (system_header)
    {
        snprintf(path, sizeof(path),
                 "/usr/include/%s", filename);
        header = fopen(path, "r");

        if (header != NULL)
            return header;

        snprintf(path, sizeof(path),
                 "/usr/include/x86_64-linux-gnu/%s",
                 filename);
        header = fopen(path, "r");

        if (header != NULL)
            return header;
    }

    return NULL;
}

void include_files(FILE *fp, FILE *out)
{
    char line[1024];
    char filename[500];
    char *p;
    int system_header;
    FILE *header;
    int ch;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        p = line;

        while (isspace((unsigned char)*p))
            p++;

        system_header = 0;

        if (strncmp(p, "#include", 8) == 0)
        {
            char *q = p + 8;

            while (isspace((unsigned char)*q))
                q++;

            if (*q == '<')
                system_header = 1;

            if (parse_include(line, filename))
            {
                header = open_header(filename, system_header);

                if (header != NULL)
                {
                    while ((ch = fgetc(header)) != EOF)
                        fputc(ch, out);

                    fclose(header);
                }
                else
                {
                    fprintf(stderr,
                            "Header file not found: %s\n",
                            filename);

                    fputs(line, out);
                }
            }
            else
            {
                fputs(line, out);
            }
        }
        else
        {
            fputs(line, out);
        }
    }
}
