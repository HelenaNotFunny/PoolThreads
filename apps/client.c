/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"

// Estrutura de dados definida pelo cliente (usuário da lib)
struct data {
    int a;
    int b;
};

// Função que será executada pelos workers
void add(void *arg) {
    struct data *val = (struct data*)arg;
    
    // Simula um trabalho pesado
    // usleep(1000); 

    printf("Thread ID %lu processou: %d + %d = %d\n", 
           pthread_self(), val->a, val->b, val->a + val->b);
}

int main(void) {
    // 1. Inicializa o pool com 4 threads
    if (pool_init(4) != 0) {
        fprintf(stderr, "Erro ao inicializar Thread Pool\n");
        return 1;
    }
    printf("Pool inicializado com 4 threads.\n");

    // 2. Cria alguns trabalhos (Tasks)
    // Como pool_shutdown garante o join, podemos usar variaveis da stack com segurança aqui.
    struct data t1 = {5, 10};
    struct data t2 = {10, 20};
    struct data t3 = {100, 200};
    struct data t4 = {1, 1};
    struct data t5 = {99, 0};

    // 3. Submete os trabalhos
    pool_submit(add, &t1);
    pool_submit(add, &t2);
    pool_submit(add, &t3);
    pool_submit(add, &t4);
    pool_submit(add, &t5);

    printf("Tarefas submetidas.\n");

    // 4. Encerra o pool (bloqueia até tudo terminar)
    pool_shutdown();
    printf("Pool encerrado com sucesso.\n");

    return 0;
}