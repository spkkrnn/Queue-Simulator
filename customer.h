#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
	double arrival_time;
	double service_time;
	struct customer *next;
};

struct customer* createCustomer(double arrival_time, double service_time, struct customer *next_customer);

double rand_exp(double *lambda);

void arrival(double arrival_time, double *mu);

double departure(void);

void updateTimes(double time_passed);

int customers(void);

double getArrivalTime(void);

double getRemainingTime(void);

#endif
