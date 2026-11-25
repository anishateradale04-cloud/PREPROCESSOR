#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "macro_handler.h"

void macro_substitution(FILE *fp,FILE *out)
{
    char macro_name[100][100];
    char macro_value[100][200];
    char line[500];
    char word[100];

    int count=0;
    int i,j,k,found;

    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        if(strncmp(line,"#define",7)==0)
        {
            if(count < 100 &&
               sscanf(line,"#define %99s%199[^\n]",
                      macro_name[count],
                      macro_value[count])==2)
            {
                count++;
            }
        }
        else
        {
            i=0;

            while(line[i]!='\0')
            {
                if(isalpha((unsigned char)line[i]) ||
                   line[i]=='_')
                {
                    j=0;

                    while(isalnum((unsigned char)line[i]) ||
                          line[i]=='_')
                    {
                        if(j<99)
                            word[j++]=line[i];

                        i++;
                    }

                    word[j]='\0';
                    found=0;

                    for(k=0;k<count;k++)
                    {
                        if(strcmp(word,macro_name[k])==0)
                        {
                            fputs(macro_value[k],out);
                            found=1;
                            break;
                        }
                    }

                    if(found==0)
                        fputs(word,out);
                }
                else
                {
                    fputc(line[i],out);
                    i++;
                }
            }
        }
    }
}
