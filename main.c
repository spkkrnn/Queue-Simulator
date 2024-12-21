#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "customer.h"

double rand_exp(double *lambda) /* Returns a random number from the exponential distribution */
{
	return (-log((double) rand() / RAND_MAX) / *lambda);
}

double get_aoi_fifo(long *n, double *lambda,  double *mu) { /* Returns the average age of information for a FIFO queue */
	double time = 0;
	double area = 0;
	double last = 0;
	double a = 0; /* arrival */
	double b = 0; /* departure */
	double duration = 0;
	for (int i = 0; i < *n; ++i)
	{
		a = time + rand_exp(lambda);
		b = (a < last) ? (last + rand_exp(mu)) : (a + rand_exp(mu));
		last = b;
		duration = b - a;
		area += (((a - time + duration) * (a - time + duration))/2) - ((duration * duration)/2);
		time = a;
	}
	return (*lambda * area / *n);
}

double get_aoi_ps(long *n, double *lambda, double *mu) { /* Returns the average age of information for a PS queue */
    int arrivals = 0;
    int customers = 0;
    double time = 0;
    double relative_time = 0;
    double next_arrival = rand_exp(lambda);
    double area = 0;
    struct customer *first = NULL;
    double last_update[2]; /* arrival and departure times of latest relevant update */
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
            update_times(&first, relative_time);
            arrival(&first, time, rand_exp(mu));
            arrivals++;
            customers++;
        } else {
            relative_time = first->service_time;
            time += customers * relative_time;
            if (first->arrival_time > last_update[0]) {
                area += (0.5*(time - last_update[0])*(time - last_update[0])) - (0.5*(last_update[1] - last_update[0])*(last_update[1] - last_update[0]));
                last_update[0] = first->arrival_time;
                last_update[1] = time;
            }
            departure(&first);
            update_times(&first, relative_time);
            customers--;
        }  
    }
    free_remaining(&first);
    return (*lambda * area / *n);
}

int main(int argc, char* argv[])
{   
    long arrivals = 10000000;
    /* Handle input arguments */
    if (argc < 2) {
        printf("Using default values. To change the number of arrivals, provide number.\n");
    }
    else {
        arrivals = strtol(argv[1], NULL, 10);
        if (arrivals <= 0) {
            printf("Invalid number of customers.\n");
            return 1;
        }
    }

    /* Set up parameters */
    srand(time(NULL));
	double arrival_rate = 0.5;
	double service_rate = 1;
	double load = arrival_rate / service_rate;

    /* Calculate averages */
    double age_fifo = get_aoi_fifo(&arrivals,  &arrival_rate, &service_rate);
	double age_ps = get_aoi_ps(&arrivals,  &arrival_rate, &service_rate);
	double model_age = (1 + 1/load + (load*load)/(1 - load)) / service_rate;

    /* Print values */
    printf("%ld customers arrived at rate %0.1f and were served at service rate %0.1f\n", arrivals, arrival_rate, service_rate);
	printf("Average age according to mathematical model for FIFO queues: %0.3f s\n", model_age);
    printf("Simulated average age of information for a FIFO queue: %0.3f s\n", age_fifo);
    printf("Simulated average age of information for a PS queue: %0.3f s\n", age_ps);
	return 0;
}