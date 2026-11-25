/*
 WAP to design a macro function to multiply two numbers */


#include<stdio.h>
int mul(int i,int j)
{
	return i*j;
}
#define MUL(i,j) (i)*(j)
int main()
{
	int a=2,b=2,r,r1;
	//int mul fun
	r=mul(a+2,b+1);
	printf("r=%d\n",r);
	// macro fun
	r1=MUL(a+2,b+1);
	printf("r1=%d\n",r1);
		return 0;
}
