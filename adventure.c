#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"

#define DEFAULT_BACKPACK_SIZE 5
#define ROOM_VARIATIONS 5
#define ITEM_VARIATIONS 5
#define ROOM_COUNT 10
#define INITIAL_GOPE 10
#define INITIAL_DAMAGE 0
#define INITIAL_ARMOUR 0
#define INITIAL_SHIELD 0
#define DIRECTION_COUNT 6

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

Room *room_gen(const char* room_descriptions[ROOM_VARIATIONS], const char* item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3]) {
    int *rooms_remaining = (int *) malloc(sizeof(int));
    *rooms_remaining = ROOM_COUNT;

    int *len = (int *) malloc(sizeof(int));//temporary variable to store string lengths
    
    char *room_description;
    int *various_rands; // Various other random quantities (Items per room, links per room, etc.)
    int *various_rands2; // Various other random quantities (Items per room, links per room, etc.)
    int *current_room_index; // Room possibility index
    int *current_item_index; // Item possibility index

    /* INITIALIZE ENDING ROOM AND ITS ITEMS */
    various_rands = random_number(2, 4); // Number of items in room
    current_room_index = random_number(0, ROOM_VARIATIONS-1); // Update room possibility index
    Item *items = item("","",1,-10,NULL); // Dummy starter for items
    for(int i = 0; i > *various_rands; i++) {
        current_item_index = random_number(0, ITEM_VARIATIONS-1);
        
        *len = strlen(item_possibilities[*current_room_index][*current_item_index][0]);
        char* name = (char *) malloc((*len+1)*sizeof(char));
        strncpy(name, item_possibilities[*current_room_index][*current_item_index][0], *len);
        name[*len] = '\0';

        *len = strlen(item_possibilities[*current_room_index][*current_item_index][1]);
        char* description = (char *) malloc((*len+1)*sizeof(char));
        strncpy(description, item_possibilities[*current_room_index][*current_item_index][1], *len);
        description[*len] = '\0';

        item_add(items, item(description,
                        name,
                        1,
                        atoi(item_possibilities[*current_room_index][*current_item_index][2]),
                        NULL));
        free(current_item_index);
        current_item_index = NULL;

        free(name);
        name = NULL;
        
        free(description);
        description = NULL;
    }
    free(various_rands);
    various_rands = NULL;

    *len = strlen(room_descriptions[*current_room_index]);
    room_description = (char *) malloc((*len+1)*sizeof(char));
    strncpy(room_description, room_descriptions[*current_room_index], *len);
    room_description[*len] = '\0';

    Room *ending_room = room(room_description, items, NULL, NULL, NULL, NULL, NULL, NULL, 2);
    (*rooms_remaining)--;
    
    free(room_description);
    room_description = NULL;

    free(current_room_index);
    current_room_index = NULL;
    
    items = NULL; // Clear for later use
    

    /* At this point, a room is inialized. The ball is rolling and we now keep generating until no more rooms remain */
    Room *prev_room = ending_room;
    Room *current_room;
    while(*rooms_remaining > 0) {

        /* ITEMS FOR NEW ROOM */
        various_rands = random_number(2, 4); // Number of items in room
        current_room_index = random_number(0, ROOM_VARIATIONS-1); // Update room possibility index
        items = item("","",1,-10,NULL); // Dummy starter for items
        for(int i = 0; i > *various_rands; i++) {
            current_item_index = random_number(0, ITEM_VARIATIONS-1);

            *len = strlen(item_possibilities[*current_room_index][*current_item_index][0]);
            char* name = (char *) malloc((*len+1)*sizeof(char));
            strncpy(name, item_possibilities[*current_room_index][*current_item_index][0], *len);
            name[*len] = '\0';
            
            *len = strlen(item_possibilities[*current_room_index][*current_item_index][1]);
            char* description = (char *) malloc((*len+1)*sizeof(char));
            strncpy(description, item_possibilities[*current_room_index][*current_item_index][1], *len);
            description[*len] = '\0';

            item_add(items, item(description,
                            name,
                            1,
                            atoi(item_possibilities[*current_room_index][*current_item_index][2]),
                            NULL));
            free(current_item_index);
            current_item_index = NULL;

            free(name);
            name = NULL;
            
            free(description);
            description = NULL;
        }
        free(various_rands);
        various_rands = NULL;


        /* INITIALIZE NEW ROOM */
        *len = strlen(room_descriptions[*current_room_index]);
        room_description = (char *) malloc((*len+1)*sizeof(char));
        strncpy(room_description, room_descriptions[*current_room_index], *len+1);
        room_description[*len] = '\0';

        free(room_description);
        room_description = NULL;

        current_room = room(room_description, items, NULL, NULL, NULL, NULL, NULL, NULL, 2);
        various_rands = random_number(1,6); // Randomize direction of new room with respect to old one
        while(check_direction(prev_room, *various_rands) != ROOM_NO_ROOM) { // Make sure direction isn't already occupied
            free(various_rands);
            various_rands = NULL;

            various_rands = random_number(1,6);
        }
        room_connect(prev_room, current_room, *various_rands);
        
        free(various_rands);
        various_rands = NULL;
        
        free(current_room_index);
        current_room_index = NULL;
        
        (*rooms_remaining)--;
        if(*rooms_remaining <= 0)
            return current_room;
        
        
        /* MAKE EXTRANEOUS ROOMS */
        various_rands = random_number(0, 2); // Number of 'extraneous' connections to room
        for(int i = 0; i < *various_rands; i++) {

            /* ITEMS FOR NEW EXTRANEOUS ROOMS */
            various_rands2 = random_number(2, 4); // Number of items in room
            current_room_index = random_number(0, ROOM_VARIATIONS-1); // Update room possibility index
            items = item("","",1,-10,NULL); // Dummy starter for items
            for(int i = 0; i > *various_rands2; i++) {
                current_item_index = random_number(0, ITEM_VARIATIONS-1); // Random item

                *len = strlen(item_possibilities[*current_room_index][*current_item_index][0]);
                char *name = (char *) malloc((*len+1)*sizeof(char));
                strncpy(name, item_possibilities[*current_room_index][*current_item_index][0], *len);
                name[*len] = '\0';

                *len = strlen(item_possibilities[*current_room_index][*current_item_index][1]);
                char *description = (char *) malloc((*len+1)*sizeof(char));
                strncpy(description, item_possibilities[*current_room_index][*current_item_index][1], *len);
                description[*len] = '\0';

                item_add(items, item(description,
                                name,
                                1,
                                atoi(item_possibilities[*current_room_index][*current_item_index][2]),
                                NULL));
                free(current_item_index);
                current_item_index = NULL;

                free(name);
                name = NULL;
                
                free(description);
                description = NULL;
            }
            free(various_rands2);
            various_rands2 = NULL;

            /* CONNECT EXTRANEOUS ROOM TO CURRENT ROOM */
            various_rands2 = random_number(1,6); // Randomize direction of new room with respect to old one
            while(check_direction(prev_room, *various_rands2)!=0) { // Make sure direction isn't already occupied
                free(various_rands2);
                various_rands2 = NULL;

                various_rands2 = random_number(1,6);
            }

            *len = strlen(room_descriptions[*current_room_index]);
            room_description = (char *) malloc((*len+1)*sizeof(char));
            strncpy(room_description, room_descriptions[*current_room_index], *len);
            room_description[*len] = '\0';

            room_connect(current_room, room(room_description, items, NULL, NULL, NULL, NULL, NULL, NULL, 2), *various_rands2);
            
            free(room_description);
            room_description = NULL;

            free(various_rands2);
            various_rands2 = NULL;
            
            (*rooms_remaining)--;
            if(*rooms_remaining <= 0) {
                free(current_room_index);
                current_room_index = NULL;
                
                free(various_rands);
                various_rands = NULL;
                return current_room;
            }
            free(current_room_index);
            current_room_index = NULL;
        }
        free(various_rands);
        various_rands = NULL;

        prev_room = current_room;
        current_room = NULL;
    }
    return current_room;
}

int main() {
    const char* room_descriptions[ROOM_VARIATIONS] = {
        "Library. It has books... not sure how you're supposed to import this.",
        "Shrine Room. A worn out inscription that seems to say -- T*m R*ch*rds.",
        "Dorm Hall. The free condom container is empty. A door reads 'Pee Mentor.'",
        "Dining Hall. Did you know that UMass was rated #1, 4 years in a row?",
        "LGRC A104. The charging points here don't work, for some reason.",
    };

    const char* item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3] = {
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
            {"Gilbert Herndon", "Nick Huph.", "-1"},
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
            {"Notebook", "Contains solutions for a CS240 quiz. (Door Key)", "0"},
            {"Homework Solutions", "Homework Solutions - Seems correct, but then again, everything does. (Door Key)", "0"},
            {"Cowboy Hat", "Often dawned by Jared. (Armour)", "5"}
        }
    };

    const char *directions[DIRECTION_COUNT] = {
                "north",
                "south",
                "east",
                "west",
                "up",
                "down"
    };
    
    srand(time(NULL));

    // max health
    int *max_gope = (int *) malloc(sizeof(int));
    *max_gope = INITIAL_GOPE;

    //current health
    int *gope = (int *) malloc(sizeof(int));
    *gope = INITIAL_GOPE;

    //damage dealt by player
    int *damage = (int *) malloc(sizeof(int));
    *damage = INITIAL_DAMAGE;

    // shielding player has
    int *shield = (int *) malloc(sizeof(int));
    *shield = INITIAL_SHIELD;

    //number of different items player can have
    int *backpack_size = (int *) malloc(sizeof(int));
    *backpack_size = DEFAULT_BACKPACK_SIZE;

    //number of different items player has
    int *item_count = (int *) malloc(sizeof(int));
    *item_count = 0;

    // backpack (linked list of items)
    Item *backpack = (Item *) malloc(*backpack_size*sizeof(Item));

    Room *current_room;
    current_room = room_gen(room_descriptions, item_possibilities);

    //used for input parsing
    char *buffer = (char *) malloc(100*sizeof(char));
    char *command = (char *) malloc(10*sizeof(char));
    char *param = (char *) malloc(60*sizeof(char));
    
    do {
        printf(">");

        // get input including spaces
        scanf ("%[^\n]%*c", buffer);
        int *space_index = (int *) malloc(sizeof(int));

        // get index of space
        *space_index = 0;
        while(*space_index < strlen(buffer) && buffer[*space_index] != ' ')
            (*space_index)++;

        // copy everything before space into 'command'
        strncpy(command, buffer, *space_index);
        command[*space_index] = '\0';

        // copy everything after space into 'param'
        strncpy(param, buffer+(*space_index)+1, strlen(buffer)-(*space_index)-1);
        param[strlen(param)] = '\0';
        
        if(strcmp(command, "go") == 0) {
            for(int direction_index=0; direction_index<DIRECTION_COUNT; direction_index++) {
                if(strcmp(directions[direction_index], param) == 0) {
                    //room is i+1 (refer to #defines in room.h)
                }
            }
            
        } else if(strcmp(command, "look") == 0) {
            int *room_state = (int *) malloc(sizeof(int));

            printf("You find yourself in a %s\n\n", current_room->description);

            for(int direction_index=0; direction_index<DIRECTION_COUNT; direction_index++) {
                printf("The %s wall leads to ", directions[direction_index]);
                if((*room_state = check_direction(current_room, direction_index+1)) == ROOM_UNLOCKED) {
                    printf("an unlocked room");
                } else if(*room_state == ROOM_LOCKED) {
                    printf("a locked room");
                } else {
                    printf(" nothing. It's a wall");
                }
            }

            item_print(current_room->items);
            
            free(room_state);
            room_state = NULL;
            
        } else if(strcmp(command, "take") == 0) {
            //temporarily take item from room (might be returned if backpack is full)
            Item *room_item = item_take(param, current_room->items);

            // item is in room
            if(room_item != NULL) {
                Item *backpack_item = item_find(param, backpack);

                if(backpack_item == NULL) {
                    //player doesn't already have item.
                    if(*item_count < *backpack_size) {
                        item_add(backpack, room_item);
                    } else {
                        item_add(current_room->items, room_item);
                    }
                } else {
                    //player has already has item.
                    *(backpack_item->count)++;
                    item_free(room_item);
                    room_item = NULL;
                }

            } else {
                printf("Item '%s' not found", param);
            }

        } else if(strcmp(command, "drop") == 0) {
            Item *temp = item_take(param, backpack);

            if(temp != NULL) {
                item_add(current_room->items, temp);
                (*item_count)--;

            } else {
                printf("Item '%s' not found", param);
            }

        } else if(strcmp(command, "use") == 0) {
            Item *temp = item_find(param, backpack);

            if(temp == NULL) {
                printf("Item not '%s' found", param);
                
            } else {
                if(*(temp->attribute) < 0) {//unusable item
                    printf("You can't really use that item");
                    item_add(backpack, temp);

                } else if(*(temp->attribute) == 0) {//key
                    printf("That's a key. Go to a locked door to use it");

                } else {if(*(temp->attribute) == 1) {//it's a book}
                    (*backpack_size) += *(temp->attribute);
                    printf("You've gotten better at memory management. Backpack size increased by %i", *(temp->attribute));

                } else {
                    int *len = (int *) malloc(sizeof(int));
                    *len = strlen(temp->description);

                    if(temp->description[*len-1] == ')') {
                        if(temp->description[*len-2] =='r') {//Armour

                        } else if(temp->description[*len-2] =='d') {//Shield
                            *shield = *(temp->attribute);
                            printf("Shield equiped. Your shielding is now at %i", *shield);
                            
                        } else if(temp->description[*len-2] =='n') {//Weapon
                            printf("Weapon equiped. Your now deal %i damage", *damage);
                            *damage = *(temp->attribute);

                        } else if(temp->description[*len-2] =='e') {//gope
                            *gope = (*gope+*(temp->attribute))%(*max_gope);
                            printf("You feel nourished. Your gope level is at %i/%i", *gope, *max_gope);

                        }
                    }
                    free(len);
                    len = NULL;
                }
            }

        } else {
            printf("Invalid command (case sensitive)");
        }

    } while(1);

    return 0;
}