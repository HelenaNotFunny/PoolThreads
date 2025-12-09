#include "queue.h"
#include <stdlib.h>

void queue_init(queue_t *q) {
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    sem_init(&q->count, 0, 0); 
}

void queue_push(queue_t *q, task_t t) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->task = t;
    new_node->next = NULL;

    pthread_mutex_lock(&q->lock); 
    if (q->tail == NULL) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    pthread_mutex_unlock(&q->lock);
    
    sem_post(&q->count); // Avisa que tem trabalho
}

task_t queue_pop(queue_t *q) {
    sem_wait(&q->count); // Dorme se não tiver trabalho

    pthread_mutex_lock(&q->lock);
    node_t *tmp = q->head;
    task_t task = tmp->task;

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    pthread_mutex_unlock(&q->lock);

    free(tmp); 
    return task;
}

void queue_destroy(queue_t *q) {
    // Limpa sobras se houver
    while(q->head != NULL) {
        node_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
    pthread_mutex_destroy(&q->lock);
    sem_destroy(&q->count);
}