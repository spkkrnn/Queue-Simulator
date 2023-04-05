#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "customer.h"

double rand_exp(double *lambda) /* Returns a random number from the exponential distribution */
{
	return (-log((double) rand() / RAND_MAX) / *lambda);
}

double avgAgeFIFO(int n, double *lambda,  double *mu) { /* Returns the average age of information */
	double time = 0;
	double area = 0;
	double last = 0;
	double a = 0; /* arrival */
	double b = 0; /* departure */
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

double avgAgePS(int *n, double *lambda, double *mu) {
    int arrivals = 0;
    int customers = 0;
    double time = 0;
    double relative_time = 0;
    double next_arrival = rand_exp(lambda);
    double area = 0;
    struct customer *first = NULL;
    double last_update[2]; /* arrival and departure times of latest relevant update */
    double update_area = 0;
    double duration = 0;
    last_update[0] = 0;
    last_update[1] = next_arrival;
    while (arrivals <= *n) {
        if (customers == 0) {
            time = next_arrival;
            next_arrival += rand_exp(lambda);
            arrival(&first, time, rand_exp(mu));
            arrivals++;
            customers++;
        }
        relative_time = (next_arrival - time) / customers;
        if (first != NULL && first->service_time > relative_time) {
            time = next_arrival;
            next_arrival += rand_exp(lambda);
            updateTimes(&first, relative_time);
            arrival(&first, time, rand_exp(mu));
            arrivals++;
            customers++;
        } else {
            relative_time = first->service_time;
            time += customers * relative_time;
            if (first->arrival_time > last_update[0]) {
                duration = time - first->arrival_time;
                update_area = (duration * duration) / 2;
                if (last_update[1] > first->arrival_time) {
                    duration = last_update[1] - first->arrival_time;
                    update_area -= (duration * duration) / 2;
                }
                area += update_area;
            }
            updateTimes(&first, relative_time);
            departure(&first);
            customers--;
        }  
    }
    return (*lambda * area / *n);
}

int main(void)
{
    srand(time(NULL));
	double arrivalRate = 0.5;
	double serviceRate = 1;
	double load = arrivalRate / serviceRate;
	int arrivals = 10000;

	double AoI = avgAgePS(&arrivals, &arrivalRate, &serviceRate);
	double modelAoI = (1 + 1/load + (load*load)/(1 - load)) / serviceRate;
	printf("Average age of information: %0.5f s\n", AoI);
	printf("Average age according to formula: %0.5f s\n", modelAoI); 
	return 0;
}