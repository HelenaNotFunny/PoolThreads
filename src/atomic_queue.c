//
// Created by icarob-eng, HelenaNotFunny, gabriel26077, DPDck972 (Rodrigo) on 08/12/25.
//

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#include "atomic_queue.h"


void queue_init(atomic_queue_t *q) {
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    sem_init(&q->task_count, 0, 0);
}

void queue_push(atomic_queue_t *q, task_t t) {
    // Aloca o nó
    queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
    new_node->task = t;
    new_node->next = NULL;

    // Região Crítica
    pthread_mutex_lock(&q->lock);
    
    if (q->tail == NULL) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    
    pthread_mutex_unlock(&q->lock);

    // Sinaliza que há uma nova tarefa
    sem_post(&q->task_count);
}

task_t queue_pop(atomic_queue_t *q) {
    // Aguarda disponibilidade de tarefa
    sem_wait(&q->task_count);

    // Região Crítica
    pthread_mutex_lock(&q->lock);
    
    queue_node_t *temp_node = q->head;
    task_t task = temp_node->task;

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    
    pthread_mutex_unlock(&q->lock);

    // Libera a memória do nó (não da tarefa/dados)
    free(temp_node);
    
    return task;
}

void queue_destroy(atomic_queue_t *q) {
    while (q->head != NULL) {
        queue_node_t *temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    pthread_mutex_destroy(&q->lock);
    sem_destroy(&q->task_count);
}