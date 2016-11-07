#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compile with: gcc -g -std=iso9899:199x autocorrect.c -o testfile


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


/////////////////////////
// Linked Declarations //
/////////////////////////

typedef struct linked* linked_t;

struct linked {
	struct linked_node* head;
};

struct linked_node {
	trie_t item;
	struct linked_node* next;
	char iterativeBuild[];
};

linked_t linked_create(); // creates linked list -- returns pointer to a struct linked, allocates space for the head
void linked_destroy(linked_t s); // destroys linkedlist
void linked_append(linked_t s, trie_t item, char* iterativeBuild); // adds node to end of linked
trie_t linked_pop(linked_t s); // returns first item in the linked and removes it
trie_t linked_peek(linked_t s);


//////////////////////////////
// Autocorrect Declarations //
//////////////////////////////

void complete(trie_t triePointer, char* wordGiven);
void correct(trie_t triePointer, char* wordGiven);
trie_t follow_word(trie_t triePointer, char* wordGiven);


//////////
// Main //
//////////

void main() {
	trie_t testTrie = create_trie();
	trie_fill(testTrie);
	char* testWord = "coo";
	complete(testTrie, testWord);

}


///////////////////////////
// Autocorrect Functions //
///////////////////////////


void complete(trie_t triePointer, char* wordGiven) {
	trie_t starterNode = follow_word(triePointer, wordGiven);
	if (starterNode != NULL) {
		linked_t stack = linked_create();
		int i = 0;
		for (i; i < sizeof(starterNode->next)/sizeof(starterNode->next[0]); i++) {
			if (starterNode->next[i]->character =! NULL) {
				trie_t new_node = starterNode->next[i];
				linked_append(stack, new_node, &(new_node->character));
			}
		}
		while (linked_peek(stack) != NULL) {
			char* wordSaver = stack->head->iterativeBuild;
			trie_t nodeSaver = linked_pop(stack); 
			if (nodeSaver->frequency >= 1) {
				printf("%s\n", wordSaver);
			}
			for (i; i < sizeof(nodeSaver->next)/sizeof(nodeSaver->next[0]); i++) {
				if (nodeSaver->next[i]->character =! NULL) {
					trie_t new_node = nodeSaver->next[i];
					char buildingLetters[strlen(wordSaver) + 1];
					int p = 0;
					for (p; p < strlen(wordSaver); p++) {
						buildingLetters[p] = wordSaver[p];
					}
					buildingLetters[p+1] = nodeSaver->next[i]->character;
					linked_append(stack, new_node, buildingLetters);
				}
			}
		}
		linked_destroy(stack);
	}
}


trie_t follow_word(trie_t triePointer, char* wordGiven) {
	int h = 0;
	for (h; h < strlen(wordGiven); h++) {
		char c = wordGiven[h];
		int i = (int) c - 97;
		if (triePointer->next[i]->character =! NULL) {
			triePointer = triePointer->next[i];
		} else {
			return NULL;
		}
	}
	int i = 0;
	for (i; i < sizeof(triePointer->next)/sizeof(triePointer->next[0]); i++) {
		if (triePointer->next[i]->character =! NULL) {
			return triePointer;
		}
	}
	return NULL; // Returns null if there are no nodes following last node
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
	}
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


//////////////////////
// Linked Functions //
//////////////////////

linked_t linked_create() {
	linked_t newLinked = malloc(sizeof(struct linked)); // newLinked is a pointer to memory that is the size of a linked
	newLinked->head = NULL; // follow the pointer and make the head of the linked NULL
	return newLinked; // return the pointer to the linked
}


void linked_destroy(linked_t s) {
	struct linked_node* curr = s->head;
	while(curr != NULL) {
		struct linked_node* temp = curr->next;
		free(curr); // Item does not need to get freed
		curr = temp;
	}
	free(s);
	(s) = NULL;
}


void linked_append(linked_t s, trie_t item, char* iterativeBuild) {
	struct linked_node* new_node = malloc(sizeof(struct linked_node) + (sizeof(char) * strlen(iterativeBuild)));
	new_node->item = item;
	int h = 0;
	for (h; h < strlen(iterativeBuild); h++) {
		new_node->iterativeBuild[h] = iterativeBuild[h];
	}
	new_node->next = NULL;
	struct linked_node* curr = s->head;
	while(curr != NULL) {
		curr = curr->next;
	}
	curr = new_node;
}


trie_t linked_pop(linked_t s) {
	if (s->head != NULL) {
		trie_t item = s->head->item;
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


trie_t linked_peek(linked_t s) {
	if (s->head != NULL) {
		return s->head->item;
	} else {
		return NULL;
	}
}

