/********************************************************************************
* @File name: tools.h
* @Author: H9
* @Version: 1.1
* @Date: 2022-11.25
* @Description: Tools library for function library
********************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

/********************************************************
* Function name ：getName
* Description  : A function that returns the file/directory name when its path is given.
* Parameter  ：
* @path  The path of file or directory
* Return  : The name of file or directory
**********************************************************/
char* getName(char* path)
{
        char* name = strrchr(path, '/');

	// absolute path
        if(name == NULL)
        {
                name = path;
        }
	// relative path
        else
        {
                //char temp[strlen(name)];;
                strncpy(name, name+1, strlen(name));;
                //temp[strlen(name)-1] = '\0';
                //name = temp;
        }
        return name;
}

/********************************************************
* Function name ：getType
* Description  : Gets the type of file
* Parameter  ：
* @path  The path of file or directory
* Return  : File's type
**********************************************************/
char* getType(char* path)
{
	// To store type
	char* type;
	// Struct to store informations about file
	struct stat buf;


	// Get file's information
	int tag = stat(path, &buf);

	// Check type
	if(tag != 0)
	{
		perror("stat error");
		type = "No type";
	}
	else if((buf.st_mode & S_IFMT) == S_IFREG)
	{
		type = "regular file";
	}
	else if((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		type = "directory";
	}
	else
	{
		type = "other file type";
	}

	return type;

 }

/********************************************************
* Function name ：checkDes
* Description  : Checks destination's path
* Parameter  ：
* @path  The path of destination
* Return  : 1-type is directory, 0-other types
**********************************************************/
int checkDes(char* path)
{
	// Get type
	char* type = getType(path);

	// Check type, only directory and device can be destination
	if(!(strcmp(type, "directory")))
	{
		return 1;
	}
	else
	{
		fprintf(stderr, "Wrong destinaton type!\n");
		exit(1);
	}
}

/********************************************************
* Function name ：checkSource
* Description  : Check source's path
* Parameter  ：
* @path  The path of source
* Return  : 1-type is regular file, 0-other types
**********************************************************/
int checkSource(char* path)
{
	// Get type
	char* type = getType(path);

	// Check type
	if(!(strcmp(type, "regular file")))
	{
		return 1;
	}
	else if(!(strcmp(type, "No type")))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/********************************************************
* Function name ：getNewDes
* Description  :Get new destination, connect file name with destination's path
* Parameter  ：
* @name  File name
* @path  Destination's path
* Return  : New destination
**********************************************************/
char* getNewDes(char* name, char* path)
{
	// To store new destination
	char* newDes = (char*)malloc(strlen(name) + (strlen(path)) + 2);

	// Make new destination
	strcat(newDes, path);
	strcat(newDes, "/");
	strcat(newDes, name);
	return newDes;
}

/********************************************************
* Function name ：checkExist
* Description  : Check if the path has been existed
* Parameter  ：
* @path  The path to check
* Return  : 1-not exist, 0-has been existed
**********************************************************/
int checkExist(char* path)
{
	if(!(access(path,0)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
