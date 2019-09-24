#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

bool isPrime11(int num) {
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

int lengthNum1(int n) {
	int c = 0;
	while (n != 0)
	{
		n /= 10;
		++c;
	}
	return c;
}
int replaceDigitFromPosition1(int x, int pos, int digit) {
	int copie = 0;

	if (pos == 1) {
		copie += (int)(x / pow(10, pos)) * 10 + digit;
	}
	else if (pos > 1.0 && pos < lengthNum1(x)) {
		copie += (int)(x / pow(10.0, pos)) * pow(10.0, pos) + digit * pow(10.0, pos - 1.0) + x % (int)pow(10.0, pos - 1);
	}
	else
	{
		copie += digit * pow(10.0, pos - 1) + x % (int)pow(10.0, pos - 1);
	}
	return copie;

}

void main1()
{
	int s = 0;
	int a = 1;
	int b = 4393139;
	int copie;
	int i, j, k;

	for (i = a; i<b; i++)
	{
		if (isPrime11(i)) {
			for (j = 1; j <= lengthNum1(i); j++)
				for (k = 0; k < 10; k++) {
					copie = replaceDigitFromPosition1(i, j, k);
					if (isPrime11(copie) == false) {
						s += 1;
					}
				}
			if (s == 9 * lengthNum1(i)) {
				printf("%d\n", i);
			}
			s = 0;
		}
	}


}