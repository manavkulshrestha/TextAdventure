#include <stdlib.h>
#include <string.h>
#include "rooms.h"

Room *room(char *description, Item *items,
                	Room *north, Room *south,
                	Room *east, Room *west,
                    Room *up, Room *down,
				   	int state) {
	Room *new_room = (Room *) malloc(sizeof(Room));

	int *len = (int *) malloc(sizeof(int));
	*len = strlen(description);
	new_room->description = (char *) malloc((*len+1)*sizeof(char));
	strncpy(new_room->description, description, *len);
	new_room->description[*len] = '\0';

	free(len);
	len = NULL;

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

int check_direction(Room *current, int direction) {
	if(direction < ROOM_NORTH || direction > ROOM_DOWN || current == NULL)
		return -1;
	if(current->exits[direction] == NULL)
		return ROOM_NO_ROOM;
	return *(current->exits[direction]->state);
}

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

void set_state(Room *room, int *state) {
	room->state = state;
}

void change_state(Room *room, int delta) {
	room->state += delta;
}

void room_free(Room *room) {
	if(room == NULL)
		return;

	free(room->description);
	room->description = NULL;

	item_free(room->items);
	room->items = NULL;

	for(int i=0; i<EXIT_COUNT; i++) {
		room_free(room->exits[i]);
		room->exits[i] = NULL;
	}

	free(room->state);
	room->state = NULL;

	free(room);
	room = NULL;
}