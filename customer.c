#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "customer.h."


srand(time(NULL));
struct customer *head = NULL;

double rand_exp(double *lambda) /* Returns a random number from the exponential distribution */
{
	return (-log((double) rand() / RAND_MAX) / *lambda);
}

struct customer* createCustomer(double arrival_time, double service_time, struct customer *next_customer) {
	struct customer *new_customer = (struct customer*) malloc(sizeof(struct customer));
	new_customer->arrival_time = arrival_time;
	new_customer->service_time = service_time;
	new_customer->next = next_customer;
	return new_customer;
}

void arrival(double arrival_time, double *mu) {
    double service_time = rand_exp(mu);
    if (head == NULL) {
        createCustomer(arrival_time, double service_time, head);
        return;
    }
    struct customer *current = head;
    struct customer *prev = head;
    while (service_time > current->service_time) {
        prev = current;
        current = current->next;
        if (current == NULL) break;
    }
    current = createCustomer(arrival_time, service_time, current);
    if (service_time < head->service_time) {
        head = current;
    }
    else {
        prev->next = current;
    }
}

double departure(void) {
    double arrival_time = head->arrival_time;
    struct customer *departer = head;
    head = head->next;
    free(departer);
    return arrival_time;
}

void updateTimes(double time_passed) {
    struct node *ptr = head;
    while (ptr != NULL) {
        ptr->service_time -= time_passed;
        ptr = ptr->next;
    }
}

int customers(void) {
    int n = 0;
    for (struct node *current = head; current !=NULL; current = current->next) {
        n++;
    }
    return n;
}

double getArrivalTime(void) {
    return head->arrival_time;
}

double getRemainingTime(void) {
    return head->service_time;
}
