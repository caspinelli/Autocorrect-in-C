#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* queue_init: initializes pointer of queue->head to null and size to 0 to start up queue */
void queue_init(queue_t* queue)
{
	queue->head = NULL;
	queue->size = 0;
	return;
}

/* queue_destroy: frees all memory presently occupied by queue */
void queue_destroy(queue_t* queue)
{
	queue_item_t* node = queue->head;
	free(queue);
	while (node != NULL) {
		queue_item_t* ptr = node->next;
		free(node->suggestion);
		free(node);
		node = ptr;
	}
	return;
}

/* queue_search: private function that returns 2 if the word is in
   already in the queue, 1 if the word is not present but should be added to the queue (has
   higher frequency than some item already in queue), or 0 if it is not already in the queue
   but should not be inserted if the queue is full (has a lower priority than all elements
   presently in the queue)
   uses the node argument to return
   a pointer to the item prior to the item where the new item should be inserted
    If the word should be at the head of the queue, *node will contain NULL on return. */
int queue_search(queue_t* queue, char* word, int freq, queue_item_t** node)
{
	queue_item_t* next = queue->head;

	*node = NULL;
	while (next != NULL) {
		/* Do not allow repeat words in the queue */
		if (!strcmp(next->suggestion, word)) {
			return 2;	// 2 represents repreat word state
		}
		if (next->frequency < freq) {
			return 1;
		}
		*node = next;
		next = next->next;
	}

	return 0;
}

/* queue_insert: function inserts a word into the queue, unless it's already there
	or has a lower frequency than the items already contained
	function takes in a queue pointers as well as a pointer to the word to be
		considered as well as its frequency */
int queue_insert(queue_t* queue, char* sugg, int freq)
{
	queue_item_t *node, *next;
		
	/* Check if this item must be added to the queue */
	/* (We must add this item if there are less than QUEUE_MAX_ITEMS) */
	int searchState = queue_search(queue, sugg, freq, &node);
	if(searchState == 0 && !(queue->size < QUEUE_MAX_ITEMS)) {
		return 0;
	} else if (searchState == 2) {
		return 0;
	}

	/* Add the word in its sorted position */
	if (node == NULL) {
		/* The word should be at the head of the list */
		next = queue->head;
		/* Allocate space for the new item */
		queue->head = malloc(sizeof(queue_item_t));
		/* Allocate space for the word, plus the null terminator */
		queue->head->suggestion = malloc(strlen(sugg) + 1);
		strcpy(queue->head->suggestion, sugg);
		queue->head->frequency = freq;
		queue->head->next = next;
	} else {
		/* The word will not be the head of the list */
		next = node->next;
		/* Allocate space for the new node */
		node->next = malloc(sizeof(queue_item_t));
		/* Allocate space for the word, plus the null terminator */
		node->next->suggestion = malloc(strlen(sugg) + 1);
		strcpy(node->next->suggestion, sugg);
		node->next->frequency = freq;
		node->next->next = next;	
	}

	/* Increase suize of the queue */
	int size = queue->size;
	++size;
	queue->size = size;

	/* Remove the word at the bottom of the list if queue is too large */
	if (queue->size > QUEUE_MAX_ITEMS) {
		queue_item_t* curr = queue->head->next;
		queue_item_t* prev = queue->head;
		while(curr->next != NULL) {
			prev = curr;
			curr = curr->next;
		}
		free(curr->suggestion);
		free(curr);
		prev->next = NULL;
	}

	return 1;
}
