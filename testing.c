#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"

#define BUFFER_LENGTH 100

int main(void) {
    char *buffer = (char *) malloc(BUFFER_LENGTH*sizeof(char));
    int *buffer_length = (int *) malloc(sizeof(int));

    char *command;
    char *param;

    scanf ("%[^\n]%*c", buffer);
    *buffer_length = strlen(buffer);

    //get index of space
    int *space_index = (int *) malloc(sizeof(int));
    *space_index = 0;
    while(*space_index < *buffer_length && buffer[*space_index] != ' ')
        (*space_index)++;

    //copy everything before space_index into 'command'
    command = (char *) malloc((*space_index+1)*sizeof(char));
    strncpy(command, buffer, *space_index);
    command[*space_index] = '\0';

    // if there is more than one word, copy everyhting after space_index into 'param'
    // printf("'%i'\n", *space_index);
    // printf("'%i'\n", *buffer_length);

    if(*space_index != *buffer_length){
        int *len = (int *) malloc(sizeof(int));
        *len = BUFFER_LENGTH-*space_index-1;

        param = (char *) malloc((*len+1)*sizeof(char));
        strncpy(param, buffer+*space_index+1, *len);
        param[*len] = '\0';

        free(len);
        len = NULL;
    } else {
        param = NULL;
    }

    printf("'%s'\n", command);
    printf("'%s'\n", param);

    return 0;
}