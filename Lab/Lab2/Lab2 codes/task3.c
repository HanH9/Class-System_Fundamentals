#include<stdio.h>

int my_strlen(char*);
void UpperLowerLen(char*);
void ConcatStr(char*, char*);

int uppercase,lowercase;

int main()
{
	int length;
	char str1[100];
	char str2[100];
	char str3[100];
	char str4[100];
	printf("\nEnter the string to calculate uppercases and lowercases :");
	scanf("%s",str1);
	
	UpperLowerLen(str1);
        printf("The number of uppercase and lowercase are %d and %d\n",uppercase,lowercase);

	printf("\nEnter two strings to concat :");
        scanf("%s%s", str2, str3);
        ConcatStr(str2, str3);
        printf("After concating:%s\n",str2);

	printf("\nEnter string to calculate length :");
        scanf("%s", str4);
	length = my_strlen(str4);
	printf("The length of string is: %d\n", length);


	return 0;
}

int my_strlen(char* str)
{
    int count = 0;
    while(*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

void UpperLowerLen(char* str)
{
	int length = my_strlen(str);
	for(int i = 0; i < length ;i++)
	{
		if(str[i]>='A' && str[i]<='Z')
		{
			uppercase++;
		}
		else if(str[i] >= 'a' && str[i] <= 'z')
		{
			lowercase++;
		}
	}
}

void ConcatStr(char* str1, char* str2)
{
	int j = my_strlen(str1);
	for(int i = 0;i <my_strlen(str2);i++)
	{
		str1[j] = str2[i];
		j++;
	}
}
