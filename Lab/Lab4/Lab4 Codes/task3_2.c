#include<stdio.h>
void binary(unsigned int);
void main(){
unsigned int num;
printf("Enter Decimal Number : ");
scanf("%u",&num);
binary(num); // Function Call
getchar();
}
void binary(unsigned int num){
unsigned int mask=32768; //mask = 1000 0000 0000 0000
printf("Binary Eqivalent : ");
while(mask > 0){
if((num & mask) == 0 )
printf("0");
else
printf("1");
mask = mask >> 1; //Right Shift
 }
}
