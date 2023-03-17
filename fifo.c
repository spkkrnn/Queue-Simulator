#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static inline double rand_exp(double *lambda) /* Returns a random number from the exponential distribution */
{
	return (-log((double) rand() / RAND_MAX) / *lambda);
}

double avg_age(int n, double *lambda,  double *mu) /* Returns the average age of information */
{
	double time = 0;
	double area = 0;
	double last = 0;
	double a = 0;
	double b = 0;
	double duration = 0;
	for (int i = 0; i < n; ++i)
	{
		a = time + rand_exp(lambda);
		b = (a < last) ? (last + rand_exp(mu)) : (a + rand_exp(mu));
		last = b;
		duration = b - a;
		area += (((a - time + duration) * (a - time + duration))/2) - ((duration * duration)/2);
		time = a;
	}
	return (*lambda*area/n);
}

int main(void)
{
	srand(time(NULL));
	double arrivalRate = 0.5;
	double serviceRate = 1;
	double load = arrivalRate / serviceRate;
	int arrivals = 1000000;

	double AoI = avg_age(arrivals, &arrivalRate, &serviceRate);
	double modelAoI = (1 + 1/load + (load*load)/(1 - load)) / serviceRate;
	printf("Average age of information: %0.3f s\n", AoI);
	printf("Average age according to formula: %0.3f s\n", modelAoI); 
	return 0;
}
