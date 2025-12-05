CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L -Iinclude
TARGET = build/clock

# Fichiers source
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
TEST_TARGET = build/test_runner
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(patsubst tests/%.c,build/tests/%.o,$(TEST_SRC))


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

# Règle pour les tests
test: $(TEST_TARGET)
	@echo "Exécution des tests..."
	@./$(TEST_TARGET)

# Lien pour l'exécutable de test
$(TEST_TARGET): $(filter-out build/main.o,$(OBJ)) $(TEST_OBJ)
	$(CC) -o $@ $^

# Règle pour les objets de test
build/tests/%.o: tests/%.c | build/tests
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier de tests
build/tests:
	mkdir -p build/tests

.PHONY: all clean run