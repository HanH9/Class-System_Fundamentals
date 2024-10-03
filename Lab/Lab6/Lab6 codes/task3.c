#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
	DIR *dp = NULL;
    	struct dirent *dptr = NULL;
	char name[100];// Name of file
	//char temp[4];
	int sum = 0;
	int num = 0;

	// Gets directory
	if (NULL == (dp = opendir("/home/h9/ICSI333/Lab/Lab5"))) 
	{
        	fprintf(stderr, "Can not open Input Directory\n");
        	exit(-1);
    	} 
	else 
	{
        	printf("Directory Content List!\n");
        	while (NULL != (dptr = readdir(dp))) 
		{
			// Gets the name of file
            		if(strstr(dptr->d_name,"numbers.") != NULL)
			{
				strcpy(name, dptr->d_name);
				printf("Get the file:%s\n",name);

				int fd = open(name, O_RDONLY);

                        	if (fd < 0)
                        	{
                                	perror("r1");
                                	exit(1);
                        	}
                        	else
                        	{
					// Calculates the sum
                                	FILE *fp = fopen(name, "r");
                                	while (fscanf(fp, "%d", &num) != EOF)
                                	{
                                        	//printf("%d\n",num);
                                        	sum += num;
                                	}

					// Try to call write
					//while(read(fd,temp,sizeof(char)*3))
					//{
						//printf("%s\n",temp);
						//sum += atoi(temp);
					//}	
                        	}
				continue;
        		}
		}

		if(name == NULL)
		{
			printf("Can't get the file\n");
		}


        closedir(dp);
	printf("sum:%d\n",sum);
    	}
}	
