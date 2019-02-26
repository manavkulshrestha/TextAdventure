#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

#define DEFAULT_BACKPACK_SIZE 5

int main() {
    char *command = (char *) malloc(10*sizeof(char));
    char *param = (char *) malloc(10*sizeof(char));

    int *backpack_size = (int *) malloc(sizeof(int));
    backpack_size = DEFAULT_BACKPACK_SIZE;
    int *item_count = (int *) malloc(sizeof(int));
    item_count = 0;

    Item *backpack = (Item *) malloc(backpack_size*sizeof(Item));

    Room *current_room = (Room *) malloc(sizeof(Room));
    // int* field[] = 
    current_room = gen_room(3, field);

    do {
        scanf("%s %s", command, param);
        command = strlwr(command);
        param = strlwr(param);

        if(strcmp(command, "go") == 0) {
            if(strcmp(param, "north") == 0) {

            } else if(strcmp(param, "south") == 0) {

            } else if(strcmp(param, "east") == 0) {
                
            } else if(strcmp(param, "west") == 0) {
                
            } else if(strcmp(param, "up") == 0) {
                
            } else if(strcmp(param, "down") == 0) {
                
            } else {

            }
            
        } else if(strcmp(command, "look") == 0) {
            
        } else if(strcmp(command, "take") == 0) {//revise how freeing works
            Item *temp = (Item *) malloc(sizeof(Item));
            temp = item_take(param, current_room->items);

            if(temp != NULL) {
                if(item_count < backpack_size) {
                    item_add(backpack, temp);
                    item_count++;
                } else {
                    printf("Backpack is full. Increase capacity or drop an item to make space.");
                }
            } else {
                printf("Item '%s' not found", param);
            }
            free(temp);
            temp = NULL;
            
        } else if(strcmp(command, "drop") == 0) {
            Item *temp = (Item *) malloc(sizeof(Item));
            temp = item_take(param, backpack);

            if(temp != NULL) {
                item_add(current_room->items, temp);
                item_count--;
            } else {
                printf("Item '%s' not found", param);
            }
            free(temp);
            temp = NULL;

        } else if(strcmp(command, "use") == 0) {
            
        }

    } while(1)

    return 0;
}