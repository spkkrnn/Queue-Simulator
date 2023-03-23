#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h."

struct customer {
	double arrival_time;
	double service_time;
	struct customer *next;
};

struct customer *head = NULL;

struct customer* addCustomer(double arrival_time, double service_time, struct customer *next_customer) {
	struct customer *new_customer = (struct customer*) malloc(sizeof(struct customer));
	new_customer->arrival_time = arrival_time;
	new_customer->service_time = service_time;
	new_customer->next = next_customer;
	return new_customer;
}

void insertCustomer(double arrival_time, double service_time) {
    if (head == NULL) {
        addCustomer(arrival_time, double service_time, head);
        return;
    }
    struct customer *current = head;
    struct customer *prev = head;
    while(service_time > current->service_time) {
        prev = current;
        current = current->next;
        if (current == NULL) break;
    }
    current = addCustomer(arrival_time, service_time, current);
    if (service_time < head->service_time) {
        head = current;
    }
    else {
        prev->next = current;
    }
}
