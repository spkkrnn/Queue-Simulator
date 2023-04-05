#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
	double arrival_time;
	double service_time;
	struct customer *next;
};

struct customer* createCustomer(double arrival_time, double service_time, struct customer *next_customer);

double rand_exp(double *lambda);

void arrival(struct customer **head, double arrival_time, double service_time);

double departure(struct customer **head);

void updateTimes(struct customer **head, double time_passed);

void printInfo(struct customer **head);

#endif