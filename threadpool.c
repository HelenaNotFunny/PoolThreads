//
// Created by icarob-eng, ... on 08/12/25.  # TODO: add your names (1/4)
//

/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"


// pointer to array of threads of size n_threads
pthread_t *array_threads;
int n_threads = -1;

sem_t semaphore_tasks;

// this represents work that has to be 
// completed by a thread in the pool
typedef struct {
    void (*function)(void *p);
    void *data;
}
task;

// the work queue  todo: implement queue as linked list
task *queue_tasks;

// insert a task into the queue
// returns 0 if successful or 1 otherwise, 
int enqueue(const task t) {
    // todo: semaphore + linked list queue
    *queue_tasks = t;

    return 0;
}

// remove a task from the queue
task dequeue() {  // todo
    return *queue_tasks;
}

// Thread level function that executes the task provided to the thread pool
void execute(void (*func)(void *p), void *p) {  // todo: removable???
    (*func)(p);
}

// Main code of worker thread, dequeue tasks and executes them
void *worker(void *param) {
    // execute the task
    // todo: loop with semaphore and dequeue
    // while (1) {
        task workload = dequeue();
    
        execute(workload.function, workload.data);
    // }

    pthread_exit(0);
}

/**
 * Submits function `func` to the pool with parameters `p`.
 *
 * @param func function to be submitted to the pool
 * @param p parameter to the function
 * @return 0 if success
 */
int pool_submit(void (*func)(void *p), void *p) {
    // todo: submit with enqueue
    queue_tasks->function = func;
    queue_tasks->data = p;

    return 0;
}

/**
 * Maps the function `func` to the array `arr` `n` times.
 *
 * @param func function to be submitted to the pool
 * @param arr array of parameters to map to the function
 * @param n num
 * @return 0 if success submitting all parameters
 */
int pool_map(void (*func)(void *p), void **arr, const int n) {
    int r = -1;
    for (int i=0; i<n; i++) {
        r = pool_submit(func, arr[i]);
        if (r != 0) return r;
    }

    return r;
}

/**
 *  Initializes the pool.
 *
 * @param _n_threads number of threads in the pool.
 * @return 0 if success creating all threads
 */
int pool_init(const int _n_threads) {
    n_threads = _n_threads;
    array_threads = (pthread_t *) malloc(n_threads * sizeof(pthread_t));
    // if `sizeof(pthread_t)` doesn't work, use #define PTHREAD_SIZE sizeof(unsigned long int)
    int r=-1;

    for (int i=0; i<n_threads; i++) {
        r = pthread_create(&array_threads[i], NULL, worker, NULL);
        if (r != 0) return r;
    }

    sem_init(&semaphore_tasks, 0, 0);  // inits semaphore with 0 tasks
    // todo: init queue

    return r;
}

// shutdown the thread pool
int pool_shutdown(void) {
    int r=-1;
    for (int i=0; i<n_threads; i++) {
        r = pthread_join(array_threads[i], NULL);  // todo: substituir NULL por thread retval
        if (r != 0) return r;
    }

    free(array_threads);
    sem_destroy(&semaphore_tasks);

    return r;
}
