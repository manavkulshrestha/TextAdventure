#ifndef ITEMS_H_  /* Include guard */
#define ITEMS_H_

typedef struct Item {
	char *name;
	char *description;
	int *count;
	struct Item *next;
} Item;

Item *item(char *name, char* description, int *count, Item *next);
char *item_name(Item *item);
char *item_description(Item *item);
Item *item_next(Item *item);
Item *item_take(char *name, Item *head_ptr);
void *item_add(Item *items, Item *to_add);
void item_print(Item *head_ptr);
void item_free(Item *item);

#endif // ITEMS_H_