#include<stdio.h> 
#include<string.h> 
int main(){ 
	char str[100], temp; 
	int i = 0; 
	printf("\nEnter the string :"); 
	gets(str);
	char* point1 = str;
	char* point2 = &(str[strlen(str)-1]);   
	while (point1 < point2)
	{ 
		temp = *point1;
		*point1 = *point2; 
		*point2 = temp; 
		point1++; 
		point2--;
		i++;	
	}	 
	printf("\nReverse string is :%s\n", str); 
	return (0); 
}
