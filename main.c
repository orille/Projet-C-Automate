// main.c
// Modifier le Finite State Machine (FSM) et remplacer par Automate d'Etat Finis (AEF)
#include <stdio.h>
#include "fsm.h"

int main() {    // interface utilisateur via la console pour qu'il détermine son choix entre saisir manuellement la FSM ou l'importer à partir d'un fichier texte
    int choix;
    printf("Choisir une option :\n");
    printf("1. Saisir une nouvelle FSM\n");
    printf("2. Charger une FSM depuis un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choix);    // récupération du choix de l'utilisateur 

    FiniteStateMachine *fsm; // déclaration du pointeur pour la fsm

    if (choix == 1) {    // cas choix de l'utilisateur de saisir les propriétés et les valeurs de sa FSM
        int etats, symboles;    // déclaration des variables de type integer pour le nombre d'états et de symboles de la fsm
        printf("Nombre d'états : ");    // saisie de l'utilisateur du nombre d'état
        scanf("%d", &etats);            // modifie la variable etats            
        printf("Nombre de symboles : ");    // saisie de l'utilisateur du nombre de symboles
        scanf("%d", &symboles);    // modifie la variable symboles

        fsm = creationFSM(etats, symboles); // utilisation de la fonction creationFSM (definition cf fsm.h) pour crééer la FSM avec les propriétés (etats et symboles) saisies par l'utilisateur
        saisieFSM(fsm);    // utilisation fonction saisieFSM (definition dans fsm.h) pour saisir les valeurs de la FSM
        affichageFSM(fsm);    // utilisation fonction affichageFSM (definition dans fsm.h) pour afficher la FSM une fois les saisies terminées
        savegardeFSMfichier(fsm, "fsm.txt");    // utilisation fonction saveFSMfichier (definition dans fsm.h) pour sauvegarder cette FSM dans un nouveau fichier texte nommé "fsm.txt"
    } else if (choix == 2) {
        char nom_fichier[100];
        printf("Entrez le nom du fichier à charger : ");
        scanf("%s", nom_fichier);
        chargerFSMfichier(&fsm, nom_fichier);
        afficherFSM(fsm);
    } else {
        printf("Choix non valide.\n");
        return 1;
    }

    supprFSM(fsm);
    return 0;
}
