#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main()
{
	int sum = 0;
	int num[100];
	char str[3];

	// Calculates the sum fristly to get the name of file
	srand(time(0));
	for(int i = 0; i<100;i++)
	{
		num[i] = rand()%99;
		sum += num[i];
	}

	// Puts numbers into file
	char name1[20] = "numbers.";
	char name2[5];
	char* name3 = ".txt";
	sprintf(name2, "%d", sum);
	strcat(name1, name2);
	strcat(name1, name3);
	int fd = open(name1, O_WRONLY | O_TRUNC | O_CREAT, 0666);
        if (fd < 0)
        {
                perror("r1");
                exit(1);
        }

	for(int i = 0; i<100;i++)
        {
                sprintf(str, "%d", num[i]);
                write(fd,str, strlen(str));
                write(fd,"\n",1);
                //printf("%s\n",str);
        }



	//printf("....%ld\n",sizeof(str));
	printf("sum:%d\n",sum);

}



	
