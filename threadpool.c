//
// Created by icarob-eng, HelenaNotFunny, gabriel26077, DPDck972 (Rodrigo) on 08/12/25.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

#include "threadpool.h"
#include "queue.h" // Incluimos nossa lib de fila

// Ponteiro para o array de threads
static pthread_t *array_threads;
static int n_threads = -1;

// Instância global da fila de tarefas
static queue_t global_queue;

/**
 * Thread level function that executes the task provided to the thread pool
 */
void execute(void (*func)(void *p), void *p) {
    (*func)(p);
}

/**
 * Main code of worker thread, dequeues tasks and executes them.
 */
void *worker(void *param) {
    while (1) {
        // Remove a tarefa da fila (bloqueia se estiver vazia)
        task_t workload = queue_pop(&global_queue);

        // Verifica "Poison Pill" (sinal para encerrar a thread)
        if (workload.function == NULL) {
            break;
        }

        // Executa a tarefa
        execute(workload.function, workload.data);
    }

    pthread_exit(NULL);
}

/**
 * Submits function `func` to the pool with parameters `p`.
 */
int pool_submit(void (*func)(void *p), void *p) {
    // Cria a tarefa
    task_t new_task;
    new_task.function = func;
    new_task.data = p;

    // Insere na fila (substitui o antigo enqueue com TODO)
    queue_push(&global_queue, new_task);

    return 0;
}

/**
 * Maps the function `func` to the array `arr` `n` times.
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
 * Initializes the pool.
 */
int pool_init(const int _n_threads) {
    n_threads = _n_threads;
    array_threads = (pthread_t *) malloc(n_threads * sizeof(pthread_t));
    
    // Inicializa a fila (mutexes e semáforos internos)
    queue_init(&global_queue);

    int r = -1;
    for (int i=0; i<n_threads; i++) {
        r = pthread_create(&array_threads[i], NULL, worker, NULL);
        if (r != 0) return r;
    }

    return 0; // Sucesso
}

/**
 * Shutdown the thread pool.
 */
int pool_shutdown(void) {
    int r = -1;

    // 1. Envia "Poison Pills" para parar os workers
    // Envia uma tarefa vazia para cada thread, forçando elas a saírem do loop
    for (int i = 0; i < n_threads; i++) {
        pool_submit(NULL, NULL);
    }

    // 2. Espera as threads terminarem
    for (int i=0; i<n_threads; i++) {
        r = pthread_join(array_threads[i], NULL); // todo: substituir NULL por thread retval se necessario
        if (r != 0) return r;
    }

    // 3. Limpeza de memória
    free(array_threads);
    queue_destroy(&global_queue);

    return 0;
}