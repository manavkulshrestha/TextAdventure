#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"

#define BUFFER_LENGTH 100

int *random_number(int min_num, int max_num) {
    int *result = (int *) malloc(sizeof(int));
    int *low_num = (int *) malloc(sizeof(int));
    int *hi_num = (int *) malloc(sizeof(int));

    *result = 0;
    *low_num = 0;
    *hi_num = 0;

    if (min_num < max_num) {
        *low_num = min_num;
        *hi_num = max_num + 1;
    } else {
        *low_num = max_num + 1; 
        *hi_num = min_num;
    }

    *result = (rand() % (*hi_num - *low_num)) + *low_num;

    free(low_num);
    low_num = NULL;

    free(hi_num);
    hi_num = NULL;
    
    return result;
}

int main(void) {
    srand(time(NULL));
    int rooms_to_create = 19;
    int *valid_exits = (int *) malloc(sizeof(int));
    *valid_exits = 5;

//SETUPEND

    int *parts = (int *) malloc((*valid_exits) * (sizeof(int)));
    int *partial_sum = (int *) malloc(sizeof(int));
    int *rand_upper_incbound = (int *) malloc(sizeof(int));
    *rand_upper_incbound = rooms_to_create/((*valid_exits)-1);

    for(int i=0; i<(*valid_exits)-1; i++) {
        int* part = random_number(0, *rand_upper_incbound);
        (*partial_sum) += (*part);

        parts[i] = *part;

        free(part);
        part = NULL;
    }

    parts[(*valid_exits)-1] = rooms_to_create - *partial_sum;

//TEST
    int sum = 0;
    for(int i=0; i<*valid_exits; i++) {
        printf("%i ", parts[i]);
        sum += parts[i];
    }
    printf("%i ", sum);


//TESTEND

    free(parts);
    parts = NULL;

    free(partial_sum);
    partial_sum = NULL;

    free(rand_upper_incbound);
    rand_upper_incbound = NULL;

    return 0;
}