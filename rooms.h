#ifndef ROOMS_H_  /* Include guard */
#define ROOMS_H_

#include "items.h"

#define ROOM_NO_ROOM 0
#define ROOM_LOCKED 1
#define ROOM_UNLOCKED 2

#define ROOM_NORTH 0
#define ROOM_SOUTH 1
#define ROOM_EAST 2
#define ROOM_WEST 3
#define ROOM_UP 4
#define ROOM_DOWN 5

#define EXIT_COUNT 6

typedef struct Room {
	char *description;
	struct Item *items;
	struct Room *exits[EXIT_COUNT];
	int *state;
} Room;

Room *room(char *description, Item *items,
                    Room *north,  Room *south,
                	Room *east,  Room *west,
                    Room *up,  Room *down,
				    int state
                    );

int check_direction(Room *current, int direction);
void room_connect(Room *current, Room *other, int direction);
void set_state(Room *room, int *state);
void change_state(Room *room, int delta);
void room_free(Room *room);

#endif // ROOMS_H_