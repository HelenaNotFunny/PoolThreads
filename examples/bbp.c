//
// Created by icarob-eng on 10/12/25.
// Implementation of Bailey-Borwein-Plouffe algorithm
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "threadpool.h"


double acc;  // accumulator
pthread_mutex_t mutex_acc = PTHREAD_MUTEX_INITIALIZER;

double kth_term(const int k) {
    const double l = 8 * k;
    return pow(2.0, -4*k) * (
    + 4/(l+1)
    - 2/(l+4)
    - 1/(l+5)
    - 1/(l+6)
    );
}

void compute_k(const int k) {
    pthread_mutex_lock(&mutex_acc);
    acc = kth_term(k);
    pthread_mutex_unlock(&mutex_acc);
}

int main(const int argc, const char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n threads> <n terms>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n_terms = atoi(argv[2]);  // n_terms

    // creates and populates the vector of k
    int vec_k[n_terms];
    for (int k = 0; k < n_terms; k++) {
        vec_k[k] = k;
    }

    pool_init(atoi(argv[1]));  // n_threads

    pool_map(&compute_k, &vec_k, n_terms);

    pool_shutdown();

    printf("Value of pi computed with %d terms: %f\n", n_terms, acc);

    return 0;
}