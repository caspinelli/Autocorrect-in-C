#ifndef QUEUE_H
#define QUEUE_H

/* queue: a priority queue of words associated with integer frequencies
	- contains at most QUEUE_MAX_ITEMS at any given time
	- allows insertion at any arbitrary time */

/* maximum number of items a queue should contain - this can be adjusted to return a different
	total number of suggestions in the main suggest program (main.c) */
#define QUEUE_MAX_ITEMS 50

typedef struct queue_item {
	char* suggestion;
	int frequency;
	struct queue_item *next;
} queue_item_t;

typedef struct {
	queue_item_t* head;  // NULL if the queue is empty
	int size;	// keeps track of size to maintain a rigid # of objects
} queue_t;

void queue_init(queue_t* queue);
void queue_destroy(queue_t* queue);

int queue_insert(queue_t* queue, char* sugg, int freq);

#endif //QUEUE_H
