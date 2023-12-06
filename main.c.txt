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
