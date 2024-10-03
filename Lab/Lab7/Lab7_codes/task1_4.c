#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(void) {
pid_t child;
int cstatus; /* Exit status of child. */
pid_t c; /* Pid of child to be returned by wait. */
if ((child = fork()) == 0) {
/* Child process. To begin with, it prints its pid. */
printf("Child: PID of Child = %ld\n", (long) getpid());
/* Wait for an input*/
printf("Press Enter to continue\n");
getchar();
/* Child will now execute the nano command. */
execlp("nano", "nano", "man2fork.txt", NULL);
fprintf(stderr, "Child process could not do execlp.\n");
exit(1);
}else { /* Parent process. */
if (child == (pid_t)(-1)) {
fprintf(stderr, "Fork failed.\n"); exit(1);
}else {
c = wait(&cstatus); /* Wait for child to complete. */
printf("Parent: Child %d exited with status = %d\n", c,
WEXITSTATUS(cstatus));
}
}
return 0;
}
