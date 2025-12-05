#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>  // Pour sleep() sous Unix/Linux
#endif
#include "../include/clock.h"

int main() {
    Time current_time;
    char time_buffer[12]; // Buffer pour stocker la chaîne de l'heure
    
    printf("Horloge en temps réel - Appuyez sur Ctrl+C pour quitter\n");
    
    while (1) {
        time_get_current(&current_time);
        time_display(&current_time, time_buffer, sizeof(time_buffer));
        printf("\rHeure actuelle: %s", time_buffer);
        fflush(stdout);  // Force l'affichage immédiat
        
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
    }
    
    return 0;
}