#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
int main(void){
pid_t pid;
int rv;
switch(pid = fork()) {
case -1:
perror("fork"); /* something went wrong */
exit(1); /* parent exits */
case 0:
printf(" CHILD: This is the child process!\n");
printf(" CHILD: My PID is %d\n", getpid());
printf(" CHILD: My parent's PID is %d\n", getppid());
exit(0);
default:
printf("PARENT: This is the parent process!\n");
printf("PARENT: My PID is %d\n", getpid());
printf("PARENT: My child's PID is %d\n", pid);
}
return 0;
 }
