#include <stdlib.h>
#include <string.h>
#include "rooms.h"

Room *room(char *description, Item *items,
                	Room *north, Room *south,
                	Room *east, Room *west,
                    Room *up, Room *down,
				   int *state) {
	Room *new_Room = (Room *) malloc(sizeof(Room));

	new_Room->description = (char *) malloc(strlen(description)*sizeof(char));
	strncpy(new_Room->description, description, strlen(description));

	new_Room->items = items;
	new_Room->north = north;
	new_Room->south = south;
	new_Room->east = east;
	new_Room->west = west;
	new_Room->up = up;
	new_Room->down = down;

	new_Room->state = (int *) malloc(sizeof(int));
	new_Room->state = state;

	return new_Room;
}

Coords *coords(int *x, int *y, int *z) {
	Coords *new_coords = (Coords *) malloc(sizeOf(Coords));
	
	new_coords->x = x;
	new_coords->y = y;
	new_coords->z = z;

	return new_coords;
}

void Room_exit_north(Room *current, Room *other) {
	current->north = other;
}

void Room_exit_south(Room *current, Room *other) {
	current->south = other;
}

void Room_exit_east(Room *current, Room *other) {
	current->east = other;
}

void Room_exit_west(Room *current, Room *other) {
	current->west = other;
}

void Room_exit_up(Room *current, Room *other) {
	current->up = other;
}

void Room_exit_down(Room *current, Room *other) {
	current->down = other;
}

void set_state(Room *Room, int *state) {
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