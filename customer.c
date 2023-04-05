#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "customer.h"


struct customer* createCustomer(double arrival_time, double service_time, struct customer *next_customer) {
	struct customer *new_customer = malloc(sizeof(struct customer));
	new_customer->arrival_time = arrival_time;
	new_customer->service_time = service_time;
	new_customer->next = next_customer;
	return new_customer;
}

void arrival(struct customer **head, double arrival_time, double service_time) {
    struct customer *current = *head;
    struct customer *new_customer = malloc(sizeof(struct customer));
	new_customer->arrival_time = arrival_time;
	new_customer->service_time = service_time;
	//new_customer->next = next_customer;
    if (*head == NULL) {
        //createcustomer(arrival_time, service_time, head);
        new_customer->next = NULL;
        *head = new_customer;
        return;
    }
    if (service_time < current->service_time) {
        new_customer->next = *head;
        *head = new_customer;
        return;
    }
    struct customer *prev = NULL;
    while (current != NULL) {
        if (service_time > current->service_time) break;
        prev = current;
        current = current->next;
    }
    //struct customer *current2 = createcustomer(arrival_time, service_time, current);
    if (current != NULL) {
        new_customer->next = current->next;
        current->next = new_customer;
    }
    else {
        new_customer->next = current;
        if (prev != NULL) {
        prev->next = new_customer;
        }
    }
}

double departure(struct customer **head) {
    if (*head == NULL) return 0;
    struct customer *leaver = *head;
    double arrival_time = leaver->arrival_time;
    //struct customer *departer = head;
    *head = leaver->next;
    free(leaver);
    return arrival_time;
}

void updateTimes(struct customer **head, double time_passed) {
    struct customer *ptr = *head;
    while (ptr != NULL) {
        ptr->service_time -= time_passed;
        ptr = ptr->next;
    }
}

void printInfo(struct customer **head) {
    unsigned int number = 1;
    struct customer *ptr = *head;
    printf("\n");
    while (ptr != NULL) {
        printf("Customer %u: Time arrived %0.3f s, time left %0.3f s.\n", number, ptr->arrival_time, ptr->service_time);
        ptr = ptr->next;
        number ++;
    }
}