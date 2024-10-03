/********************************************************************************
* @File name: Driver.c
* @Author: H9
* @Version: 1.3
* @Date: 2022-11.25
* @Description: Driver program for the project3
********************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "functionLib.h"
#include"tools.h"


/********************************************************
* Function name ：main
* Descriptio  : A function that copy or move files to destination
* Parameter  ：
* @argc The numbers of paramater
* @argv A string array to store paramaters
* Return  : The name of file or directory
**********************************************************/
int main(int argc, char* argv[])
{
	// To store path of files that be copied or moved successfully
	char success[argc][100];
	// The number of files that be copied or moved successfully
	int num = 0;

	if(!strcmp(argv[0], "./copy"))
	{
		if(argc < 3)
		{
			printf("Wrong input! Usage: copy source1 [source2 ...] destination\n");
			exit(1);
		}
		else
		{
			// Check destination's file type
			checkDes(argv[argc-1]);		
			for(int i = 1; i<argc-1; i++)
			{
				if(copy(argv[i], argv[argc-1]))
				{
					strcpy(success[num], argv[i]);
					num++;
				}
			}

			// Output the result of copying
			if(num == 0)
			{
				printf("Fail to copy anyone!\n");
			}
			else
			{
				for(int j = 0;j < num;j++)
				{	
					printf("%s ", success[j]);
				}
				printf("succesefuly copied to %s\n", argv[argc-1]);
			}
		}
	}

	else if(!strcmp(argv[0], "./move"))
	{
		if(argc < 3)
                {
                        printf("Wrong input! Usage: move source1 [source2 ...] destination\n");
                        exit(1);
                }
		else
		{
			// Check destination's file type
			checkDes(argv[argc-1]);
			for(int i = 1; i < argc-1; i++)
			{	
				if(move(argv[i], argv[argc-1]))
				{
					strcpy(success[num], argv[i]);
					num++;
				}
			}

			// Output the result of moving
			if(num == 0)
			{
				printf("Fail to move anyone!\n");
			}
			else
			{
				for(int j = 0;j < num;j++)
                        	{
                                	printf("%s ", success[j]);
                        	}
                        	printf("succesefuly moved to %s\n", argv[argc-1]);
			}
		}
	}
	return 1;
}
