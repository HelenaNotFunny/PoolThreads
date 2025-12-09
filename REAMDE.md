# 🧵 C Threadpool Library

Uma implementação robusta e eficiente de uma **Threadpool (Pool de Threads)** em linguagem C.

Este projeto demonstra o uso de **concorrência**, **sincronização** (mutexes e variáveis de condição) e o padrão **Produtor-Consumidor** para gerenciar tarefas assíncronas de forma eficiente, evitando o overhead de criar e destruir threads repetidamente.

-----

## 📑 Índice

  - [Sobre o Projeto](https://www.google.com/search?q=%23-sobre-o-projeto)
  - [Estrutura de Diretórios](https://www.google.com/search?q=%23-estrutura-de-diret%C3%B3rios)
  - [Pré-requisitos](https://www.google.com/search?q=%23-pr%C3%A9-requisitos)
  - [Como Compilar e Executar](https://www.google.com/search?q=%23-como-compilar-e-executar)
  - [Como Usar a Biblioteca](https://www.google.com/search?q=%23-como-usar-a-biblioteca)
  - [Limpeza e Recompilação](https://www.google.com/search?q=%23-limpeza-e-recompila%C3%A7%C3%A3o)
  - [Autoria](https://www.google.com/search?q=%23-autoria)

-----

## 📖 Sobre o Projeto

Uma **Threadpool** mantém um conjunto de threads "trabalhadoras" (workers) ativas, esperando por tarefas em uma fila segura (thread-safe queue). Quando uma tarefa é submetida:

1.  Ela é adicionada à fila.
2.  Uma thread disponível a retira e executa.
3.  Ao terminar, a thread volta a ficar disponível para a próxima tarefa.

**Principais funcionalidades:**

  * Criação dinâmica de N threads.
  * Fila de tarefas thread-safe.
  * Encerramento gracioso (Graceful Shutdown): aguarda as tarefas terminarem antes de fechar.

-----

## 📂 Estrutura de Diretórios

O projeto segue uma arquitetura modular para separar a implementação da biblioteca, a interface pública e a aplicação cliente.

```plaintext
threadpool_project/
├── include/            # CABEÇALHOS PÚBLICOS
│   ├── threadpool.h    # Contratos da API da Threadpool
│   └── atomic_queue.h  # Definições da Fila (estrutura interna)
│
├── src/                # CÓDIGO FONTE DA BIBLIOTECA
│   ├── threadpool.c    # Lógica das threads, workers e sync
│   └── atomic_queue.c  # Implementação da fila thread-safe
│
├── examples/           # APLICAÇÃO CLIENTE
│   └── client.c        # Main: Exemplo de uso da biblioteca
│
├── docs/               # DOCUMENTAÇÃO
│   └── ...             # Diagramas e documentação Doxygen
│
├── report/             # RELATÓRIOS
│   └── relatorio.pdf   # Análise de desempenho/descrição acadêmica
│
├── obj/                # OBJETOS TEMPORÁRIOS (Gerado pelo Make)
│   └── *.o             # Arquivos compilados intermédios
│
├── bin/                # EXECUTÁVEIS (Gerado pelo Make)
│   └── client          # O binário final pronto para rodar
│
└── Makefile            # AUTOMAÇÃO DE BUILD
```

-----

## ⚙️ Pré-requisitos

  * **GCC** (GNU Compiler Collection) ou compatível.
  * **Make** (Ferramenta de automação de build).
  * Ambiente **Linux/Unix** (devido ao uso da `pthread.h`).

-----

## 🚀 Como Compilar e Executar

Utilizamos um `Makefile` configurado para gerenciar as dependências e diretórios automaticamente.

### 1\. Compilar todo o projeto

No terminal, na raiz do projeto (`threadpool_project/`), execute:

```bash
make
```

*Isso criará automaticamente as pastas `obj/` e `bin/` se elas não existirem e compilará o executável.*

### 2\. Rodar a aplicação

O executável final será gerado dentro da pasta `bin`. Execute com:

```bash
./bin/client
```

*Ou, se o Makefile tiver a regra de conveniência:*

```bash
make run
```

-----

## 🧹 Limpeza e Recompilação

Para limpar arquivos temporários (`.o`) e o executável final (útil para garantir uma recompilação limpa):

```bash
make clean
```

-----

## 💻 Como Usar a Biblioteca

Abaixo um exemplo simplificado de como utilizar a API no seu `examples/client.c`:

```c
#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

// Função que as threads irão executar
void minha_tarefa(void* arg) {
    int* num = (int*)arg;
    printf("Thread processando numero: %d\n", *num);
    sleep(1); // Simula trabalho pesado
}

int main() {
    // 1. Cria uma pool com 4 threads
    threadpool_t* pool = threadpool_create(4);

    // 2. Submete tarefas
    int dados[10];
    for(int i = 0; i < 10; i++) {
        dados[i] = i;
        threadpool_add(pool, minha_tarefa, &dados[i]);
    }

    // 3. Destrói a pool (aguarda o fim das tarefas)
    threadpool_destroy(pool);

    return 0;
}
```

-----

## 🛠️ Tecnologias Utilizadas

  * **C Standard (C99/C11)**
  * **POSIX Threads (pthreads)**: Para gerenciamento de threads e mutexes.
  * **Make**: Para orquestração da compilação.

-----

## ✒️ Autoria

Desenvolvido por **[Nossos nomes (lembrar de por depois)]**.

-----

