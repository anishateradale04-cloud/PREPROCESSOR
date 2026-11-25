#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "macro_handler.h"

char name[50][50], value[50][100];
char p1[50][20], p2[50][20];
int type[50], count = 0;

void macro_substitution(FILE *fp, FILE *out)
{
    char line[500], arg1[100], arg2[100];
    char result[500], *p;
    int i, j, k, a, b;

    while(fgets(line, sizeof(line), fp))
    {
        if(strncmp(line, "#define", 7) == 0)
        {
            if(sscanf(line, "#define %49[^ (](%19[^,],%19[^)]) %99[^\n]",
                name[count], p1[count], p2[count], value[count]) == 4)
                type[count] = 1;
            else
            {
                sscanf(line, "#define %49s %99[^\n]",
                    name[count], value[count]);
                type[count] = 0;
            }

            count++;
            continue;
        }

        i = 0;

        while(line[i] != '\0')
        {
            for(k = 0; k < count; k++)
            {
                j = strlen(name[k]);

                if(strncmp(line+i, name[k], j) == 0)
                    break;
            }

            if(k == count)
            {
                fputc(line[i++], out);
                continue;
            }

            if(type[k] == 0)
            {
                fputs(value[k], out);
                i += j;
            }
            else
            {
                i += j;

                while(isspace((unsigned char)line[i]))
                    i++;

                if(line[i] != '(')
                {
                    fputs(name[k], out);
                    continue;
                }

                a = ++i;

                while(line[i] != ',' && line[i] != '\0')
                    i++;

                b = i;
                snprintf(arg1, sizeof(arg1), "%.*s", b-a, line+a);

                a = ++i;

                while(line[i] != ')' && line[i] != '\0')
                    i++;

                snprintf(arg2, sizeof(arg2), "%.*s", i-a, line+a);

                if(line[i]) i++;

                strcpy(result, value[k]);

                p = strstr(result, p1[k]);
                if(p)
                {
                    memmove(p+strlen(arg1), p+strlen(p1[k]),
                            strlen(p+strlen(p1[k]))+1);
                    memcpy(p, arg1, strlen(arg1));
                }

                p = strstr(result, p2[k]);
                if(p)
                {
                    memmove(p+strlen(arg2), p+strlen(p2[k]),
                            strlen(p+strlen(p2[k]))+1);
                    memcpy(p, arg2, strlen(arg2));
                }

                fputs(result, out);
            }
        }
    }
}
