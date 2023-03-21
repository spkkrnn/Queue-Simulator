#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer {
	double arrival_time;
	double service_time;
	struct customer *next;
};

struct customer *head = NULL;

void addCustomer(double arrival_time, double service_time) {
	struct customer *new_customer = (struct customer*) malloc(sizeof(struct customer));
	new_customer->arrival_time = arrival_time;
	new_customer->service_time = service_time;
	//new_customer->
}
