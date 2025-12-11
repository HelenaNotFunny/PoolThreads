//
// Created by icarob-eng, HelenaNotFunny, gabriel26077, DPDck972 (Rodrigo) on 08/12/25.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "threadpool.h"
#include "atomic_queue.h"


// Variáveis estáticas (contexto do módulo)
static pthread_t *threads = NULL;
static int thread_count = 0;
static atomic_queue_t task_queue;

/**
 * Main code of worker thread.
 * Dequeues tasks and executes them until a Poison Pill is received.
 */
static void *worker_routine(void *) {
    while (1) {
        // Bloqueia até haver uma tarefa disponível
        task_t current_task = queue_pop(&task_queue);

        // Verifica "Poison Pill" (sinal para encerrar a thread)
        if (current_task.function == NULL) {
            break;
        }

        // Executa a função diretamente
        current_task.function(current_task.arg);
    }

    pthread_exit(NULL);
}

int pool_init(const int num_threads) {
    thread_count = num_threads;
    threads = (pthread_t *)malloc(thread_count * sizeof(pthread_t));
    
    if (threads == NULL) {
        perror("Failed to allocate memory for threads");
        return -1;
    }

    // Inicializa a fila
    queue_init(&task_queue);

    // Cria os workers
    for (int i = 0; i < thread_count; i++) {
        if (pthread_create(&threads[i], NULL, worker_routine, NULL) != 0) {
            perror("Failed to create thread");
            // Nota: Em um código de produção robusto, deveríamos limpar as threads já criadas aqui.
            return 1;
        }
    }

    return 0;
}
/*
 Cria uma tarefa utilizando o tipo task e o adiciona ao fim da fila instanciada no contexto do programa.
*/
int pool_submit(void (*func)(void *arg), void *arg) {
    task_t new_task;
    new_task.function = func;
    new_task.arg = arg;

    queue_push(&task_queue, new_task);
    return 0;
}

/*
 Designa para num_items threads na pool uma tarefa func.
*/
int pool_map(void (*func)(void *arg), void **args, const int num_items) {
    for (int i = 0; i < num_items; i++) {
        // Se houver erro no submit, retornamos (embora submit atual retorne sempre 0)
        int r = pool_submit(func, args[i]);
        if (r != 0) return r;
    }
    return 0;
}

int pool_shutdown(void) {
    // 1. Envia "Poison Pills" para parar os workers
    for (int i = 0; i < thread_count; i++) {
        pool_submit(NULL, NULL);
    }

    // 2. Espera as threads terminarem (Join)
    for (int i = 0; i < thread_count; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    // 3. Limpeza de memória
    free(threads);
    queue_destroy(&task_queue);
    
    // Reseta variáveis para evitar uso após shutdown
    threads = NULL;
    thread_count = 0;

    return 0;
}