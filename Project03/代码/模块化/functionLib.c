/********************************************************************************
* @File name: functionLib.c
* @Author: H9
* @Version: 1.1
* @Date: 2022-11.25
* @Description: Function library
********************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include "tools.h"


/********************************************************
* Function name ：copy
* Description  : Copy file to destination
* Parameter  ：
* @source  Source file's path
* @des Destination's path
* Return  : 1-success, 0-failure
**********************************************************/
int copy(char* source, char* des)
{
	char flag[4];// When file has been existed in destination, record the permission of overwriting
	int count;// Record that how many informations has been read from source file
	char buf[BUFSIZ];// Store information in buffer
	int sourceType;// Tag of source file's type
	char* name;// Source file's name
	char sourcePath[100];// Path of source file

	// Get source file's name
	strcpy(sourcePath, source);
	name = getName(sourcePath);

	// Check source file's type
	sourceType = checkSource(source);
	if(sourceType  == 0)
	{
		fprintf(stderr, "%s has a wrong file type\n", name);
		return 0;
	}
	else if(sourceType == -1)
	{
		fprintf(stderr, "Can't get %s's type\n", name);
		return 0;
	}

	// Get new destination
	char* newDes = getNewDes(name, des);

	// A file should not be copied to itself
	if(!strcmp(newDes, source))
	{
		fprintf(stderr, "The file %s should not be copied to itself!\n", name);
		exit(1);
	}

	// If a file already exists in the destination folder, permission for overwriting should be asked
	if(checkExist(newDes))
	{
		printf("The file %s  already exists in the destination folder! Do you want to overwrite it?(yes/no)\n", name);
		scanf("%s",flag);
		if(strcmp(flag, "yes"))
		{
			printf("Do not overwrite with %s\n", name);
			return 0;
		}

	}

	// Open source file
	int file = open(source, O_RDONLY);
        if(file == -1)
	{
       		fprintf(stderr, "Can't open %s!\n", name);
        	return 0;
        }

	// Open destination
	int new_file=open(newDes, O_TRUNC|O_CREAT|O_WRONLY, 0777);
        if(new_file==-1)
	{
        	fprintf(stderr, "Can't open destination when copy %s!\n", name);
		close(file);
        	return 0;
        }

	// Read data from source file then write into destination
	while ((count = read(file, buf, BUFSIZ))!= 0)
	{
		if(count == -1)
		{
			fprintf(stderr, "Fail to read data from %s\n", name);
			close(file);
			close(new_file);
			return 0;
		}
		if ((write(new_file, buf, count)) < 0)
		{
			fprintf(stderr, "Fail to write data when copy %s\n", name);
			close(file);
			close(new_file);
			return 0;
		}
	}

	// Close the opening file
	close(file);
	close(new_file);
	// Free memory
	free(newDes);
	return 1;
}

/********************************************************
* Function name ：move
* Description  : Moves file to destination
* Parameter  ：
* @source Source file's path
* @des Destination's path
* Return  : 1-success, 0-failure
**********************************************************/
int move(char* source, char* des)
{
	char* name;// Source file's name
	int sourceType;// Tag of source file's type
	char sourcePath[100];// Path of source file

	// Get source file's name
	strcpy(sourcePath, source);
        name = getName(sourcePath);

	// Check source file's type
        sourceType = checkSource(source);
        if(sourceType  == 0)
        {
                fprintf(stderr, "%s has a wrong file type\n", name);
                return 0;
        }
        else if(sourceType == -1)
        {
                fprintf(stderr, "Can't get %s's type\n", name);
                return 0;
        }


	// Get new destination
	char* newDes = getNewDes(name, des);

	// link source file to new destination
        if(link(source, newDes) == -1)
	{
		fprintf(stderr, "Can't link with %s\n", name);
		perror("link wrong");
		return 0;
	}

	// Unlink the souce file to delete itself
	if(unlink(source) == -1)
	{
		fprintf(stderr, "Can't unlink with %s\n", name);
		perror("unlink wrong");
		return 0;
	}

	// Free memory
	free(newDes);
	return 1;
}
