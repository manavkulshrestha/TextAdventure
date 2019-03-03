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
#define ROOM_COUNT 10
#define INITIAL_GOPE 0
#define BUFFER_LENGTH 100

/*
    int min_num - lower bound for random number generation (inclusive)
    int man_num - Upper bound for random number generation (inclusive)

    Generates a random number in range min_num and max_num

    returns:
    int *result - random number between min_num and max_num
*/
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

/*
    int *num_items - Number of items to be generated
    int *current_room_index - Index denoting what type of room the items will be placed in
    int *key_flag - This is modified depending on whether a Door Key item is generated for the room
    char *item_possibilities[][][] - A pool containing all the item possibilities (name, description, attribute), ordered by room type

    Generates a Linked List of Items to be placed in a room.

    return:
    Items *items - a Linked List of items which contains num_items items, chosen randomly from the pool item_possibilities, depending on the current_room_index
*/
Item *rand_items(int *num_items, int *current_room_index, int *current_item_index, int *key_flag, char *item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3]) {
    Item *items = item("","",1,-1,NULL); // Dummy starter for items
    for(int i = 0; i < *num_items; i++) {
        current_item_index = random_number(0, ITEM_VARIATIONS-1);

        item_add(items, item(item_possibilities[*current_room_index][*current_item_index][0],
                        item_possibilities[*current_room_index][*current_item_index][1],
                        1,
                        atoi(item_possibilities[*current_room_index][*current_item_index][2]),
                        NULL));
        if(atoi(item_possibilities[*current_room_index][*current_item_index][2]) == 0)
            *key_flag = 1;
        free(current_item_index);
        current_item_index = NULL;
    }
    free(num_items);
    num_items = NULL;

    return items;
}

/*
    char *room_descriptions[] - A pool containing descriptions for all room variations
    char *item_possibilities[][][] -  A pool containing all the item possibilities (name, description, attribute), ordered by room type

    Generates ROOM_COUNT number of rooms linked to eachother in random directions from the top down.
    The basic algorithm is: generate final room, then sequentially generate connections in random directions until there are no more rooms to generate

    returns:
    Room *current_room - the final room generated (starting room)
*/
Room *room_gen(char *room_descriptions[ROOM_VARIATIONS], char *item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3]) {
    int *rooms_remaining = (int *) malloc(sizeof(int));
    *rooms_remaining = ROOM_COUNT; // Keep track of how many rooms have been generated

    /* ALLOCATED STUFF FOR MEMORY MANAGEMENT */
    int *various_rands; // Various other random quantities (Items per room, links per room, etc.)
    int *various_rands2; // Various other random quantities (Items per room, links per room, etc.)
    int *current_room_index; // Room possibility index
    int *current_item_index; // Item possibility index
    int *key_flag = (int *) malloc(sizeof(int)); // Flag to keep track of most recently generated key. If key is 1, the next room will be locked
    *key_flag = 0;

    /* INITIALIZE ENDING ROOM AND ITS ITEMS */
    various_rands = random_number(2, 4); // Number of items in room
    current_room_index = random_number(0, ROOM_VARIATIONS-1); // Update room possibility index
    
    Room *ending_room = room("Congratulations! This is the final room!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, ROOM_FINAL);
    *key_flag = 0;
    (*rooms_remaining)--; // One less room remaining

    free(current_room_index); // Free for later use
    current_room_index = NULL;    

    /* At this point, a room is inialized. The ball is rolling and we now keep generating until no more rooms remain */
    Room *prev_room = ending_room;
    Room *current_room;
    while(*rooms_remaining > 0) { // Terminate loop when there are no more rooms left to generate

        /* INITIALIZE NEW ROOM */
        various_rands = random_number(2, 4); // Number of items in room
        current_room_index = random_number(0, ROOM_VARIATIONS-1); // Update room possibility index

        Item *items = rand_items(various_rands, current_room_index, current_item_index, key_flag, item_possibilities);
        if(*key_flag == 1 && *(prev_room->state) != ROOM_FINAL) 
            *(prev_room->state) = ROOM_LOCKED;
        *key_flag = 0;
        current_room = room(room_descriptions[*current_room_index], items, NULL, NULL, NULL, NULL, NULL, NULL, ROOM_UNLOCKED);
        
        /* CONNECT NEW ROOM TO PREVIOUS */
        various_rands = random_number(1,6); // Randomize direction of new room with respect to old one
        while(check_direction(prev_room, *various_rands) != ROOM_NO_ROOM) { // Make sure direction isn't already occupied
            free(various_rands);
            various_rands = NULL;

            various_rands = random_number(1,6);
        }
        room_connect(prev_room, current_room, *various_rands); // Connect the previous room and the room we just generated
        
        free(current_room_index); // Free for later use
        current_room_index = NULL;

        free(various_rands); // Free for later use
        various_rands = NULL;

        (*rooms_remaining)--; // One less room remaining
        if(*rooms_remaining <= 0)
            break;

        prev_room = current_room; // Set up for the next iteration
        current_room = NULL;
    }
    return current_room;
}

/*
    Main function. This is where the game takes place
*/
int main(void) {
    // Pools for random room and item generation
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

    // to easily convert int representing a direction to a char * for comparision.
    char *directions[EXIT_COUNT] = {
        "north",
        "south",
        "east",
        "west",
        "up",
        "down"
    };
    
    //seeds the random number generator
    srand(time(NULL));

    //Current gope
    int *gope = (int *) malloc(sizeof(int));
    *gope = INITIAL_GOPE;

    //number of different items player can have
    int *backpack_size = (int *) malloc(sizeof(int));
    *backpack_size = DEFAULT_BACKPACK_SIZE;

    //number of different item types player has
    int *item_count = (int *) malloc(sizeof(int));
    *item_count = 0;

    // backpack (linked list of items)
    Item *backpack = (Item *) malloc(*backpack_size*sizeof(Item));

    // The room the player is currently in
    Room *current_room;
    current_room = room_gen(room_descriptions, item_possibilities);

    //used for input parsing
    char *buffer = (char *) malloc(BUFFER_LENGTH*sizeof(char));
    char *command; //freed inside the loop to prevent memory leak
    char *param; //freed inside the loop to prevent memory leak
    do {
        printf("> ");

        // get input including spaces
        int *buffer_length = (int *) malloc(sizeof(int));

        scanf("%[^\n]%*c", buffer);
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
        
        // GO command
        if(strcmp(command, "go") == 0 && param != NULL) {
            for(int direction_index=0; direction_index<EXIT_COUNT; direction_index++) {
                if(strcmp(directions[direction_index], param) == 0) {

                    // room exit doesn't exit/is a wall
                    if(current_room->exits[direction_index] == NULL) {
                        printf("Do you want to Seg fault? Because that's how you Seg fault");

                    // room is unlocked (or final room, since the final room is "unlocked", but has a different state)
                    } else if(*(current_room->exits[direction_index]->state) == ROOM_UNLOCKED || *(current_room->exits[direction_index]->state) == ROOM_FINAL) {
                        current_room = current_room->exits[direction_index];
                        printf("You go through the %s exit", directions[direction_index]);

                    // room is locked
                    } else if(*(current_room->exits[direction_index]->state) == ROOM_LOCKED) {
                        printf("Your question is 'Can I pass?' But, Prof. Joe Chiu has a question for you!\n");
                        printf("...And you don't know the answer. Maybe someone left some solutions lying around.\n");
                    }
                    break;
                }
            }
            
        // LOOK command
        } else if(strcmp(command, "look") == 0) {
            int *room_state = (int *) malloc(sizeof(int));

            printf("You find yourself in a %s\n\n", current_room->description);

            // Printing out states of all exits
            for(int direction_index=0; direction_index<EXIT_COUNT; direction_index++) {
                printf("The %s exit leads to ", directions[direction_index]);
                if((*room_state = check_direction(current_room, direction_index)) == ROOM_UNLOCKED || (*room_state = check_direction(current_room, direction_index)) == ROOM_FINAL) {
                    printf("an unlocked room");
                } else if(*room_state == ROOM_LOCKED) {
                    printf("a locked room");
                } else {
                    printf("nothing. It's solid concrete");
                }
                printf("\n");
            }
            // Printing out the items in the room
            printf("\nRoom ");
            item_print(current_room->items);

            // Printing out contents of backpack
            printf("\n\nBackpack ");
            item_print(backpack);
            
            // Freeing the temporary variable used to check room states
            free(room_state);
            room_state = NULL;
            
        } else if(strcmp(command, "take") == 0 && param != NULL) {
            //temporarily take item from room (might be returned if backpack is full)
            Item *room_item = item_take(param, current_room->items);

            // check whether item is in room
            if(room_item != NULL) {
                Item *backpack_item = item_find(param, backpack);

                // check whether player already has said item
                if(backpack_item == NULL) {
                    //check whether player has enough space for item
                    if(*item_count < *backpack_size) {
                        item_add(backpack, room_item);
                        (*item_count)++;
                        printf("Took item '%s' (x%i)", room_item->name, *(room_item->count));

                    } else {
                        item_add(current_room->items, room_item);
                        printf("You can't hold more item types. Either drop some or get better at memory management");
                    }
                } else {
                    // if player already had said item, increase the count for the item in the backpack and free the one from the room
                    *(backpack_item->count) += *(room_item->count);
                    printf("Took item '%s' (x%i)", room_item->name, *(room_item->count));
                    item_free(room_item);
                }

            } else {
                printf("Item '%s' not found", param);
            }

        // DROP command
        } else if(strcmp(command, "drop") == 0 && param != NULL) {
            // taking item from backpack
            Item *temp = item_take(param, backpack);

            // checking if item was found in backpack
            if(temp != NULL) {
                printf("Dropped item '%s' (x%i)", temp->name, *(temp->count));
                item_add(current_room->items, temp);
                (*item_count)--;

            } else {
                printf("Item '%s' not found", param);
            }

        // USE command
        } else if(strcmp(command, "use") == 0 && param != NULL) {
            // finds item to use (May not be consumed)
            Item *temp = item_find(param, backpack);

            // checking if item was found in backpack
            if(temp == NULL) {
                printf("Item not '%s' found", param);
                
            } else {
                // -1 attribute means the item is useless
                if(*(temp->attribute) < 0) {
                    printf("You can't really use that item");
                    item_add(backpack, temp);

                // 0 attribute means the item is a key
                } else if(*(temp->attribute) == 0) {
                     //"north\0" and "south\0" are 6 big
                    char *dir_buffer = (char *) malloc(6*sizeof(char));
                    // getting which exit to use key on
                    printf("Which exit?: ");
                    scanf("%[^\n]%*c", dir_buffer);

                    // iterating to convert char * of direction into an int to be used for state comparision
                    for(int direction_index=0; direction_index<EXIT_COUNT; direction_index++) {
                        if(strcmp(directions[direction_index], dir_buffer) == 0) {
                            if(current_room->exits[direction_index] == NULL) {
                                printf("That's not how any of this works.");

                            } else if(*(current_room->exits[direction_index]->state) == ROOM_UNLOCKED || *(current_room->exits[direction_index]->state) == ROOM_FINAL) {
                                printf("This door is already unlocked");

                            } else if(*(current_room->exits[direction_index]->state) == ROOM_LOCKED) {
                                printf("Prof. Joe Chiu accepts your answer and lets you pass");
                                (*(temp->count))--;
                                *(current_room->exits[direction_index]->state) = ROOM_UNLOCKED;
                            }
                            break;
                        }
                    }

                    // freeing temporary buffer used to get input
                    free(dir_buffer);
                    dir_buffer = NULL;

                // 1 attribute signifies that item is a book
                } else if(*(temp->attribute) == 1) {
                    // increases backpack by 1. Generalized so it can be scaled later
                    (*backpack_size) += *(temp->attribute);
                    printf("You've gotten smarter and thus, better at memory management. Backpack size increased by %i", *(temp->attribute));
                    //consumes one book
                    (*(temp->count))--;

                } else {
                    // temporary variable to store length of description
                    int *len = (int *) malloc(sizeof(int));
                    *len = strlen(temp->description);

                    // all "special" items have a ')' character at the end of their description. Ex. (Emrour)
                    if(temp->description[*len-1] == ')') {
                        // comparing second last character to item is supposed to do
                        if(temp->description[*len-2] =='e') {//increase gope
                            *gope += *(temp->attribute);
                            printf("You feel nourished. Your gope level is now at %i", *gope);
                            //consumes one one count of item
                            (*(temp->count))--;

                        } else if(temp->description[*len-2] =='n') {//Weapon
                            //damages gope by attribute of weapon
                            *gope -= *(temp->attribute);
                            printf("You whip out the %s, swing it around, and hurt yourself in your confusion.\n", temp->name);
                            printf("Your gope level is now at %i", *gope);
                        
                        } else if(temp->description[*len-2] =='r') {//Armour
                            printf("You may have put on their apparel, but you will never be a God\n");
                        
                        } else if(temp->description[*len-2] =='d') {//Shield
                            printf("You carefully hold up your shield... realize there are no threats, feel stupid, and put it down");

                        }
                    }
                    // freeing temporary variable
                    free(len);
                    len = NULL;
                }

                // if usage of an item recued its count to 0, remove it from backpack and free it.
                if(*(temp->count) == 0) {
                    temp = item_take(param, backpack);
                    item_free(temp);
                }
            }

        } else {
            printf("Invalid command (case sensitive)");
        }
        printf("\n\n");

        // free the command and param to be allocated again at the top of the loop
        free(command);
        command = NULL;

        free(param);
        param = NULL;

    // run until player reaches final room
    } while(*(current_room->state) != ROOM_FINAL);

    // custom message depending on the player's gope
    printf("You survived CS 230 and 240 with a final gope of %i. ", *gope);
    printf("\n");
    if(*gope < 16) 
        printf("Oof, that's not a lot of gope... A W on my transcript isn't that bad, right? \n");
    else if(*gope < 21)
        printf("Medium gope. You did... average, yay. \n");
    else if(*gope >= 21)
        printf("Dear students. The professors decided to adjust the grades for the first exam. It turns out there was gope after all \n");

    // free everything else that was being used
    free(gope);
    gope = NULL;

    free(backpack_size);
    backpack_size = NULL;

    free(item_count);
    item_count = NULL;
    
    item_free(backpack); // recursively free all the items in backpack
    backpack = NULL;
    
    free(buffer);
    buffer = NULL;

    room_free(current_room); // recursively frees all rooms
    current_room = NULL;

    return 0;
}