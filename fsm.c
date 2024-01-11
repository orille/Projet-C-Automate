// fsm.c
#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

FiniteStateMachine *creationFSM(int etats, int symboles) {
    FiniteStateMachine *fsm = malloc(sizeof(FiniteStateMachine));
    fsm->nombre_etats = etats;
    fsm->nombre_symboles = symboles;
    fsm->matrice_transition = malloc(etats * sizeof(int *));
    for (int i = 0; i < etats; i++) {
        fsm->matrice_transition[i] = malloc(symboles * sizeof(int));
        for (int j = 0; j < symboles; j++) {
            fsm->matrice_transition[i][j] = -1;
        }
    }
    return fsm;
}

void saisieFSM(FiniteStateMachine *fsm) {
    printf("Entrer les transitions pour chaque état et symbole :\n");
    for (int i = 0; i < fsm->nombre_etats; i++) {
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            printf("Transition de l'état %d avec le symbole %d: ", i, j);
            scanf("%d", &fsm->matrice_transition[i][j]);
        }
    }
}

void affichageFSM(FiniteStateMachine *fsm) {
    printf("Matrice de transition de la FSM :\n");
    for (int i = 0; i < fsm->nombre_etats; i++) {
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            printf("%d ", fsm->matrice_transition[i][j]);
        }
        printf("\n");
    }
}

void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(fichier, "%d %d\n", fsm->nombre_etats, fsm->nombre_symboles);
    for (int i = 0; i < fsm->nombre_etats; i++) {
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            fprintf(fichier, "%d ", fsm->matrice_transition[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
    printf("FSM enregistrée dans le fichier '%s'.\n", nom_fichier);
}


void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier) {
    FICHIER *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int etats, symboles;
    fscanf(fichier, "%d %d", &etats, &symboles);
    *fsm = creationFSM(etats, symboles);
    for (int i = 0; i < etats; i++) {
        for (int j = 0; j < symboles; j++) {
            fscanf(fichier, "%d", &(*fsm)->matrice_transition[i][j]);
        }
    }
    fclose(fichier);
    printf("FSM chargée depuis le fichier '%s'.\n", nom_fichier);
}

void supprFSM(FiniteStateMachine *fsm) {
    for (int i = 0; i < fsm->nombre_etats; i++) {
        free(fsm->matrice_transition[i]);
    }
    free(fsm->matrice_transition);
    free(fsm);
    printf("FSM supprimée.\n");
}
