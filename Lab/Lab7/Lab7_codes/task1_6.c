#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handle_sigint(int sig)
{
	printf("Caught signal: %d\n", sig);
}

int main()
{
	printf("%d/n", getpid());
	int flag = 5;
	signal(SIGINT, handle_sigint);
	while(flag)
	{
		flag--;
		sleep(10);
	}
	return 0;
}
