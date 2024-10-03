/********************************************************************************
* @File name: project4.c
* @Author: H9
* @Version: 1.3
* @Date: 2022-12-05
* @Description: Program for the project4
********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>

int number;// The number of input digits
int ave;// The average of numbers
int max;// The maximum of numbers
int min;// The minimum of numbers
int sum;// The sum of numbers
double mid;// The median of numbers
double sigma;// The Standard deviation of numbers

/********************************************************
* Function name ：getSum
* Description  : Get the sum of numbers
* Parameter  ：
* @arg The arrary that store numbers
**********************************************************/
void* getSum(void* arg)
{
	sum = 0;
	int* numbers = (int*)arg;

        for(int i = 0; i < number;i++)
        {
                sum += numbers[i];
        }

	return 0;
}

/********************************************************
* Function name ：average
* Description  : Get the average of numbers
* Parameter  ：
* @arg The arrary that store numbers
**********************************************************/
void* average(void* arg)
{
	int* numbers = (int*)arg;

	getSum(numbers);
	ave = sum/number;
	return 0;
}

/********************************************************
* Function name ：minimum
* Description  : Get the minimum of numbers
* Parameter  ：
* @arg The arrary that store numbers
**********************************************************/
void* minimum(void* arg)
{
        int* numbers = (int*)arg;
        min = numbers[0];
        for(int i = 1; i < number; i++)
        {
                if(numbers[i] < min)
                        min = numbers[i];
        }
        return 0;
}

/********************************************************
* Function name ：maximum
* Description  : Get the maximum of numbers
* Parameter  ：
* @arg The arrary that store numbers
**********************************************************/
void* maximum(void* arg)
{
	int* numbers = (int*)arg;

	for(int i = 0; i < number; i++)
	{
		if(numbers[i] > max)
			max = numbers[i];
	}
	return 0;
}

/********************************************************
* Function name ：median
* Description  : Get the median of numbers
* Parameter  ：
* @arg The arrary that store numbers
**********************************************************/
void* median(void* arg)
{
	int b = 0;
	int temp = 0;
        int* numbers = (int*)arg;

        for(int i = 0; i < number; i++)
        {
                if(numbers[i] > max)
                        max = numbers[i];
        }

	// Sort the numbers
	for(int i = 0; i < number - 1; i++)
	{
		for(int j = 0;j < number - 1 - i; j++)
		{
			if(numbers[j] > numbers[j + 1])
			{
				temp = numbers[j + 1];
				numbers[j + 1] = numbers[j];
				numbers[j] = temp;
			}
		}
	}

	// Get the median
	if(number % 2 == 0)
	{
		b = number / 2;
		mid = (numbers[b]+numbers[b - 1]) / 2.0;
	}
	else
	{
		mid = numbers[(number - 1) / 2];
	}
        return 0;
}

/********************************************************
* Function name ：getSigma
* Description  : Get the standard devision of numbers
* Parameter  ：
* @arg The arrary that store numbers
**********************************************************/
void* getSigma(void* arg)
{
        int* numbers = (int*)arg;
        double spow = 0; // sum of power

	// calculate standard deviation
	average(numbers);// get average fristly
        for(int i = 0; i < number; i++)
        {
        	spow += (numbers[i] - ave) * (numbers[i] - ave);
        }
	sigma = sqrt(spow / number); 
        return 0;
}

/********************************************************
* Function name ：main
* Description  : The driver of program
* Parameter  ：
* @argc The numbers of paramaters
* @argv The array that store paramaters
**********************************************************/
int main(int argc, char*argv[])
{
	int* numbers = (int*)malloc((argc - 1) * sizeof(int));
	pthread_t t1_id;
	pthread_t t2_id;
	pthread_t t3_id;
	pthread_t t4_id;
	pthread_t t5_id;
	int s; // flag of creating pthread
	void* res;

	// put numbers into a int array
	for(int i = 0; i < argc - 1; i++)
	{
		numbers[i] = atoi(argv[i + 1]);
	}

	// get the number of digit
	number = argc - 1;

	// make a thread to get average
	s = pthread_create(&t1_id, NULL, average, numbers);
	if(s != 0)
		perror("Ave pthread_create error");
	s = pthread_join(t1_id, &res);
	printf("The average value is %d\n", ave);

	// make a thread to get maximum
	s = pthread_create(&t2_id, NULL, maximum, numbers);
        if(s != 0)
                perror("Max pthread_create error");
        s = pthread_join(t2_id, &res);
	printf("The maximum value is %d\n", max);

	// make a thread to get minimum
	s = pthread_create(&t3_id, NULL, minimum, numbers);
        if(s != 0)
                perror("Min pthread_create error");
        s = pthread_join(t3_id, &res);
	printf("The minimum value is %d\n", min);

	// make a thread to get median
	s = pthread_create(&t4_id, NULL, median, numbers);
        if(s != 0)
                perror("Mid pthread_create error");
        s = pthread_join(t4_id, &res);
        printf("The median value is %f\n", mid);

	// make a thread to get standard deviation
	s = pthread_create(&t5_id, NULL, getSigma, numbers);
        if(s != 0)
                perror("getSigma pthread_create error");
        s = pthread_join(t5_id, &res);
        printf("The standard deviation value is %f\n", sigma);

	free(numbers);

	return 0;
}
