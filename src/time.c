#include <stdio.h>
#include "../include/time.h"

void time_init(Time* time, unsigned char h, unsigned char m, unsigned char s) {
    if (time) {
        time->hour = h;
        time->minute = m;
        time->second = s;
    }
}

void time_tick(Time* time) {
    if (!time) return;

    time->second++;
    if (time->second >= 60) {
        time->second = 0;
        time->minute++;

        if (time->minute >= 60) {
            time->minute = 0;
            time->hour = (time->hour + 1) % 24;
        }
    }
}

// Dans src/time.c
char* time_display(const Time* time) {
    static char buffer[12]; // HH:MM:SS + 1 pour le null terminator + \0
    if (!time) return "INVALID";
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", 
             time->hour, time->minute, time->second);
    return buffer;
}

int time_is_valid(const Time* time) {
    if (!time) return 0;
    return (time->hour < 24 && time->minute < 60 && time->second < 60);
}