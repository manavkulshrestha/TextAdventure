#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "items.h"

Item *item(char* name, char* description, int count, int attribute, Item *next) {
	Item *item = (Item *) malloc(sizeof(Item));

	item->name = (char *) malloc(strlen(name)*sizeof(char));
	strncpy(item->name, name, strlen(name));

	item->description = (char *) malloc(strlen(description)*sizeof(char));
	strncpy(item->description, description, strlen(description));

	item->count = (int *) malloc(sizeof(int));
	*(item->count) = count;

	item->attribute = (int *) malloc(sizeof(int));
	*(item->attribute) = attribute;

	item->next = next;
	return item;
}

char *item_name(Item *item) {
	return item->name;
}

char *item_description(Item *item) {
	return item->description;
}

Item *item_next(Item *item) {
	return item->next;
}

Item *item_take(char *name, Item *head_ptr) {
	if(head_ptr == NULL)
		return NULL;
	Item *prev_ptr = (Item *) malloc(sizeof(Item));
	Item *iter_ptr = (Item *) malloc(sizeof(Item));
	prev_ptr = head_ptr;
	iter_ptr = head_ptr->next;
	
	while(iter_ptr != NULL) {
		if(strcmp(name, iter_ptr->name) == 0) {
			prev_ptr->next = iter_ptr->next;
			iter_ptr->next = NULL;
			prev_ptr = NULL;
			return iter_ptr;
		}
		iter_ptr = iter_ptr->next;
		prev_ptr = prev_ptr->next;
	}
	prev_ptr = NULL;
	free(prev_ptr);
	iter_ptr = NULL;
	free(iter_ptr);
	return NULL;
}

int *item_add(Item *items, Item *to_add) {
	if(items == NULL)
		return 0;//should at least have a dummy head

	to_add->next = items->next;
	items->next = to_add;
}

void item_print(Item *head_ptr) {
	if(head_ptr == NULL)
		return;

	head_ptr = head_ptr->next;

	printf("Items:");
	if(head_ptr == NULL) {
		printf(" [empty]");
		return;
	}

	while(head_ptr != NULL) {
		printf("\nItem name: %s, Item description: %s", head_ptr->name, head_ptr->description);
	 	head_ptr = head_ptr->next;
	}
	printf("\n\n");
}

void item_free(Item *item) {
	if(item == NULL)
		return;

	free(item->name);
	item->name = NULL;

	free(item->description);
	item->description = NULL;

	free(item->count);
	item->count = NULL;

	item_free(item->next);
	item->next = NULL;

	free(item);
	item = NULL;
}
