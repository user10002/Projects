#include "threads.h"

typedef struct Sem {
    int val;
    Queue* SemQ;
} Sem;

Sem* InitSem(int value) {
    Sem* semaphore = (Sem*) malloc(sizeof(Sem));
    semaphore->val = value;
    semaphore->SemQ = InitQueue();
    return semaphore;
}

void P(Sem* semaphore) {
    while (1) {
        if (semaphore->val <= 0) {
            TCB_t* item = DelQueue(RunQ);
            AddQueue(semaphore->SemQ, item);
            if (isQueueEmpty(RunQ)) exit(0);
            swapcontext(&(semaphore->SemQ->tail->context), &(RunQ->head->context));
        } else {
            semaphore->val--;
            return;
        }
    }
}

void V(Sem* semaphore) {
    if (!isQueueEmpty(semaphore->SemQ)) {
        TCB_t* item = DelQueue(semaphore->SemQ);
        AddQueue(RunQ, item);
    }
    semaphore->val++;
}