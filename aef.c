#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numberOfStates;
    int numberOfSymbols;
    int **transitionMatrix;
} FiniteStateMachine;

FiniteStateMachine *createFSM(int states, int symbols) {
    FiniteStateMachine *fsm = malloc(sizeof(FiniteStateMachine));
    fsm->numberOfStates = states;
    fsm->numberOfSymbols = symbols;
    fsm->transitionMatrix = malloc(states * sizeof(int *));
    for (int i = 0; i < states; i++) {
        fsm->transitionMatrix[i] = malloc(symbols * sizeof(int));
        for (int j = 0; j < symbols; j++) {
            fsm->transitionMatrix[i][j] = -1;
        }
    }
    return fsm;
}

void inputFSM(FiniteStateMachine *fsm) {
    printf("Entrer les transitions pour chaque état et symbole :\n");
    for (int i = 0; i < fsm->numberOfStates; i++) {
        for (int j = 0; j < fsm->numberOfSymbols; j++) {
            printf("Transition de l'état %d avec le symbole %d: ", i, j);
            scanf("%d", &fsm->transitionMatrix[i][j]);
        }
    }
}

void printFSM(FiniteStateMachine *fsm) {
    printf("Matrice de transition de la FSM :\n");
    for (int i = 0; i < fsm->numberOfStates; i++) {
        for (int j = 0; j < fsm->numberOfSymbols; j++) {
            printf("%d ", fsm->transitionMatrix[i][j]);
        }
        printf("\n");
    }
}

void saveFSMToFile(FiniteStateMachine *fsm, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(file, "%d %d\n", fsm->numberOfStates, fsm->numberOfSymbols);
    for (int i = 0; i < fsm->numberOfStates; i++) {
        for (int j = 0; j < fsm->numberOfSymbols; j++) {
            fprintf(file, "%d ", fsm->transitionMatrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("FSM enregistrée dans le fichier '%s'.\n", filename);
}

void loadFSMFromFile(FiniteStateMachine **fsm, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int states, symbols;
    fscanf(file, "%d %d", &states, &symbols);
    *fsm = createFSM(states, symbols);
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < symbols; j++) {
            fscanf(file, "%d", &(*fsm)->transitionMatrix[i][j]);
        }
    }
    fclose(file);
    printf("FSM chargée depuis le fichier '%s'.\n", filename);
}

void deleteFSM(FiniteStateMachine *fsm) {
    for (int i = 0; i < fsm->numberOfStates; i++) {
        free(fsm->transitionMatrix[i]);
    }
    free(fsm->transitionMatrix);
    free(fsm);
    printf("FSM supprimée.\n");
}

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
