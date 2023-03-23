#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
	double arrival_time;
	double service_time;
	struct customer *next;
};

struct customer* addCustomer(double arrival_time, double service_time, struct customer *next_customer);

void insertCustomer(double arrival_time, double service_time);

#endif
