#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"
#include <stdbool.h>

#define DEFAULT_BACKPACK_SIZE 5
#define ROOM_VARIATIONS 5
#define ITEM_VARIATIONS 5
#define MAX_ITEMS_IN_ROOM 5
#define ROOM_COUNT 20
#define INITIAL_GOPE 0
#define DIRECTION_COUNT 6
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

Room *room_gen(int rooms_to_create, Room *prev_room, int direction, char* room_descriptions[ROOM_VARIATIONS], char* item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3], bool key) {
    if(rooms_to_create <= 0)
        return;

    int *num_items = random_number(2, MAX_ITEMS_IN_ROOM-1);//arbitrary range
    int *room_type = random_number(0, ROOM_VARIATIONS-1);//any room possible
    Item *room_items = rand_items(num_items, room_type, item_possibilities);

    int *valid_exits = (int *) malloc(sizeof(int));
    *valid_exits = EXIT_COUNT;//number of exist which will be recursively generated.

    Room *current_room = room(room_descriptions[*room_type], room_items, NULL, NULL, NULL, NULL, NULL, NULL, (key) ? ROOM_LOCKED : ROOM_UNLOCKED);
    if(prev_room != NULL) {
        room_connect(prev_room, current_room, direction);
        (*valid_exits)--;//don't want to create rooms in the same place.
    }
    rooms_to_create--;

    //partition rooms_to_create into EXIT_COUNT unequal random numbers
    

    for(int i=0; i<EXIT_COUNT-1; i++) {
        if(current_room->exits[i] == NULL) {
            int *rooms_to_create_ = random_number(rooms);

            current_room->exits[i] = room_gen()
        }
    }

    return current_room;
}

Item *rand_items(int *num_items, int *room_type, char *item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3]) {
    Item *items = item("", "", 0, -1, NULL);

    for(int i=0; i<*num_items; i++) {
        int *item_type = random_number(0, ITEM_VARIATIONS-1);

        items_add(items, item(
            item_possibilities[*room_type][*item_type][0],
            item_possibilities[*room_type][*item_type][1],
            1,
            atoi(item_possibilities[*room_type][*item_type][2]),
            NULL
        ));

        free(item_type);
        item_type = NULL;
    }

    return items;
}

int main(void) {
    char *room_descriptions[ROOM_VARIATIONS] = {
        "Library. It has books... not sure how you're supposed to import this.",
        "Shrine Room. A worn out inscription that seems to say -- T*m R*ch*rds.",
        "Dorm Hall. It smells of old socks and stale ketchup",
        "Dining Hall. Did you know that UMass was rated #1, 4 years in a row?",
        "LGRC A104. The charging points here don't work, for some reason.",
    };

    char *item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3] = {
        {
            {"Programming In C (3rd Edition)", "Could prove very useful for the exams", "1"},
            {"The Linux Programming Interface", "Could prove very useful for the exams", "1"},
            {"Discrete Mathematics: A Foundation for Computer Science", "Could prove very useful for the exams", "1"},
            {"Introduction To Probability (2nd Edition)", "Could prove very useful for the exams", "1"},
            {"Tying Knots for Dummies", "Could prove very useful after the exams", "1"}
        },
        {
            {"Green and Blue Vest", "Worn by the King himself. (Armour)", "10"},
            {"Plaque", "Official disbandment of global variables. (Shield)", "3"},
            {"Flashdrive", "Completely implemented Project 2. No need for an extension. (Door Key)", "0"},
            {"Gilbert Herndon", "Nic Huph.", "-1"},
            {"Baseball Hat", "Dat Dad Hat. (Armour)", "3"}
        },
        {
            {"Empty Condom Wrapper", "Wrap your willie, don't be silly.", "-1"}, 
            {"Phone", "The only installed app is Discord, on light mode nontheless.", "-1"},
            {"Pee Mentor Sign", "Seems like some letters R missing. (Shield)", "1"},
            {"Rotten Banana", "Just a rotten banana sitting on the ground.", "-1"},
            {"Katana", "From the weeb next door. (Weapon)", "10"}
        },
        {
            {"General Tso's Peppers", "Now with extra chicken. (yes gope)", "5"}, 
            {"Chicken Tenders", "Reeeee, give me tendies. (medium gope)", "3"},
            {"Butter Knife", "Faint stains of jelly can be seen. (Weapon)", "6"},
            {"Diet Coke", "No insulin required, diabetic friendly. (no gope)", "2"},
            {"Canada Dry", "Frothy boi. (no gope)", "2"}
        },
        {
            {"Pencil", "It's particularly sharp. (Weapon)", "3"}, 
            {"Answer Sheet", "I hope this exam was scaled. (Door Key)", "0"},
            {"Notebook", "Contains solutions for a CS240 Homework. (Door Key)", "0"},
            {"Homework Solutions", "Seems correct, but then again, everything does. (Door Key)", "0"},
            {"Cowboy Hat", "Often dawned by Jared. (Armour)", "5"}
        }
    };

    char *directions[EXIT_COUNT] = {
        "north",
        "south",
        "east",
        "west",
        "up",
        "down"
    };
    
    srand(time(NULL));

    //Current gope
    int *gope = (int *) malloc(sizeof(int));
    *gope = INITIAL_GOPE;

    //number of different items player can have
    int *backpack_size = (int *) malloc(sizeof(int));
    *backpack_size = DEFAULT_BACKPACK_SIZE;

    //number of different items player has
    int *item_count = (int *) malloc(sizeof(int));
    *item_count = 0;

    // backpack (linked list of items)
    Item *backpack = (Item *) malloc(*backpack_size*sizeof(Item));

    Room *current_room;
    // current_room = room_gen(room_descriptions, item_possibilities);
    current_room = room_gen(room_descriptions, item_possibilities);

    //used for input parsing
    char *buffer = (char *) malloc(BUFFER_LENGTH*sizeof(char));
    char *command; //freed inside the loop to prevent memory leak
    char *param; //freed inside the loop to prevent memory leak
    do {
        printf("> ");

        // get input including spaces
        int *buffer_length = (int *) malloc(sizeof(int));

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

        // if there is more than one word, copy everyhting after space_index into 'param'if(*space_index != *buffer_length){
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
        
        if(strcmp(command, "go") == 0 && param != NULL) {
            for(int direction_index=0; direction_index<EXIT_COUNT; direction_index++) {
                if(strcmp(directions[direction_index], param) == 0) {

                    if(current_room->exits[direction_index] == NULL) {
                        printf("Do you want to Seg fault? Because that's how you Seg fault");

                    } else if(*(current_room->exits[direction_index]->state) == ROOM_UNLOCKED) {
                        current_room = current_room->exits[direction_index];
                        printf("You go through the %s exit", directions[direction_index]);

                    } else if(*(current_room->exits[direction_index]->state) == ROOM_LOCKED) {
                        printf("Your question is 'Can I pass?' But, Prof. Joe Chiu has a question for you!\n");
                        printf("...And you don't know the answer. Maybe someone left some solutions lying around.\n");
                    }
                    break;
                }
            }
            
        } else if(strcmp(command, "look") == 0) {
            int *room_state = (int *) malloc(sizeof(int));

            printf("You find yourself in a %s\n\n", current_room->description);

            for(int direction_index=0; direction_index<EXIT_COUNT; direction_index++) {
                printf("The %s exit leads to ", directions[direction_index]);
                if((*room_state = check_direction(current_room, direction_index)) == ROOM_UNLOCKED) {
                    printf("an unlocked room");
                } else if(*room_state == ROOM_LOCKED) {
                    printf("a locked room");
                } else {
                    printf("nothing. It's solid concrete");
                }
                printf(" ROOM STATE: %i", *room_state);
                printf("\n");
            }
            printf("\nRoom ");
            item_print(current_room->items);

            printf("\n\nBackpack ");
            item_print(backpack);
            
            printf("ROOM STATE: %i", *(current_room->state));

            free(room_state);
            room_state = NULL;
            
        } else if(strcmp(command, "take") == 0 && param != NULL) {
            //temporarily take item from room (might be returned if backpack is full)
            Item *room_item = item_take(param, current_room->items);

            // item is in room
            if(room_item != NULL) {
                Item *backpack_item = item_find(param, backpack);

                if(backpack_item == NULL) {
                    //player doesn't already have item.
                    if(*item_count < *backpack_size) {
                        item_add(backpack, room_item);
                        (*item_count)++;
                        printf("Took item '%s' (x%i)", room_item->name, *(room_item->count));

                    } else {
                        item_add(current_room->items, room_item);
                        printf("You can't hold more item types. Either drop some or get better at memory management");
                    }
                } else {
                    //player has already has item.
                    *(backpack_item->count) += *(room_item->count);
                    printf("Took item '%s' (x%i)", room_item->name, *(room_item->count));
                    item_free(room_item);
                }

            } else {
                printf("Item '%s' not found", param);
            }

        } else if(strcmp(command, "drop") == 0 && param != NULL) {
            Item *temp = item_take(param, backpack);

            if(temp != NULL) {
                printf("Dropped item '%s' (x%i)", temp->name, *(temp->count));
                item_add(current_room->items, temp);
                (*item_count)--;

            } else {
                printf("Item '%s' not found", param);
            }

        } else if(strcmp(command, "use") == 0 && param != NULL) {
            Item *temp = item_find(param, backpack);

            if(temp == NULL) {
                printf("Item not '%s' found", param);
                
            } else {
                if(*(temp->attribute) < 0) {//unusable item
                    printf("You can't really use that item");
                    item_add(backpack, temp);

                } else if(*(temp->attribute) == 0) {//key
                    printf("Which exit?: ");
                    scanf("%s", buffer);

                    for(int direction_index=0; direction_index<EXIT_COUNT; direction_index++) {
                        if(strcmp(directions[direction_index], param) == 0) {
                            if(current_room->exits[direction_index] == NULL) {
                                printf("That's not how any of this works.");

                            } else if(*(current_room->exits[direction_index]->state) == ROOM_UNLOCKED) {
                                printf("This door is already unlocked");

                            } else if(*(current_room->exits[direction_index]->state) == ROOM_LOCKED) {
                                printf("Prof. Joe Chiu accepts your answer and lets you pass");
                                (*(temp->count))--;

                            }
                            break;
                        }
                    }

                } else if(*(temp->attribute) == 1) {//book}
                    (*backpack_size) += *(temp->attribute);
                    printf("You've gotten smarter and thus, better at memory management. Backpack size increased by %i", *(temp->attribute));
                    (*(temp->count))--;

                } else {
                    // comparing a character in description to see what the item s used for
                    int *len = (int *) malloc(sizeof(int));
                    *len = strlen(temp->description);

                    if(temp->description[*len-1] == ')') {
                        if(temp->description[*len-2] =='e') {//gope
                            *gope += *(temp->attribute);
                            printf("You feel nourished. Your gope level is now at %i", *gope);
                            (*(temp->count))--;

                        } else if(temp->description[*len-2] =='n') {//Weapon
                            *gope -= *(temp->attribute);
                            printf("You whip out the %s, swing it around, and hurt yourself in your confusion.\n", temp->name);
                            printf("Your gope level is now at %i", *gope);
                        
                        } else if(temp->description[*len-2] =='r') {//Armour
                            printf("You may have put on their apparel, but you will never be a God\n");
                        
                        } else if(temp->description[*len-2] =='d') {//Shield
                            printf("You carefully hold up your shield... realize there are no threats, feel stupid, and put it down");

                        }
                    }
                    free(len);
                    len = NULL;
                }

                if(*(temp->count) == 0) {
                    temp = item_take(param, backpack);
                    item_free(temp);
                }
            }

        } else {
            printf("Invalid command (case sensitive)");
        }
        printf("\n\n");

        free(command);
        command = NULL;
        free(param);
        param = NULL;
    } while(1);

    // free everything
    free(gope);
    gope = NULL;

    free(backpack_size);
    backpack_size = NULL;

    free(item_count);
    item_count = NULL;
    
    item_free(backpack);
    
    free(buffer);
    buffer = NULL;

    room_free(current_room);//recursively frees all rooms
    current_room = NULL;

    return 0;
}