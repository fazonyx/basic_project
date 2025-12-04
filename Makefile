CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = build/clock

# Création automatique du dossier build
\$(shell mkdir -p build)

# Règles par défaut
all: \$(TARGET)

clean:
\trm -rf build

.PHONY: all clean