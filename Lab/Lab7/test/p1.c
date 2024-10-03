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
	if(signum == SIGUSR1)
	{
		// print pid of the process and the signal information
		printf("\nP1: Handling SIGUSR1 in p1!\n");
		printf("Pid: %d\n", getpid());
		printf("Signal information: %d\n", signum);
	}
}

int main()
{
	pid_t cpid;
	int status = 0;
	char characters[6];
	int fd, num;

	// p1 writes to a FIFO. Five characters can be written to the FIFO by p1
        printf("P1: Please put five charcaters\n");
        //fgets(characters, 6, stdin);
        mkfifo("my_fifo", 0777);
        fd = open("my_fifo", O_WRONLY|O_TRUNC|O_CREAT);
	while(fgets(characters, sizeof(characters), stdin), !feof(stdin))
	{
        	if((num = write(fd, characters, strlen(characters))) == -1)
        	{
        		perror("write");
        	}	
	}
	close(fd);

	if((cpid = fork()) == -1)
	{
		exit(1);
	}
	if(cpid == 0)
	{
		// child process execute p2
		execl("p2", "./p2", NULL);
	}
	else
	{
		if(signal(SIGUSR1, signal_handler) == SIG_ERR)
		{
			fprintf(stderr, "Can't handle SIGUSR1!\n");
			exit(1);
		}

		// p1 writes to a FIFO. Five characters can be written to the FIFO by p1
		//printf("P1: Please put five charcaters\n");
		//fgets(characters, 6, stdin);
		//mkfifo("my_fifo", 0777);
                //fd = open("my_fifo", O_WRONLY|O_TRUNC|O_CREAT);
		//if((num = write(fd, characters, strlen(characters))) == -1)
		//{
		//	perror("write");
		//}
		//close(fd);

		// send signal to p2
		kill(cpid, SIGUSR2);
		// wait for p2
		cpid = wait(&status);
	}

	return 0;
}
