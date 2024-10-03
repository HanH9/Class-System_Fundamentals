#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

static void signal_handler(int signum)
{
	if(signum == SIGUSR2)
	{
		// print pid of the process and the signal information
		printf("\nP2: Handling SIGUSR2 in p2!\n");
		printf("Pid: %d\n", getpid());
                printf("Signal information: %d\n", signum);

	}
}

void check(char c)
{
	// If a byte to be read is a digit, prints ‘N’
	if(c >= '0' && c<= '9')
	{
		printf("N");
	}
	// if a byte to be read is a letter, prints ‘L‘
	else if((c >='a' && c <='z')||(c >= 'A' && c <='Z'))
	{
		printf("L");
	}
	//  for otherwise, prints ‘O‘
	else
	{
		printf("O");
	}
}

int main()
{
	int fd,num;
	char characters[6];

	if(signal(SIGUSR2, signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "Can't handle SIGUSR2!\n");
		exit(-1);
	}

	// wait for p1 to write
	sleep(2);

	// p2 reads from the same FIFO
	fd = open("my_fifo", O_RDONLY);
	//if((num = read(fd, characters, 5)) == -1)
	//{
	//	perror("read");
	//}
	//characters[num] = '\0';
	//close(fd);

	// transfer characters
	//printf("\nP2:Tansfer characters\n");
	//for(int i = 0; i<strlen(characters); i++)
	//{
	//	check(characters[i]);
	//}
	//printf("\n");
	
	printf("\nP2:Tansfer characters\n");
	do 
	{
		if ((num = read(fd, characters, 5)) == -1)
		perror("read");
		else 
		{
			characters[num] = '\0';
			for(int i = 0; i<strlen(characters); i++)
        		{
        		      check(characters[i]);
        		}
		}
	} 
	while (num > 0);
	printf("\n");
	close(fd);

	// send signal to p1
	kill(getppid(), SIGUSR1);

	// exit p2
	return 0;
}
