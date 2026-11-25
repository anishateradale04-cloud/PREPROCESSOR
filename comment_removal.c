#include<stdio.h>
#include "comment_removal.h"
void remove_comments(FILE *fp,FILE *out)
{
	int ch,next;
	int state=0;
	while((ch=fgetc(fp))!=EOF)
	{
		if(state==0)
		{
			if(ch=='/')
			{
				next=fgetc(fp);
				if(next=='/')
					state=1;
				else if(next=='*')
					state=2;
				else
				{
					fputc(ch,out);
					if(next!=EOF)
						ungetc(next,fp);
				}
			}
			else
				fputc(ch,out);
		}
		else if(state==1)
		{
			if(ch=='\n')
			{
				fputc(ch,out);
					state=0;
			}
		}
		else if(state==2)
		{
			if(ch=='*')
			{
				next=fgetc(fp);
				if(next=='/')
					state=0;
				else if(next!=EOF)
					ungetc(next,fp);
			}
		}
	}
}
