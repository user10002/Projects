//Omar Solis
//CSE330
//Summer 2021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"
//#include "threads.h"


int Philosophers;
int Entries;

Sem** Chopsticks;

void philosopher(int philosopherID) {
    int leftChopstick = (philosopherID - 1) % Philosophers;
    int rightChopstick = philosopherID % Philosophers;

    P(Chopsticks[leftChopstick]);
    yield();
    P(Chopsticks[rightChopstick]);
    yield();

    printf("\n Philosopher %d is eating \n", philosopherID);
    V(Chopsticks[leftChopstick]);
    V(Chopsticks[rightChopstick]);

    TCB_t* item = DelQueue(RunQ);
    if (!isQueueEmpty(RunQ)) {
        swapcontext(&(item->context), &(RunQ->head->context));
    }
}

int main() {
    RunQ = InitQueue();
    scanf("%d, %d", &Philosophers, &Entries);
    Chopsticks = (Sem**) malloc(Philosophers * sizeof(Sem));

    for (int i = 0; i < Philosophers; i++) {
        Chopsticks[i] = InitSem(1);
    }

    for (int i = 0; i < Entries; i++) {
        int threadID;
        scanf("%d", &threadID);
        void* function = philosopher;
        start_thread(function, threadID);
    }
    run();

    return 0;
}
