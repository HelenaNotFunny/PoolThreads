#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <semaphore.h>

/**
 * Representa uma tarefa a ser executada pela thread.
 */
typedef struct task {
    void (*function)(void *arg);
    void *arg;
} task_t;

/**
 * Nó da lista encadeada da fila.
 */
typedef struct queue_node {
    task_t task;
    struct queue_node *next;
} queue_node_t;

/**
 * Estrutura principal da fila (Thread-safe).
 */
typedef struct queue {
    queue_node_t *head;
    queue_node_t *tail;
    pthread_mutex_t lock; // Mutex para exclusão mútua
    sem_t task_count;     // Semáforo para sinalizar disponibilidade
} queue_t;

// Protótipos das funções
void queue_init(queue_t *q);
void queue_push(queue_t *q, task_t t);
task_t queue_pop(queue_t *q);
void queue_destroy(queue_t *q);

#endif // QUEUE_H