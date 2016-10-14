#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct trie_node *trie_t;

struct trie_node {
	char character;
	int frequency;
	trie_t next[26];
};


trie_t create_trie();
void insert_trie(trie_t* triePointer, char* word);

main() {
	create_trie();
}


trie_t create_trie() {
	trie_t newTrie = malloc(sizeof(struct trie_node));
	newTrie->character = '\0';
	newTrie->frequency = 0;
	int i = 0;
	for (i; i < sizeof(newTrie->next)/sizeof(newTrie->next[0]); i++) {
		printf("%i", i);
	}
	return newTrie;
}














void insert_trie(trie_t* triePointer, char* word) {




}



/* struct stack: internal structure hidden by opaque pointer in .h file -
	provides access to the head (starting point) 
struct stack {
	struct stack_node* head;
};

 prepare internal data for insertion/usage 
stack_t stack_create() {
	stack_t newStack = malloc(sizeof(struct stack));
	newStack->head = NULL;
	return newStack;
}

 free any remaining nodes along with all necessary metadata (items are NOT freed, only
	pointers to them are abandoned - it is up to the user of this structure to call free() on
	the values added 
void stack_destroy(stack_t* s) {
	struct stack_node* curr = (*s)->head;
	while(curr != NULL) {
		struct stack_node* temp = curr->next;
		free(curr);
		curr = temp;
	}
	free((*s)->head);
	free(*s);
	(*s) = NULL;
}


Adds a new element to the stack, which becomes the new head of the stack

void stack_push(stack_t* s, void* item) {
	/* if there are no elements yet, must create head nnode
	if ((*s)->head == NULL) {
		(*s)->head = malloc(sizeof(struct stack_node));
		(*s)->head->item = item;
		(*s)->head->next = NULL;
	} else {
		struct stack_node* new_head = malloc(sizeof(struct stack_node));
		new_head->item = item;
		new_head->next = (*s)->head;
		(*s)->head = new_head;
	}
}

Get the top element without removing it.
returns NULL if no such value is allowed (stack is empty)

void* stack_peek(const stack_t s) {
	if (s->head != NULL) {
	return s->head->item;
	} else {
		return NULL;
	}
}


Get the top element without removing it.
returns NULL if no such value is found (stack is empty)

void* stack_pop(stack_t *s) {
	/* check if both a head and a next pointer are available to allow simple
		pop of the current head off the stack linked list
	if ((*s)->head != NULL && (*s)->head->next != NULL) {
		struct stack_node* new_head = (*s)->head->next;
		void* item = (*s)->head->item;
		free((*s)->head);
		(*s)->head = new_head;
		return item;
	} else {
		return item if there is only a head (then free/nullify said head) - otherwise return nothing
		if ((*s)->head != NULL) {
			void* item = (*s)->head->item;
			free((*s)->head);
			(*s)->head = NULL;
			return item;
		} else {
			return NULL;
		}
	}
}
*/