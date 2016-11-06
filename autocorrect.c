#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////
// Trie Declarations //
///////////////////////

typedef struct trie_node* trie_t;

struct trie_node {
	char character;
	int frequency;
	trie_t next[26];
};

trie_t create_trie();
void trie_fill(trie_t triePointer);
void insert_trie(trie_t triePointer, char* word);
void delete_trie(trie_t triePointer);

trie_t follow_word(trie_t triePointer, char* wordGiven);


////////////////////////
// Stack Declarations //
////////////////////////

typedef struct linked* linked_t;

struct linked {
	struct linked_node* head;
};

struct linked_node {
	trie_t item;
	struct linked_node* next;
};

linked_t linked_create(); // creates linked list -- returns pointer to a struct linked, allocates space for the head
void linked_destroy(linked_t s); // destroys linkedlist
void linked_append(linked_t s, trie_t item); // adds node to end of linked
void* linked_pop(linked_t s); // returns first item in the linked and removes it


//////////
// Main //
//////////

main() {
	trie_t testTrie = create_trie();
	trie_fill(testTrie);
	delete_trie(testTrie);
}


////////////////////
// Trie Functions //
////////////////////

trie_t create_trie() {
	trie_t newTrie = malloc(sizeof(struct trie_node));
	newTrie->character = '\0';
	newTrie->frequency = 0;
	int i = 0;
	for (i; i < sizeof(newTrie->next)/sizeof(newTrie->next[0]); i++) {
		newTrie->next[i] = NULL;
	}
	return newTrie;
}


void trie_fill(trie_t triePointer) {
	FILE* pFile = fopen("wordsEn.txt", "r");
	char line[256];
	while(fgets(line, sizeof(line), pFile)){
  		char* wordRead = strtok(line, "\n");
  		printf("%s\n", wordRead);
  		insert_trie(triePointer, wordRead);
  	}
}


void insert_trie(trie_t triePointer, char* word) {
	int h = 0;
	for (h; h < strlen(word); h++) {
		char c = word[h];
		int i = (int) c - 97;
		if (triePointer->next[i] == NULL) {
			triePointer->next[i] = malloc(sizeof(struct trie_node));
			triePointer->next[i]->character = word[h];
			if (word[h+1] == '\0') {
				triePointer->next[i]->frequency = 1;
			} else {
				triePointer->next[i]->frequency = 0;
			}
			int s = 0;
			for (s; s < sizeof(triePointer->next[i]->next)/sizeof(triePointer->next[i]->next[0]); s++) {
				triePointer->next[i]->next[s] = NULL;
			}
		} else {
			if (word[h+1] == '\0') {
				triePointer->frequency = 1;
			}
		}
		triePointer = triePointer->next[i];
		printf("%c", triePointer->character);
	}
	printf("\n");
}


void delete_trie(trie_t triePointer) {
	int i = 0;
	for (i; i < sizeof(triePointer->next)/sizeof(triePointer->next[0]); i++) {
		if (triePointer->next[i] != NULL) {
			delete_trie(triePointer->next[i]);
		}
	}
	free(triePointer);
}


trie_t follow_word(trie_t triePointer, char* wordGiven) {
	int h = 0;
	for (h; h < strlen(wordGiven); h++) {
		char c = wordGiven[h];
		int i = (int) c - 97;
		if (triePointer->next[i] == NULL) {
			return NULL;
		} else {
			triePointer = triePointer->next[i];
		}
	}
	return triePointer;
}


//////////////////////
// Linked Functions //
//////////////////////

linked_t linked_create() {
	struct linked newLinked = malloc(sizeof(struct linked)); // newLinked is a pointer to memory that is the size of a linked
	newLinked->head = NULL; // follow the pointer and make the head of the linked NULL
	return newLinked; // return the pointer to the linked
}


void linked_destroy(linked_t s) {
	struct linked_node* curr = s->head;
	while(curr != NULL) {
		struct linked_node* temp = curr->next;
		free(curr);
		free(curr->item);
		curr = temp;
	}
	free(s);
	(s) = NULL;
}


void linked_append(linked_t s, trie_t item) {
	struct linked_node* new_node = malloc(sizeof(struct linked_node));
	new_node->item = item;
	new_node->next = NULL;
	struct linked_node* curr = s->head;
	while(curr != NULL) {
		curr = curr->next;
	}
	curr = new;
}


void* linked_pop(linked_t s) {
	if (s->head != NULL) {
		trie_t* item = s->head->item;
		free(s->head);
		if (s->head->next != NULL){
			struct linked_node* new_head = s->head->next;
			s->head = new_head;
		} else {
			s->head = NULL;
		}
		return item;
	} else {
		return NULL;
	}
}