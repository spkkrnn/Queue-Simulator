#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
	double arrival_time;
	double service_time;
	struct customer *next;
};

struct customer* create_customer(double arrival_time, double service_time, struct customer *next_customer);

double rand_exp(double *lambda);

void arrival(struct customer **head, double arrival_time, double service_time);

double departure(struct customer **head);

void update_times(struct customer **head, double time_passed);

void print_info(struct customer **head);

void free_remaining(struct customer **head);

#endif