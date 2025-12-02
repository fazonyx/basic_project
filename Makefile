CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = hello

# Règle par défaut
all: $(TARGET)

# Règle de compilation
$(TARGET): hello.c
	$(CC) $(CFLAGS) -o $(TARGET) hello.c

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Nettoyage
clean:
	rm -f $(TARGET)
