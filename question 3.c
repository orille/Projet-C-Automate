#include <stdio.h>
#include <stdbool.h>

// Définition de la structure de transition
typedef struct {
    int currentState;
    char inputSymbol;
} Transition;

// Fonction de vérification du déterminisme
bool isDeterministic(const Transition transitions[], int numTransitions) {
    for (int i = 0; i < numTransitions; ++i) {
        for (int j = i + 1; j < numTransitions; ++j) {
            // Vérifier si deux transitions ont la même paire (état, symbole)
            if (transitions[i].currentState == transitions[j].currentState &&
                transitions[i].inputSymbol == transitions[j].inputSymbol) {
                return false; // L'automate n'est pas déterministe
            }
        }
    }
    return true; // L'automate est déterministe
}
