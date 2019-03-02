#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    int *yee = (int *) malloc(sizeof(int));
    yee = random_number(1, 2);

    printf("%i",*yee);

    free(yee);
    yee = NULL;

    return 0;
}