/*
void complete(trie_t triePointer, char* wordGiven) {
	trie_t starterNode = follow_word(triePointer, wordGiven);
	if (starterNode != NULL) {
		linked_t stack = linked_create();
		int i = 0;
		char starterLetters[strlen(wordGiven) + 1];
		int q = 0;
		for (q; q < strlen(wordGiven); q++) {
			starterLetters[q] = wordGiven[q];
		}
		starterLetters[q] = '\0';
		linked_append(stack, starterNode, starterLetters, NULL);
		while (linked_peek(stack) != NULL) {
			int length = strlen(stack->head->iterativeBuild);
			char wordSaver[length + 1];
			int r = 0;
			for (r; r < length; r++) {
				wordSaver[r] = stack->head->iterativeBuild[r];
			}
			wordSaver[r] = '\0';
			trie_t nodeSaver = linked_pop(stack); 
			if (nodeSaver->frequency >= 1) {
				int c = 0;
				for (c; c < strlen(wordSaver); c++) {
					printf("%c", wordSaver[c]);
				}
				printf("\n");
			}
			int g = 0;
			for (g; g < sizeof(nodeSaver->next)/sizeof(nodeSaver->next[0]); g++) {
				if (nodeSaver->next[g] != NULL) {
					trie_t new_node = nodeSaver->next[g];
					char buildingLetters[strlen(wordSaver) + 2];
					int p = 0;
					for (p; p < strlen(wordSaver); p++) {
						buildingLetters[p] = wordSaver[p];
					}
					buildingLetters[p] = nodeSaver->next[g]->character;
					buildingLetters[p+1] = '\0';
					linked_append(stack, new_node, buildingLetters, NULL);
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
		if (triePointer->next[i] != NULL) {
			triePointer = triePointer->next[i];
		} else {
			return NULL;
		}
	}
	int i = 0;
	for (i; i < sizeof(triePointer->next)/sizeof(triePointer->next[0]); i++) {
		if (triePointer->next[i] != NULL) {
			return triePointer;
		}
	}
	return NULL; // Returns null if there are no nodes following last node
}
*/