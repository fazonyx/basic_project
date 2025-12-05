#ifndef CLOCK_H
#define CLOCK_H

#include <stddef.h> // Pour size_t

// Structure pour représenter une heure
typedef struct Time {
    unsigned char hour;    // 0-23
    unsigned char minute;  // 0-59
    unsigned char second;  // 0-59
} Time;

// Initialise une structure Time
void time_init(Time* time, unsigned char h, unsigned char m, unsigned char s);

// Avance le temps d'une seconde
void time_tick(Time* time);

// Affiche l'heure au format HH:MM:SS
void time_display(const Time* time, char* buffer, size_t buffer_size);

// Vérifie si une heure est valide
int time_is_valid(const Time* time);

void time_get_current(Time* time_ptr);

#endif // CLOCK_H