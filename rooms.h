#ifndef ROOMS_H_  /* Include guard */
#define ROOMS_H_

#include "items.h"

#define ROOM_NO_ROOM 0
#define ROOM_LOCKED 1
#define ROOM_UNLOCKED 2
#define ROOM_FINAL 3

#define ROOM_NORTH 0
#define ROOM_SOUTH 1
#define ROOM_EAST 2
#define ROOM_WEST 3
#define ROOM_UP 4
#define ROOM_DOWN 5

#define EXIT_COUNT 6

typedef struct Room {
	char *description; // Description of room
	struct Item *items; // Items stored in room
	struct Room *exits[EXIT_COUNT]; // Stores the exits in room
	int *state; // Current state of room
} Room;


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
                    Room *north,  Room *south,
                	Room *east,  Room *west,
                    Room *up,  Room *down,
				    int state
                    );


/*
	Used to check the state of a room connected to the current room

	Parameters:
		current: current room
		direction: desired direction of connection to check

	Returns:
		-1 if current or direction are null OR if direction is not valid
		state of specified room otherwise
*/
int check_direction(Room *current, int direction);



/*
	Connect two rooms together that weren't previously connected

	Parameters:
		current: current room
		other: room to connect to current room
		direction: direction to connect them in
	
	Returns void
*/
void room_connect(Room *current, Room *other, int direction);



/*
	Set the state of a room

	Parameters:
		room: room to change the state of
		state: desired state (NOTE: this is an int*. This fits better with our usage)

	Returns void
*/
void set_state(Room *room, int *state);



/*
	Change the state of a room by a specified integer amount

	Parameters:
		room: room to change the state of
		delta: change  (NOTE: this is an int)

	Returns void
*/
void change_state(Room *room, int delta);

/*
	Recursively a room and all its connected rooms (we only call this at the end of the program)

	Parameter: room: room to be freed

	Returns void
*/
void room_free(Room *room);

#endif // ROOMS_H_