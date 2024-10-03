#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
	int number = atoi(argv[1]);
	int num = 0;
	printf("Your number was %d\n", number);

	while(number!=0)
	{
		//printf("%d\n", number);
		if((number & 1) == 1)
		{
			num++;
		}
		number = number >> 1;
	}

	printf("In %d, there are %d bits set to 1\n", atoi(argv[1]), num);
	return 0;
}
