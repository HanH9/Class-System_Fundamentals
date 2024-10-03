/********************************************************************************
* @File name: Project1.c
* @Author: H9
* @Version: 1.1
* @Date: 2022-9-26
* @Description: calculate an arithmetic expression then converts the result to an equivalent radix r expansion
********************************************************************************/
#include<stdio.h>
#include<math.h>

int Calculation(char*);
int JudgmentSpace(char);
void change( int ,int , char* , int*);


int main(){
	char expression[80]={0};// the expresssion
	int CalResult;//The result for one expression per execution
	int radix;//The radix
	int i=0;// The index to help record the converted result
	char output[80]={'0'};//The result about converting the previous result to an equivalent radix r expansion

	
	printf("Enter an expresion:");
	fflush(stdout);
	scanf("%[^\n]", expression);//The expression can include space
	CalResult = Calculation(expression);//Calculate the expression
	printf("Value = %d \n", CalResult);
	fflush(stdout);


	printf("Enter radix:");
	fflush(stdout);
	scanf("%d", &(radix));
	change(CalResult, radix, output,&i);//Converting the previous result to an equivalent radix r expansion
	printf("Answer = %s\n",output);
	fflush(stdout);
	return 0;
}


/********************************************************
* Function name ：JudgmentSpace
* Description : To judge if the inputting char is ' '
* Parameter ：
* @temp    The char to judge
* return    if the char is ' ' or not
**********************************************************/   
int JudgmentSpace(char temp)
{
	if(temp == ' ')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/********************************************************
* Function name ：Calculation
* Description : Calculating the expression by per execution 
* Parameter ：
* @expression    the reference about a char[] to store the result
* return    the result
**********************************************************/
int Calculation(char* expression)
{	
	int result = 0;
	for(int i = 0;expression[i]!='\0';i++)
       	 {

		 //when the char is space
         	 if(JudgmentSpace(expression[i]))
                 {
                 	continue;
                 }
		 //when the char is number
                 else if(expression[i]!= '+' && expression[i]!= '-' && expression[i]!= '*' && expression[i]!= '/')
                 {
                 	result  = expression[i]-'0';
                 }
		 //when the char is operator
               	 else
                 {
                 	if(expression[i] == '+')
                 	{
                      		while(JudgmentSpace(expression[i+1]))
                                {
                                	 i++;
                                }
                                result += expression[i+1]-'0';
                                i += 1;
                        }
                        else if(expression[i] == '-')
                        {
                        	while(JudgmentSpace(expression[i+1]))
                        	{
                                	i++;
                                }
                                result -= expression[i+1]-'0';
                             	i += 1;
                   	}
			else if(expression[i] == '*')
                        {
                        	while(JudgmentSpace(expression[i+1]))
                                {
                                	i++;
                                }
                               	result *= expression[i+1]-'0';
                                i += 1;
                        }
                        else if(expression[i] == '/')
                        {
                        	while(JudgmentSpace(expression[i+1]))
                        	{
                                	i++;
                               	}
                                result /= expression[i+1]-'0';
                                i += 1;
                        }

                   }
	}
	return result;
}


/********************************************************
* Function name ：change
* Description : converts the result to an equivalent radix r expansion
* Parameter ：
* @n    the number to convert
* @r    the radix
* @output    the reference of a char[] to store the result after converting
* @i     help to record the position in output
* return  
**********************************************************/
void change( int n,int r, char* output, int* i)
{	
     //when result less than 0
     if(n < 0)
     {
	output[*i] = '-';
	(*i) += 1;
	change(fabs(n), r, output, i);
     }
     //when result greater than 0
     else  if(n)
     {
         change( n / r, r , output,i);
	 if( n%r <= 9)
	{
		output[*i] = (char)(n%r+'0');
		(*i) += 1;
	}
	 else
	{
	 	output[*i] =(char)( n%r-10+'A');
		(*i) += 1;
	}
     }
 }
