#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "customer.h"


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

double avgAgePS(int n, double *lambda, double *mu) {
    int arrivals = 0;
    int customers = 0;
    double time = 0;
    double relative_time = 0;
    double next_arrival = rand_exp(lambda);
    double area = 0;
    double last_update[2]; /* arrival and departure times of latest relevant update */
    double update_area = 0;
    double duration = 0;
    last_update[0] = 0;
    last_update[1] = next_arrival;
    while (arrivals <= n) {
        if (customers == 0) {
            time = next_arrival;
            next_arrival += rand_exp(lambda);
            arrival(time, mu);
            arrivals++;
            customers++;
        }
        relative_time = (next_arrival - time) / customers;
        if (getRemainingTime() > relative_time) {
            time = next_arrival;
            next_arrival += rand_exp(lambda);
            updateTimes(relative_time);
            arrival(time, mu);
            arrivals++;
            customers++;
        } else {
            relative_time = getRemainingTime();
            time += customers * relative_time;
            if (getArrivalTime() > last_update[0]) {
                duration = time - getArrivalTime();
                update_area = (duration * duration) / 2;
                if (last_update[1] > getArrivalTime()) {
                    duration = last_update[1] - getArrivalTime();
                    update_area -= (duration * duration) / 2;
                }
                area += update_area;
            }
            updateTimes(relative_time);
            departure();
            customers--;
        }
        printInfo();    
    }
    return (*lambda * area / n);
}

int main(void)
{
	double arrivalRate = 0.5;
	double serviceRate = 1;
	double load = arrivalRate / serviceRate;
	int arrivals = 10;

	double AoI = avgAgePS(arrivals, &arrivalRate, &serviceRate);
	double modelAoI = (1 + 1/load + (load*load)/(1 - load)) / serviceRate;
	printf("Average age of information: %0.5f s\n", AoI);
	printf("Average age according to formula: %0.5f s\n", modelAoI); 
	return 0;
}
