#include <stdio.h> 
int main(){ 
int x = 10; 
int *ptr; 
ptr = &x; 
printf("%p\n", ptr); 
printf("%p\n", &x); 
printf("%d\n", *ptr); 
printf("%p\n", &ptr); 
*ptr = 20; 
printf("%d\n", x); 
x = 30; 
printf("%d\n", *ptr); 
return 0; 
}
