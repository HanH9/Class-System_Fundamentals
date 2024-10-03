/********************************************************************************
* @File name: project3.c
* @Author: H9
* @Version: 1.3
* @Date: 2022-11.25
* @Description: Program for the project3
********************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

char* getName(char*);
char* getType(char*);
int checkDes(char*);
int checkSource(char*);
char* getNewDes(char*, char*);
int checkExist(char*);
int copy(char*, char*);
int move(char*, char*);


//struct stat buf; // Struct to store informations about file
//char sourcePath[100];// Path of source file
//char* sourceType;// Source file type
//char* newDes;// The final destination

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
			checkDes(argv[argc-2]);		
			for(int i = 1; i<argc-2; i++)
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
                strncpy(name, name+1, strlen(name));
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

