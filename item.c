struct Item {
	char name[20];
	char description[100];
	struct Item *next;
};
struct Item *item(char* name, char* description, struct Item *next) {
	struct Item *item = (struct Item *) malloc(sizeof(struct Item));
	strncpy(item->name, name, strlen(name));
	strncpy(item->description, description, strlen(description));
	item->next = next;
	return item;
}
void test_func(struct Item *head_ptr) {
	head_ptr = head_ptr->next;
}
char *item_name(struct Item *item) {
	return item->name;
}
char *item_description(struct Item *item) {
	return item->description;
}
struct Item *item_next(struct Item *item) {
	return item->next;
}
struct Item* item_take(char *name, struct Item *head_ptr) {
	if(head_ptr == NULL)
		return NULL;
	struct Item *prev_ptr = (struct Item *) malloc(sizeof(struct Item));
	struct Item *iter_ptr = (struct Item *) malloc(sizeof(struct Item));
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
void item_print(struct Item *head_ptr) {
	struct Item *current_ptr = head_ptr;
	printf("Items:");
	if(head_ptr == NULL)
		printf(" [empty]");
	while(current_ptr != NULL) {
		printf("\nItem name: %s, Item description: %s", current_ptr->name, current_ptr->description);
	 	current_ptr = current_ptr->next;
	}
	printf("\n\n");
}

