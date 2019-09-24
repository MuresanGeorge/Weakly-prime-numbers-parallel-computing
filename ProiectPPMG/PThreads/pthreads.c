#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define NUM_THREADS 5

static int  a = 0;
static long b = 35000000;
pthread_t tid[NUM_THREADS];

struct timespec start, stop;
time_t tv_sec;
double sqrt(double x);
double pow(double x, double y);

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

void *thr_func( void *arg )
{
	
	int threadNo = (intptr_t) arg;
	int i, j, k;
	int s, copie;
	
	for (i = 0 + threadNo; i <= b; i += NUM_THREADS )
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
					printf("nr=%d ---from thread=%d\n", i, threadNo);
				}
				s = 0;
			}
		}
	

	return NULL;
}


int main(void)
{
	clock_gettime(CLOCK_REALTIME, &start);    

  for (int i = 1; i <= NUM_THREADS; i++)
  {
    if (pthread_create(&tid[i], NULL, &thr_func, (void *)(intptr_t)i) != 0)
    {
      printf("Thread %d cannot be created!\n", i);
      return 1;
		}
	
  }

for (int i = 0; i < NUM_THREADS; i++){
	pthread_join(tid[i], NULL);
}


  clock_gettime(CLOCK_REALTIME, &stop);   

  long seconds = stop.tv_sec - start.tv_sec;

  long ns = stop.tv_nsec - start.tv_nsec;
  if (start.tv_nsec > stop.tv_nsec)
  {
    ns += 1000000000;
  }
  
  printf("Total execution time (seconds): %.4f\n", (double)seconds + (double)ns/(double)1000000000);

  return 0;
}
