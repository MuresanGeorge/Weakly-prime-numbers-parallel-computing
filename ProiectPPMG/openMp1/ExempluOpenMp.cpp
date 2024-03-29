// ExempluOpenMp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define NUM_THREADS 8

static long b = 35000000;
//static long b = 4393139;

bool isPrime1(int num) {
	if (num > 2 && num % 2 == 0) {
		return false;
	}
	int top = (int)sqrt(num) + 1;
	for (int i = 3; i < top; i += 2) {
		if (num % i == 0) {

			return false;
		}
	}
	return true;
}
int lengthNum(int n) {
	int c = 0;
	while (n != 0)
	{
		n /= 10;
		++c;
	}
	return c;
}
int replaceDigitFromPosition(int x, int pos, int digit) {
	int copie = 0;

	if (pos == 1) {
		copie += (int)(x / pow(10, pos)) * 10 + digit;
	}
	else if (pos > 1.0 && pos < lengthNum(x)) {
		copie += (int)(x / pow(10.0, pos)) * pow(10.0, pos) + digit * pow(10.0, pos - 1.0) + x % (int)pow(10.0, pos - 1);
	}
	else
	{
		copie += digit * pow(10.0, pos - 1) + x % (int)pow(10.0, pos - 1);
	}
	return copie;

}

int main()
{
	omp_set_num_threads(NUM_THREADS);
	clock_t t;
	
t = clock();
int i, j, k;
int copie, s = 0;

#pragma omp parallel for private (s, copie, k, i, j)
		for (i = 0; i <= b; i ++)
		{
			s = 0;
			if (isPrime1(i)) {
				for (j = 1; j <= lengthNum(i); j++)
					for (k = 0; k < 10; k++) {
						copie = replaceDigitFromPosition(i, j, k);
						if (isPrime1(copie) == false) {
							s += 1;
						}
					}
				if (s == 9 * lengthNum(i)) {
					printf("nr=%d, de la threadul=%d\n", i, omp_get_thread_num());
				}
				s = 0;
			}
		}
t = clock() - t;
double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
printf(" %f seconds to execute \n", time_taken);

}

