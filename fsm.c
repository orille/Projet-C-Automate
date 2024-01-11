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

// Fonction pour afficher la matrice de transition de la fsm
void affichageFSM(FiniteStateMachine *fsm) {
    printf("Matrice de transition de la FSM :\n");
    // lit chaque état
    for (int i = 0; i < fsm->nombre_etats; i++) {
        // lit chaque symbole pour l'état i
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            // affiche transition pour état i et symbole j
            printf("%d ", fsm->matrice_transition[i][j]);
        }
        // retour ligne apres toutes les transitions d'un état affichées
        printf("\n");
    }
}

// Fonction pour sauvegarder le nombre d'états, le nombre de symboles et la matrice de transition d'une struct FiniteStateMachine dans un fichier txt
void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");    // ouverture d'un fichier texte en mode écriture "w" et nommé par la valeur l'argument nom_fichier
    // test pour savoir si l'ouverture du fichier est un succès ou non
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");    // message affiché dans la console si échec lors de l'ouverture du fichier
        return;
    }
    // fprintf permet d'écrire dans le fichier le nombre d'états et de symboles de la fsm et ensuite de passer à une nouvelle ligne pour les autres données en écrire
    fprintf(fichier, "%d %d\n", fsm->nombre_etats, fsm->nombre_symboles);
    // lit chaque état de la fsm
    for (int i = 0; i < fsm->nombre_etats; i++) {
        // lit chaque symbole pour l'état i
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            fprintf(fichier, "%d ", fsm->matrice_transition[i][j]); // écrit la valeur de la transition dans le fichier et ajoute un espace
        }
        fprintf(fichier, "\n"); // une fois toutes les transitions d'un état écrites retour à une nouvelle ligne pour répéter l'action pour chaque état
    }
    fclose(fichier);    // une fois toutes les données écrites fermeture du fichier
    printf("FSM enregistrée dans le fichier '%s'.\n", nom_fichier);    // message à l'utilisateur pour l'informer que son fichier est sauvegardé
}

// Fonction pour charger et lire un fichier et obtenir les données de la fsm contenue dans ce fichier (nb états, nb symboles et transitions)
void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier) {
    FICHIER *fichier = fopen(nom_fichier, "r");    // ouverture d'un fichier texte en mode lecture "r"
    // test pour savoir si l'ouverture du fichier est un succès ou non
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");    // message affiché dans la console si échec lors de l'ouverture du fichier
        return;
    }
    int etats, symboles;
    fscanf(fichier, "%d %d", &etats, &symboles); // lit la première ligne du fichier contenant le nombre d'états et de symboles séparés par un espace (le fichier chargé doit donc respecter cette regle d'écriture)
    *fsm = creationFSM(etats, symboles);    // création donc d'une nouvelle instance de la fsm à partir des nb états et symboles lus
    // lit chaque état de la fsm
    for (int i = 0; i < etats; i++) {
        // lit chaque symbole pour l'état i
        for (int j = 0; j < symboles; j++) {
            fscanf(fichier, "%d", &(*fsm)->matrice_transition[i][j]); // lecture valeur de la transition dans le fichier et stockage de cette valeur dans la matrice de transition
        }
    }
    fclose(fichier); // une fois toutes les données lues à partir du fichier et affectées aux variables à la nouvelle instance de la fsm on ferme le fichier
    printf("FSM chargée depuis le fichier '%s'.\n", nom_fichier);    // message à l'utilisateur pour l'informer que son fichier est bien chargé
}

// Fonction pour libérer la mémoire allouée à une instance de la struct FiniteStateMachine et sa matrice de transition
void supprFSM(FiniteStateMachine *fsm) {
    // lit chaque ligne de la matrice de transition
    for (int i = 0; i < fsm->nombre_etats; i++) {
        free(fsm->matrice_transition[i]);    // libération de la mémoire allouée à la ligne i de la matrice de transition
    }
    free(fsm->matrice_transition);    // libèration de la mémoire allouée à la matrice de transition
    free(fsm);    // libération de la mémoire allouée à la structure FiniteStateMachine
    printf("FSM supprimée.\n");    // message à l'utilisateur pour l'informer que la fsm est bien supprimée
}
