#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

#define DEFAULT_BACKPACK_SIZE 5

int main() {
    char *command = (char *) malloc(10*sizeof(char));
    char *param = (char *) malloc(10*sizeof(char));
    Item *backpack = (Item *) malloc(DEFAULT_BACKPACK_SIZE*sizeof(Item));
    Room *current_room = (Room *) malloc(sizeOf(Room));
    int* field[] = 
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
            
        } else if(strcmp(command, "take") == 0) {
            if(strcmp(command, "all") == 0) {

            } else {
                
            }
            
        } else if(strcmp(command, "drop") == 0) {

        } else if(strcmp(command, "use") == 0) {

        }

    } while(1)

    return 0;
}