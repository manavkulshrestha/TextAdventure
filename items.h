#ifndef ITEMS_H_
#define ITEMS_H_


typedef struct Item {
	char *name;
	char *description;
	int *count;
	int *attribute;
	struct Item *next;
} Item;

/*
	CONSTRUCTOR

	Constructs an item given the parameters.

	Parameters:
		char *name - string denoting the name of the item
		char *name - string denoting the description for the item
		int count - number of items grouped together
		Item *next - link for the next item

	Returns:
		Item *item - dynamically allocated item with all attributes also dynamically allocated given the parameters
*/
Item *item(char *name, char* description, int count, int attribute, Item *next);


/*
	Find the first item within the Linked List with the name specified, removes it, and returns it

	Parameters:
		char *name - string representing the name of the item to take
		Item *head_ptr - Item representing the "head" of the Linked List

	Returns:
		NULL - didn't find item or head was NULL
		Item *item - Item with name specified
*/
Item *item_take(char *name, Item *head_ptr);



/*
	Find the first item within the Linked List with the name specified, removes it, and returns it

	Parameters:
		char *name - string representing the name of the item to take
		Item *head_ptr - Item representing the "head" of the Linked List

	Returns:
		NULL - didn't find item or head was NULL
		Item *item - Item with name specified
*/
Item *item_find(char *name, Item *head_ptr);



/*
	Adds item to given linked list of items

	Parameters:
		items: existing list of items
		to_add: item to add
	
	Returns void
*/
void item_add(Item *items, Item *to_add);



/*
	Prints the contents of a given linked list of items

	Parameter: head_ptr: head of linked list to print

	Returns void
*/
void item_print(Item *head_ptr);



/*
	Frees given list of items. Used in room_free

	Parameter: items: list of items to free

	Returns void
*/
void item_free(Item *item);

#endif