CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = build/clock

# Fichiers source
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

# Détection du système d'exploitation
ifeq ($(OS),Windows_NT)
    LDFLAGS = -lws2_32
    TARGET := $(TARGET).exe
endif

# Création automatique du dossier build
$(shell mkdir -p build)

# Règles par défaut
all: $(TARGET)

# Lien des objets
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des sources
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier build
build:
	mkdir -p build

# Nettoyage
clean:
	rm -rf build

# Exécution
run: $(TARGET)
	@echo "Lancement du programme..."
	@./$(TARGET)

.PHONY: all clean run