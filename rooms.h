#ifndef ROOMS_H_  /* Include guard */
#define ROOMS_H_

#include "items.h"

typedef struct Room {
	char *description;
	struct Item *items;
	struct Room *north;	
	struct Room *south;	
	struct Room *east;	
	struct Room *west;	
	struct Room *up;	
	struct Room *down;
	int *state;
} Room;

typedef struct Coords {
	int *x;
    int *y;
    int *z;
} Room;

Room *room(char *description, Item *items,
                    Room *north,  Room *south,
                	Room *east,  Room *west,
                    Room *up,  Room *down,
				    int *state
                    );
Coords *coords(int *x, int *y, int *z);

void room_exit_north(Room *current, Room *other);
void room_exit_south(Room *current, Room *other);
void room_exit_east(Room *current, Room *other);
void room_exit_west(Room *current, Room *other);
void room_exit_up(Room *current, Room *other);
void room_exit_down(Room *current, Room *other);
void set_state(Room *room, int *state);
void change_state(Room *room, int delta);
void room_free(Room *room);

#endif // ROOMS_H_