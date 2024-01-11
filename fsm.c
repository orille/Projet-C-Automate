// fsm.c
#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

// Création d'une nouvelle instance de la structure FiniteStateMachine et initialisation des variables retournant un pointeur vers cette nouvelle structure
FiniteStateMachine *creationFSM(int etats, int symboles) {
    FiniteStateMachine *fsm = malloc(sizeof(FiniteStateMachine));    // allocation dynamique de la mémoire pour la nouvelle instance de FiniteStateMachine
    // initialisations des variables de la structure avec les valeurs int en argument de cette fonction
    fsm->nombre_etats = etats;    
    fsm->nombre_symboles = symboles;
    // allocation dynamique de la mémoire pour la matruce de transition
    fsm->matrice_transition = malloc(etats * sizeof(int *));
    for (int i = 0; i < etats; i++) {
        fsm->matrice_transition[i] = malloc(symboles * sizeof(int));    // pour chaque lignes de la matrice
        for (int j = 0; j < symboles; j++) {
            fsm->matrice_transition[i][j] = -1;    // valeur par défaut pour chaque élément de la matrice à -1 
        }
    }
    return fsm;    // retourne un pointeur vers la nouvelle instance de la structure FiniteStateMachine
}

// Fonction pour saisir les transitions de chaque état et symbole de la fsm créée
void saisieFSM(FiniteStateMachine *fsm) {
    printf("Entrer les transitions pour chaque état et symbole :\n");
    // lit chaque état de la fsm en utilisant la variable nombre_etats de la structure
    for (int i = 0; i < fsm->nombre_etats; i++) {
        // lit chaque symbole de la fsm en utilisant la variable nombre_symboles de la structure
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            printf("Transition de l'état %d avec le symbole %d: ", i, j);    // l'utilisateur doit saisir la transition pour chaque état i et symbole j
            scanf("%d", &fsm->matrice_transition[i][j]);    // applique ces transitions dans la variable matrice_transition de la structure
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
