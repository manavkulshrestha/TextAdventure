#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rooms.h"

/*
	Constructor for Room struct

	Parameters:
		description: description of room
		items: items stored in room
		[direction]: what rooms to connect to
		state: integer specifying state (NOTE: state in the struct is an int*, while the passed in value is an int)

	Returns the constructed room
*/
Room *room(char *description, Item *items,
                	Room *north, Room *south,
                	Room *east, Room *west,
                    Room *up, Room *down,
				   	int state) {
	Room *new_room = (Room *) malloc(sizeof(Room)); // Create new room

	int *len = (int *) malloc(sizeof(int)); // Temp variable for the length of the passed in description
	*len = strlen(description);
	new_room->description = (char *) malloc((*len+1)*sizeof(char)); // Assignment (+1 is to account for the null character, since strcpy doesn't include it)
	strncpy(new_room->description, description, *len);
	new_room->description[*len] = '\0'; // Account for the Null character

	free(len); // Free that boy
	len = NULL;

	/* Assign the other room atributes */
	new_room->items = items;
	new_room->exits[ROOM_NORTH] = north;
	new_room->exits[ROOM_SOUTH] = south;
	new_room->exits[ROOM_EAST] = east;
	new_room->exits[ROOM_WEST] = west;
	new_room->exits[ROOM_UP] = up;
	new_room->exits[ROOM_DOWN] = down;

	new_room->state = (int *) malloc(sizeof(int));
	*(new_room->state) = state;

	return new_room; 
}



/*
	Used to check the state of a room connected to the current room

	Parameters:
		current: current room
		direction: desired direction of connection to check

	Returns:
		-1 if current or direction are null OR if direction is not valid
		state of specified room otherwise
*/
int check_direction(Room *current, int direction) {
	if(direction < ROOM_NORTH || direction > ROOM_DOWN || current == NULL)
		return -1;
	if(current->exits[direction] == NULL)
		return ROOM_NO_ROOM;
	return *(current->exits[direction]->state);
}



/*
	Connect two rooms together that weren't previously connected

	Parameters:
		current: current room
		other: room to connect to current room
		direction: direction to connect them in
	
	Returns void
*/
void room_connect(Room *current, Room *other, int direction) {
	if(direction < ROOM_NORTH || direction > ROOM_DOWN || current == NULL || other == NULL)
		return;
	int *counter_part = (int *) malloc(sizeof(int));
	*counter_part = direction + ((direction%2 == 0) ? 1 : -1);
	
	current->exits[direction] = other;
	other->exits[*counter_part] = current;

	free(counter_part);
	counter_part = NULL;
}



/*
	Set the state of a room

	Parameters:
		room: room to change the state of
		state: desired state (NOTE: this is an int*. This fits better with our usage)

	Returns void
*/
void set_state(Room *room, int *state) {
	room->state = state;
}



/*
	Change the state of a room by a specified integer amount

	Parameters:
		room: room to change the state of
		delta: change  (NOTE: this is an int)

	Returns void
*/
void change_state(Room *room, int delta) {
	room->state += delta;
}


/*
	Recursively a room and all its connected rooms (we only call this at the end of the program)

	Parameter: room: room to be freed

	Returns void
*/
void room_free(Room *room) {
	if(room == NULL)
		return;

	// Flag the room as being currently free
	// Avoid segmentation fault in recursive calls trying to free this room again
	*(room->state) = -1;

	free(room->description);
	room->description = NULL;

	item_free(room->items);
	room->items = NULL;

	for(int i=0; i<EXIT_COUNT; i++) {
		// Check if room exists and is not already being freed
		if(room->exits[i] != NULL && *(room->exits[i]->state) != -1) {
			room_free(room->exits[i]);
			room->exits[i] = NULL;
		}
	}

	free(room->state);
	room->state = NULL;

	free(room);
	room = NULL;
}