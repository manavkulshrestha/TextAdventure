#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "items.h"

int main(void) {

    // char *buffer = (char *) malloc(100*sizeof(char));
    // char *param = (char *) malloc(100*sizeof(char));
    // char *command = (char *) malloc(100*sizeof(char));


    // scanf ("%[^\n]%*c", buffer);
    // int *space_index = (int *) malloc(sizeof(int));

    // *space_index = 0;
    // while(*space_index < strlen(buffer) && buffer[*space_index] != ' ')
    //     (*space_index)++;

    // strncpy(command, buffer, *space_index);
    // command[*space_index] = '\0';

    // strncpy(param, buffer+(*space_index)+1, strlen(buffer)-(*space_index)-1);
    // param[strlen(param)] = '\0';

    // printf("'%s'\n", command);
    // printf("'%s'", param);

    // Item *i = item("", "", 1, -1, NULL);





    int *i = (int *) malloc(sizeof(int));
    int *j = i;
    *i = 5;
    *i = 8;
    printf("%i", *j);
    free(i);
    
    return 0;
}