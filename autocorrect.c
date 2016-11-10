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
	int* correctMatrix;
	char iterativeBuild[];
};

linked_t linked_create();
void linked_destroy(linked_t s);
void linked_append(linked_t s, trie_t item, char iterativeBuild[], int* optionalMatrix);
trie_t linked_pop(linked_t s);
struct linked_node* linked_peek(linked_t s);

/////////////////////////////
// Autocorrect Declaration //
/////////////////////////////

int numberMin(int one, int two, int three);
int arrayMin(int* arrayToCheck, int size);
void correctcomplete(trie_t triePointer, char* wordGiven, int maxEdit);

//////////
// Main //
//////////

void main() {
	trie_t testTrie = create_trie();
	trie_fill(testTrie);
	char* testWord = "coop";
	correctcomplete(testTrie, testWord, 3);
	delete_trie(testTrie);
}

///////////////////////////
// Autocorrect Functions //
///////////////////////////

int numberMin(int one, int two, int three) {
	if (one <= two && one <= three) {
		return one;
	} else if (two <= one && two <= three) {
		return two;
	} else {
		return three;
	}
}

int arrayMin(int* arrayToCheck, int size) {
	int min = arrayToCheck[0];
	for (int w = 1; w < size; w++) {
		if (arrayToCheck[w] < min) {
			min = arrayToCheck[w];
		}
	}
	return min;
}

void correctcomplete(trie_t triePointer, char* wordGiven, int maxEdit) {
	linked_t bfsLinked = linked_create();
	int givenLength = strlen(wordGiven) + 1;
	int* startingMatrix = malloc(sizeof(int) * givenLength);
	for (int i = 0; i < givenLength; i++) {
		startingMatrix[i] = i;
	}
	char startNull[1] = "\0";
	linked_append(bfsLinked, triePointer, startNull, startingMatrix);
	while (linked_peek(bfsLinked) != NULL) {
		int* fetchedMatrix = bfsLinked->head->correctMatrix;
		int length = strlen(bfsLinked->head->iterativeBuild);
		char wordSaver[length + 1];
		int r = 0;
		for (r; r < length; r++) {
			wordSaver[r] = bfsLinked->head->iterativeBuild[r];
		}
		wordSaver[r] = '\0';
		trie_t nodeSaver = linked_pop(bfsLinked);
		for (int g = 0; g < sizeof(nodeSaver->next)/sizeof(nodeSaver->next[0]); g++) {
			if (nodeSaver->next[g] != NULL) {
				trie_t new_node = nodeSaver->next[g];
				char buildingLetters[strlen(wordSaver) + 2];
				int p = 0;
				for (p; p < strlen(wordSaver); p++) {
					buildingLetters[p] = wordSaver[p];
				}
				buildingLetters[p] = nodeSaver->next[g]->character;
				buildingLetters[p+1] = '\0';
				//New Matrix Building
				if (fetchedMatrix == NULL) {
					// Check whether to print
					if (new_node->frequency > 0) {
						for (int x = 0; x < strlen(buildingLetters); x++) {
							printf("%c", buildingLetters[x]);
						}
						printf("\n");
					}
					linked_append(bfsLinked, new_node, buildingLetters, NULL);
				} else {
					// Make matrix
					int* newMatrix = malloc(sizeof(int) * givenLength);
					newMatrix[0] = strlen(buildingLetters);
					int buildingLength = strlen(buildingLetters);
					for (int b = 0; b < givenLength - 1; b++) {
						int cost;
						if (buildingLetters[buildingLength - 1] == wordGiven[b] || (buildingLength > 1 && buildingLetters[buildingLength - 1] == wordGiven[b - 1] && buildingLetters[buildingLength - 2] == wordGiven[b])) {
							cost = 0;
						} else {
							cost = 1;
						}
						newMatrix[b+1] = numberMin(fetchedMatrix[b+1] + 1, newMatrix[b] + 1, fetchedMatrix[b] + cost);
					}
					// Check whether to print
					if (newMatrix[givenLength - 1] <= maxEdit && new_node->frequency > 0) {
						for (int x = 0; x < strlen(buildingLetters); x++) {
							printf("%c", buildingLetters[x]);
						}
						printf("\n");
					}
					// Check whether to initiate complete
					if (newMatrix[givenLength - 1] == 0) {
						free(newMatrix);
						linked_append(bfsLinked, new_node, buildingLetters, NULL);
					} else if (arrayMin(newMatrix, givenLength) <= maxEdit) { // Check whether to add back the linked
						linked_append(bfsLinked, new_node, buildingLetters, newMatrix);
					} else {
						free(newMatrix);
					}
				}

			}
		}
	}
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
  	fclose(pFile);
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
	for (i; i < sizeof(triePointer->next)/(sizeof(triePointer->next[0])); i++) {
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
		free(curr);
		curr = temp;
	}
	free(s);
	(s) = NULL;
}

void linked_append(linked_t s, trie_t item, char iterativeBuild[], int* optionalMatrix) {
	struct linked_node* new_node = malloc(sizeof(struct linked_node) + (sizeof(char) * (strlen(iterativeBuild) + 1)));
	new_node->item = item;
	new_node->correctMatrix = optionalMatrix;
	int h = 0;
	for (h; h < strlen(iterativeBuild) + 1; h++) {
		new_node->iterativeBuild[h] = iterativeBuild[h];
	}
	new_node->next = NULL;
	if (s->head == NULL) {
		s->head = new_node;
	} else {
		struct linked_node* curr = s->head; 
		while(curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = new_node;
	}
}

trie_t linked_pop(linked_t s) {
	if (s->head != NULL) {
		trie_t item = s->head->item;
		struct linked_node* toBeFreed = s->head;
		if (s->head->next != NULL){
			struct linked_node* new_head = s->head->next;
			s->head = new_head;
		} else {
			s->head = NULL;
		}
		free(toBeFreed);
		return item;
	} else {
		return NULL;
	}
}

struct linked_node* linked_peek(linked_t s) {
	if (s->head != NULL) {
		return s->head;
	} else {
		return NULL;
	}
}
