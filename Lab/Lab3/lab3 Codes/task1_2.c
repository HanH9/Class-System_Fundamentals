#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
int main(int argc, char *argv[]){ 
char name[50]; 
int age; 
float salary; 
 FILE *fptr;
if(argc==4){ 
strcpy(name, argv[1]); //array is not assignable 
age = atoi(argv[2]); 
salary = atof(argv[3]); 
} else { 
perror("\n"); 
exit(-1); 
} 
fptr = fopen("record.txt", "a"); 
if (fptr == NULL){ 
exit(-1); 
} 
fprintf(fptr, "Name = %s\n", name); 
fprintf(fptr, "Age = %d\n", age); 
fprintf(fptr, "Salary = %.2f\n", salary);
fclose(fptr); 
}
