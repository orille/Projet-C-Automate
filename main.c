// main.c
#include <stdio.h>
#include "fsm.h"

int main() {
    int choice;
    printf("Choisir une option :\n");
    printf("1. Saisir une nouvelle FSM\n");
    printf("2. Charger une FSM depuis un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choice);

    FiniteStateMachine *fsm;

    if (choice == 1) {
        int states, symbols;
        printf("Nombre d'états : ");
        scanf("%d", &states);
        printf("Nombre de symboles : ");
        scanf("%d", &symbols);

        fsm = createFSM(states, symbols);
        inputFSM(fsm);
        printFSM(fsm);
        saveFSMToFile(fsm, "fsm.txt");
    } else if (choice == 2) {
        char filename[100];
        printf("Entrez le nom du fichier à charger : ");
        scanf("%s", filename);
        loadFSMFromFile(&fsm, filename);
        printFSM(fsm);
    } else {
        printf("Choix non valide.\n");
        return 1;
    }

    deleteFSM(fsm);
    return 0;
}


// 3
bool isComplete(const Transition transitions[], int numTransitions, int numStates, const char alphabet[]) {
    for (int state = 0; state < numStates; ++state) {
        for (int symbol = 0; symbol < strlen(alphabet); ++symbol) {
            bool transitionFound = false;

            // Vérifier si une transition est définie pour la paire (état, symbole)
            for (int i = 0; i < numTransitions; ++i) {
                if (transitions[i].currentState == state && transitions[i].inputSymbol == alphabet[symbol]) {
                    transitionFound = true;
                    break;
                }
            }

            // Si aucune transition n'est trouvée, l'automate n'est pas complet
            if (!transitionFound) {
                return false;
            }
        }
    }
    return true; // L'automate est complet
}

// Fonction pour ajouter une transition à l'automate
void addTransition(Automaton *automaton, int currentState, char inputSymbol, int nextState) {
    automaton->transitions[automaton->numTransitions].currentState = currentState;
    automaton->transitions[automaton->numTransitions].inputSymbol = inputSymbol;
    automaton->transitions[automaton->numTransitions].nextState = nextState;
    automaton->numTransitions++;
}
//4
while(!isComplete(const Transition transitions[], int numTransitions, int numStates, const char alphabet[]){
void addNonFinalState(Automaton *automaton, int *finalStates, int *numFinalStates) {
    int newState = automaton->numStates;
    automaton->numStates++;

    // Ajouter une transition bidirectionnelle avec une lettre arbitraire
    addTransition(automaton, newState, 'x', newState);
    addTransition(automaton, newState, 'y', newState);

    // Ajouter l'état non final à la liste des états finaux (si nécessaire)
    if (!isFinalState(newState, finalStates, *numFinalStates)) {
        finalStates[*numFinalStates] = newState;
        (*numFinalStates)++;
    }
}}
