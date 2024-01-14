// main.c
// Modifier le Finite State Machine (FSM) et remplacer par Automate d'Etat Finis (AEF)
#include <stdio.h>
#include <stdbool.h> // bibliothèque pour booleen
#include <string.h>    // bibliothèque pour manipulation de caratères et d'allocation mémoire
#include "fsm.h"    // on inclus le fichier .h contenant la structure de données et les prototypes
#include "fsm.c"    // on inclus le fichier .c contenant les définitions de toutes les fonctions utilisées

int main() {   // interface utilisateur via la console pour qu'il détermine son choix entre saisir manuellement la FSM ou l'importer à partir d'un fichier texte
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
        afficherFSM(fsm);    // utilisation fonction affichageFSM (definition dans fsm.h) pour afficher la FSM une fois les saisies terminées
        sauvegardeFSMfichier(fsm, "fsm.txt");    // utilisation fonction saveFSMfichier (definition dans fsm.h) pour sauvegarder cette FSM dans un nouveau fichier texte nommé "fsm.txt"
    } else if (choix == 2) {    // cas choix de l'utilisateur d'importer à partir d'un fichier les propriétés et les valeurs de sa FSM    
        char nom_fichier[50];    // définition d'une variable char d'une taille de 50 caractères (pas besoin de plus) pour le nom du fichier texte qui va être importé
        printf("Entrez le nom du fichier à charger : ");    // saisie de l'utilisateur du nom du fichier texte à importer
        scanf("%s", nom_fichier);    // affectation de la valeur saisie à la variable nom_fichier
        chargerFSMfichier(&fsm, nom_fichier);    // utilisation de la fonction chargerFSMfichier (déclaration dasn fsm.h) pour charger ce fichier texte et la fsm
        afficherFSM(fsm);
        // on devrait demander à l'utilisateur si il est satisfait de sa fsm alors on sauvegarde cette fsm et sinon lui proposer de le modifier et ensuite de save avec sauvegardeFSMfichier
    } else {    // autre cas si l'utilisateur ne saisie pas un choix 1 ou 2
        printf("Choix non valide.\n");    // affichage message d'erreur
        return 1;
    }

    if (VerifComplet(fsm)) {    //appel de la fonction pour vérifier si la fsm est complet, cette fonction retourne un booléen
        printf("L'automate est complet.\n");    // affichage d'un message dans le cas où la fsm est complet
    } else {    // sinon affichage d'un message pour informer l'utilisateur
        printf("L'automate n'est pas complet.\n");
        printf("Souhaitez-vous le rendre complet ? (oui ou non) ");    // demande à l'utilisateur si il veut le compléter
        char answer[3];    // definition d'une variable de 3 caractères
        scanf("%s", answer);    // récupération de la réponse dans la variable char
        if (answer == "oui") {    
            CompleterFSM(fsm);    // appel de la fonction pour compléter la fsm dans le cas où l'utilisateur a répondu oui
            printf("Votre FSM a été complétée avec succès !\n");
            afficherFSM(fsm); // Afficher la FSM complétée
        } else {
            printf("Ok.\n");
        }
    }
    
    printf("Entrez un mot à vérifier : ");    // demande à l'utilisateur d'entrer un mot pour voir si la fsm le reconnait
    char mot[100]; // définition de la variable de 100 caractères max pour le mot à vérifier
    scanf("%s", mot);
    
    if (estReconnu(fsm, mot)) {    // appel fonction pour reconnaitre le mot
        printf("Le mot est reconnu par la FSM.\n");    // message succès
    } else {
        printf("Le mot n'est pas reconnu par la FSM.\n");    // message erreur
    }

    supprFSM(fsm); // suppression de la dsl après toutes les modifications réalisées par l'utilisateur

return 0; }

