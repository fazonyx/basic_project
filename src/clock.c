#include "../include/clock.h"
#include <time.h>
#include <stdio.h>

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

void time_display(const Time* time, char* buffer, size_t buffer_size) {
    // "HH:MM:SS\0" requires at least 9 characters.
    if (!buffer || buffer_size < 9) {
        return; // Not enough space, do nothing.
    }
    if (!time) {
        buffer[0] = '\0'; // Handle NULL time pointer gracefully.
        return;
    }
    snprintf(buffer, buffer_size, "%02d:%02d:%02d",
             time->hour, time->minute, time->second);
}

int time_is_valid(const Time* time) {
    if (!time) return 0;
    return (time->hour < 24 && time->minute < 60 && time->second < 60);
}

void time_get_current(Time* time_ptr) {
    if (!time_ptr) return;
    
    time_t current_time = time(NULL);
    struct tm* time_info = localtime(&current_time);
    
    time_ptr->hour = time_info->tm_hour;
    time_ptr->minute = time_info->tm_min;
    time_ptr->second = time_info->tm_sec;
}