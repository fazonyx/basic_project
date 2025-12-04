#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>  // Pour sleep() sous Unix/Linux
#endif
#include "../include/time.h"

int main() {
    Time clock;
    time_init(&clock, 23, 59, 55); // 23h59:55
    
    printf("Starting the clock...\n");

    // Simuler le temps qui passe
    for (int i = 0; i < 10; i++) {
        printf("Current time: ");
        time_display(&clock);
        printf("\n");
        time_tick(&clock);
        
        #ifdef _WIN32
        Sleep(1000);  // 1000 ms sous Windows
        #else
        sleep(1);     // 1 seconde sous Unix/Linux
        #endif
    }
    return 0;
}