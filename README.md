# 🧵 C Threadpool Library

🇧🇷 [Leia em Português](README.pt-BR.md)

A simple and efficient C library for managing a pool of worker threads using pthreads. It provides a lightweight task queue for asynchronous execution in multi-threaded applications.

This project demonstrates key concepts such as **concurrency**, **synchronization** (mutexes and condition variables), and the **Producer–Consumer** pattern, reducing the overhead of repeatedly creating and destroying threads.

---

## 📑 Table of Contents

- [About the Project](#about-the-project)
- [Directory Structure](#directory-structure)
- [Prerequisites](#prerequisites)
- [Build and Run](#build-and-run)
- [Usage](#usage)
- [Clean and Rebuild](#clean-and-rebuild)
- [Authors](#authors)

---

## 📖 About the Project

A **thread pool** maintains a set of worker threads that continuously wait for tasks in a thread-safe queue. When a task is submitted:

1. It is added to the queue.
2. An available worker thread retrieves and executes it.
3. After completion, the thread returns to the pool, ready for the next task.

### Key Features

- Dynamic creation of worker threads.
- Thread-safe task queue.
- Graceful shutdown (waits for all tasks to complete before terminating).

---

## 📂 Directory Structure

```plaintext
threadpool_project/
├── include/            # Public headers
│   ├── threadpool.h    # Threadpool API
│   └── atomic_queue.h  # Internal queue definitions
│
├── src/                # Library source code
│   ├── threadpool.c    # Thread and synchronization logic
│   └── atomic_queue.c  # Thread-safe queue implementation
│
├── examples/           # Example client application
│   └── client.c        # Usage example
│
├── docs/               # Documentation (e.g., diagrams, Doxygen)
├── report/             # Academic report / performance analysis
│   └── relatorio.pdf
│
├── obj/                # Object files (generated)
├── bin/                # Executables (generated)
│   └── client
│
└── Makefile            # Build automation
```

---

## ⚙️ Prerequisites

- **GCC** (or a compatible C compiler)
- **Make**
- **Linux/Unix environment** (due to `pthread.h`)

---

## 🚀 Build and Run

### Compile

```bash
make
```

### Run

```bash
./bin/client <num_threads> <num_terms>
```

Or using the convenience rule:

```bash
make run NTHREADS=<num_threads> NTERMS=<num_terms>
```

---

## 🧹 Clean and Rebuild

```bash
make clean
```

---

## 💻 Usage

```c
#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

// Task executed by worker threads
void my_task(void* arg) {
    int* num = (int*)arg;
    printf("Processing number: %d\n", *num);
    sleep(1); // Simulate workload
}

int main() {
    threadpool_t* pool = threadpool_create(4);

    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
        threadpool_add(pool, my_task, &data[i]);
    }

    threadpool_destroy(pool);
    return 0;
}
```

---

## 🛠️ Technologies Used

- **C (C99/C11)**
- **POSIX Threads (pthreads)**
- **Make**

---

## ✒️ Authors

- Maria Helena Fernandes Leocádio - [HelenaNotFunny](https://github.com/HelenaNotFunny)
- Icaro Bruno Silbe Cortês - [icarob-eng](https://github.com/icarob-eng)
- Gabriel Sebastião do Nascimento Neto - [gabriel26077](https://github.com/gabriel26077)
- Rodrigo de Menezes Souza - [DPDck972](https://github.com/DPDck972)
