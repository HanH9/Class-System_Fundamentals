#include<stdio.h>
int main()
{
	int a,b;
	int* aptr;
	int* bptr;
	
	aptr = &a;
	bptr = &b;
	
	a = 1;
	*bptr = 2;

	printf("a=%d\n",a);
	printf("b=%d\n",b);
	printf("Deference of the aptr:%d\n", *aptr);
	printf("Deference of the bptr:%d\n", *bptr);
	return 0;
}

