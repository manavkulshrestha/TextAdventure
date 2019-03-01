#include <stdlib.h>
#include <string.h>
#include "rooms.h"

Room *room(char *description, Item *items,
                	Room *north, Room *south,
                	Room *east, Room *west,
                    Room *up, Room *down,
				   int state) {
	Room *new_room = (Room *) malloc(sizeof(Room));

	new_room->description = (char *) malloc(strlen(description)*sizeof(char));
	strncpy(new_room->description, description, strlen(description));

	new_room->items = items;
	new_room->north = north;
	new_room->south = south;
	new_room->east = east;
	new_room->west = west;
	new_room->up = up;
	new_room->down = down;

	new_room->state = (int *) malloc(sizeof(int));
	*(new_room->state) = state;

	return new_room;
}

int check_direction(Room *current, int *direction) {
	if(*direction <= 0 || *direction > 6)
		return -1;
	else if(*direction == ROOM_NORTH) 
		if(current->north == NULL)
			return 0;
		else if(current->north->state == ROOM_LOCKED)
			return ROOM_LOCKED;
		else if(current->north->state == ROOM_UNLOCKED)
			return ROOM_UNLOCKED;
	else if(*direction == ROOM_EAST) 
		if(current->south == NULL)
			return 0;
		else if(current->south->state == ROOM_LOCKED)
			return ROOM_LOCKED;
		else if(current->south->state == ROOM_UNLOCKED)
			return ROOM_UNLOCKED;
	else if(*direction == ROOM_EAST) 
		if(current->east == NULL)
			return 0;
		else if(current->east->state == ROOM_LOCKED)
			return ROOM_LOCKED;
		else if(current->east->state == ROOM_UNLOCKED)
			return ROOM_UNLOCKED;
	else if(*direction == ROOM_WEST) 
		if(current->west == NULL)
			return 0;
		else if(current->west->state == ROOM_LOCKED)
			return ROOM_LOCKED;
		else if(current->west->state == ROOM_UNLOCKED)
			return ROOM_UNLOCKED;
	else if(*direction == ROOM_UP) 
		if(current->up == NULL)
			return 0;
		else if(current->up->state == ROOM_LOCKED)
			return ROOM_LOCKED;
		else if(current->up->state == ROOM_UNLOCKED)
			return ROOM_UNLOCKED;
	else if(*direction == ROOM_DOWN) 
		if(current->down == NULL)
			return 0;
		else if(current->down->state == ROOM_LOCKED)
			return ROOM_LOCKED;
		else if(current->down->state == ROOM_UNLOCKED)
			return ROOM_UNLOCKED;
}


void room_connect(Room *current, Room *other, int *direction) {
	if(*direction <= 0 || *direction > 6)
		return;
	else if(*direction == ROOM_NORTH) 
		current->north = other;
		other->south = current;
	else if(*direction == ROOM_EAST) 
		current->south = other;
		other->north = current;
	else if(*direction == ROOM_EAST) 
		current->east = other;
		other->west = current;
	else if(*direction == ROOM_WEST) 
		current->west = other;
		other->east = current;
	else if(*direction == ROOM_UP) 
		current->up = other;
		other->down = current;
	else if(*direction == ROOM_DOWN) 
		current->down = other;
		other->up = current;
}

void set_state(Room *Room, int state) {
	Room->state = state;
}

void change_state(Room *Room, int delta) {
	Room->state += delta;
}

void room_free(Room *room) {
	if(room == NULL)
		return;

	free(room->description);
	room->description = NULL;

	item_free(room->items);
	room->items = NULL;

	room_free(room->north);
	room->north = NULL;

	room_free(room->south);
	room->south = NULL;

	room_free(room->east);
	room->east = NULL;
	
	room_free(room->west);
	room->west = NULL;
	
	room_free(room->up);
	room->up = NULL;
	
	room_free(room->down);
	room->down = NULL;

	free(room->state);
	room->state = NULL;

	free(room);
	room = NULL;
}