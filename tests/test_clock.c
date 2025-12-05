#include <stdio.h>
#include <string.h>  // Pour strcmp
#include "../include/clock.h"
#include "minunit.h"

int tests_run = 0;

static char* test_time_init() {
    Time t;
    time_init(&t, 12, 30, 45);
    mu_assert("Erreur: Heure incorrecte", t.hour == 12);
    mu_assert("Erreur: Minutes incorrectes", t.minute == 30);
    mu_assert("Erreur: Secondes incorrectes", t.second == 45);
    return 0;
}

// Fonction utilitaire pour vérifier l'heure
static char* assert_time(Time* t, int h, int m, int s, const char* msg) {
    if(!(t->hour == h && t->minute == m && t->second == s)){
        return (char*)msg;
    }
    return 0;
}

static char* test_tick_second() {
    Time t;
    time_init(&t, 12, 30, 44);
    time_tick(&t);
    assert_time(&t, 12, 30, 45, "Erreur: L'incrémentation des secondes a échoué");
    return 0;
}

static char* test_tick_minute() {
    Time t;
    time_init(&t, 12, 30, 59);
    time_tick(&t);
    assert_time(&t, 12, 31, 0, "Erreur: La bascule des minutes a échoué");
    return 0;
}

static char* test_tick_hour() {
    Time t;
    time_init(&t, 23, 59, 59);
    time_tick(&t);
    assert_time(&t, 0, 0, 0, "Erreur: La bascule des heures a échoué");
    return 0;
}

static char* test_display_format() {
    Time t;
    char buffer[12];
    
    // Test 1: Format standard
    time_init(&t, 9, 5, 30);
    time_display(&t, buffer, sizeof(buffer));
    mu_assert("Format incorrect pour 09:05:30", strcmp(buffer, "09:05:30") == 0);
    
    // Test 2: Minuit
    time_init(&t, 0, 0, 0);
    time_display(&t, buffer, sizeof(buffer));
    mu_assert("Format incorrect pour 00:00:00", strcmp(buffer, "00:00:00") == 0);
    
    // Test 3: Midi
    time_init(&t, 12, 0, 0);
    time_display(&t, buffer, sizeof(buffer));
    mu_assert("Format incorrect pour 12:00:00", strcmp(buffer, "12:00:00") == 0);
    
    // Test 4: Cas limite (23:59:59)
    time_init(&t, 23, 59, 59);
    time_display(&t, buffer, sizeof(buffer));
    mu_assert("Format incorrect pour 23:59:59", strcmp(buffer, "23:59:59") == 0);
    
    // Test 5: Pointeur NULL
    time_display(NULL, buffer, sizeof(buffer));
    mu_assert("Gestion incorrecte de NULL (devrait être une chaîne vide)", strcmp(buffer, "") == 0);
    
    return 0;
}

// Effectuer les tests
static char* all_tests() {
    mu_run_test(test_time_init);
    mu_run_test(test_tick_second);
    mu_run_test(test_tick_minute);
    mu_run_test(test_tick_hour);
    mu_run_test(test_display_format);
    return 0;
}

int main() {
    char *result = all_tests();
    if (result != 0) {
        printf("ÉCHEC: %s\n", result);
    } else {
        printf("TOUS LES TESTS ONT RÉUSSI\n");
    }
    printf("Tests exécutés: %d\n", tests_run);
    return result != 0;
}
