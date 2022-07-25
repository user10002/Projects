#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"


typedef struct Queue {
    TCB_t* head;
    TCB_t* tail;
} Queue;

Queue* InitQueue();
void AddQueue(Queue* queue, TCB_t* qEl);
TCB_t* DelQueue(Queue* queue);
void RotateQueue(Queue* queue);
int isQueueEmpty(Queue* queue);

Queue* InitQueue() {
    return (Queue*) malloc(sizeof(Queue));
}

void AddQueue(Queue* queue, TCB_t* qEl) {
    if (isQueueEmpty(queue)) {
        queue->head = qEl;
        queue->tail = qEl;
    } else {
        qEl->prev = queue->tail;
        qEl->next = NULL;
        queue->tail->next = qEl;
        queue->tail = qEl;
    }
}

TCB_t* DelQueue(Queue* queue) {
    if (!isQueueEmpty(queue)) {
        TCB_t* delQEl = queue->head;
        if (queue->head == queue->tail) {
            queue->head = queue->tail = NULL;
        } else {
            queue->head = queue->head->next;
            queue->head->prev = NULL;
        }
        return delQEl;
    }
}

void RotateQueue(Queue* queue) {
    if (!isQueueEmpty(queue)) {
        TCB_t* delQEl = DelQueue(queue);
        AddQueue(queue, delQEl);
    }
}


int isQueueEmpty(Queue* queue) {
    if (queue->head == NULL) return 1;
    else return 0;
}