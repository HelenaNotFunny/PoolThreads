//
// Created by icarob-eng, HelenaNotFunny, gabriel26077, DPDck972 (Rodrigo) on 08/12/25.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

/**
 * Submits function `func` to the pool with parameters `arg`.
 *
 * @param func function to be submitted to the pool
 * @param arg parameter to the function
 * @return 0 if success
 */
int pool_submit(void (*func)(void *arg), void *arg);

/**
 * Maps the function `func` to the array `args` `n` times.
 *
 * @param func function to be submitted to the pool
 * @param args array of parameters to map to the function
 * @param num_items number of elements (constant)
 * @return 0 if success submitting all parameters
 */
int pool_map(void (*func)(void *arg), void **args, const int num_items);

/**
 * Initializes the pool.
 *
 * @param num_threads number of threads in the pool (constant).
 * @return 0 if success creating all threads
 */
int pool_init(const int num_threads);

/**
 * Shutdown the thread pool.
 * Waits for all threads to finish their current tasks before destroying the pool.
 * @return 0 if success
 */
int pool_shutdown(void);

#endif // THREADPOOL_H