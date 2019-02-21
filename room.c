struct Room {
	char description[100];
	struct Item *items;
	struct Room *north;	
	struct Room *south;	
	struct Room *east;	
	struct Room *west;	
	struct Room *up;	
	struct Room *down;	
};
struct Room *room(char *description, struct Item *items,
                   struct Room *north, struct Room *south,
                   struct Room *east, struct Room *west,
                   struct Room *up, struct Room *down) {
	struct Room *new_room = (struct Room *) malloc(sizeof(struct Room));
	strncpy(new_room->description, description, strlen(description));
	new_room->items = items;
	new_room->north = north;
	new_room->south = south;
	new_room->east = east;
	new_room->west = west;
	new_room->up = up;
	new_room->down = down;
	return new_room;
}
void room_exit_north(struct Room *current, struct Room *other) {
	current->north = other;
}
void room_exit_south(struct Room *current, struct Room *other) {
	current->south = other;
}
void room_exit_east(struct Room *current, struct Room *other) {
	current->east = other;
}
void room_exit_west(struct Room *current, struct Room *other) {
	current->west = other;
}
void room_exit_up(struct Room *current, struct Room *other) {
	current->up = other;
}
void room_exit_down(struct Room *current, struct Room *other) {
	current->down = other;
}

