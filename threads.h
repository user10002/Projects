#include "q.h"

Queue* RunQ;

void start_thread(void (*function)(int), int threadID) {
    int stack_size = 8192;
    void* stackP = malloc(stack_size);
    TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t));
    init_TCB(tcb, function, stackP, stack_size, threadID);
    AddQueue(RunQ, tcb);
}


void run() {
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(RunQ->head->context));
}

void yield() {
    ucontext_t* prev = &(RunQ->head->context);
    RotateQueue(RunQ);
    ucontext_t* next = &(RunQ->head->context);
    swapcontext(prev, next);
}