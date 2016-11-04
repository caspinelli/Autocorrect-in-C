#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct trie_node* trie_t;
typedef struct queue_node* priority_t;

struct trie_node {
	char character;
	int frequency;
	trie_t next[26];
};

trie_t create_trie();
void trie_fill(trie_t triePointer);
void insert_trie(trie_t triePointer, char* word);
void delete_trie(trie_t triePointer);

main() {
	trie_t testTrie = create_trie();
	trie_fill(testTrie);
	//insert_trie(testTrie, "cooper");
	delete_trie(testTrie);
}


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


void insert_trie(trie_t holder, char* word) {
	int h = 0;
	for (h; h < sizeof(word)/sizeof(word[0]); h++) {
		char c = word[h];
		int i = (int) c - 97;
		if (holder->next[i] == NULL) {
			holder->next[i] = malloc(sizeof(struct trie_node));
			holder->next[i]->character = word[h];
			if (word[h+1] == '\0') {
				holder->next[i]->frequency = 1;
			} else {
				holder->next[i]->frequency = 0;
			}
			int s = 0;
			for (s; s < sizeof(holder->next[i]->next)/sizeof(holder->next[i]->next[0]); s++) {
				holder->next[i]->next[s] = NULL;
			}
		} else {
			if (word[h+1] == '\0') {
				holder->frequency = 1;
			}
		}
		holder = holder->next[i];
		printf("%c", holder->character);
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


