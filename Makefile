CC = gcc
CFLAGS = -Wall -pthread -g

# Agora usamos client.o em vez de main.o
OBJS = client.o threadpool.o queue.o

# Alvo principal (gera o executável 'app')
app: $(OBJS)
	$(CC) $(CFLAGS) -o app $(OBJS)

# Regra para o client.c
client.o: client.c threadpool.h
	$(CC) $(CFLAGS) -c client.c

# Regra para o threadpool (depende da queue)
threadpool.o: threadpool.c threadpool.h queue.h
	$(CC) $(CFLAGS) -c threadpool.c

# Regra para a fila
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

# Limpeza
clean:
	rm -f *.o app