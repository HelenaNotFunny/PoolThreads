/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"

struct data {
    int a;
    int b;
};

void add(void *param) {
    struct data *temp = (struct data*)param;
    printf("Thread %lu: %d + %d = %d\n", pthread_self(), temp->a, temp->b, temp->a + temp->b);
    // free(temp); // Se usasse malloc, descomentaria aqui
}

int main(void) {
    pool_init(4); // 4 threads

    struct data work1 = {5, 10};
    struct data work2 = {10, 20};
    struct data work3 = {100, 200};

    pool_submit(&add, &work1);
    pool_submit(&add, &work2);
    pool_submit(&add, &work3);

    // O shutdown vai esperar todos terminarem antes de sair
    pool_shutdown(); 

    return 0;
}