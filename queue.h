#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <semaphore.h>

// Define o formato da tarefa
typedef struct {
    void (*function)(void *p);
    void *data;
} task_t;

// Nó da lista encadeada
typedef struct node {
    task_t task;
    struct node *next;
} node_t;

// A estrutura da fila em si
typedef struct {
    node_t *head;
    node_t *tail;
    pthread_mutex_t lock; // Protege a lista (head/tail)
    sem_t count;          // Conta tarefas disponíveis
} queue_t;

void queue_init(queue_t *q);
void queue_push(queue_t *q, task_t t);
task_t queue_pop(queue_t *q);
void queue_destroy(queue_t *q);

#endif