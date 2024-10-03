#include <stdio.h> 
int main(){ 
FILE *fp = fopen("record.txt", "r"); 
int ch = getc(fp); //return value of getc is integer 
while (ch != EOF){ //or use feof(fp) function 
putchar(ch); //display the char 
ch = getc(fp); 
} 
}

