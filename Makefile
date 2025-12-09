# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -pthread -g -I./include

# Estrutura de Pastas
INCDIR = include
SRCDIR = src
EXMDIR = examples
OBJDIR = obj
BINDIR = bin

# Onde vai ficar o executável final
TARGET = $(BINDIR)/examples

# Lista de arquivos fontes da biblioteca (src/*.c)
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Lista de objetos da biblioteca (obj/*.o)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# O objeto do cliente é separado
CLIENT_SRC = $(EXMDIR)/client.c
CLIENT_OBJ = $(OBJDIR)/client.o

# --- Regras de Compilação ---

# Regra padrão: cria o executável
all: directories $(TARGET)

# Cria o executável linkando tudo (Lib + Cliente)
$(TARGET): $(OBJECTS) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compila os arquivos da biblioteca (.c -> .o)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compila o cliente (.c -> .o)
$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria as pastas de build se não existirem
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Limpa tudo
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Atalho para rodar
run: all
	./$(TARGET)

.PHONY: all clean directories run