#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
 int sz;
 int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
 if (fd < 0){
 perror("r1");
 exit(1);
 }
 sz = write(fd, "hello world\n", strlen("hello world\n"));
 printf("called write(%d, \"hello world\\n\", %zu)returned and %d\n ", 
 fd, strlen("hello world\n"), sz);
 close(fd);
}
