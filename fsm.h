// fsm.h
// Ce fichier .h (header) contient les prototypes des fonctions de la fsm
// Le fichier fsm.c contient lui les définitions de ces foncions
#ifndef FSM_H    // utilisation de ifndef pour éviter problème si ce fichier de prototype est importé dans plusieurs fichier .h à la fois, ici si la variable FSM_H n'est pas définie alors le header sera inclus sinon il sera vide
#define FSM_H
// définition de cette variavble FSM_H, d'autres solutions à ce problème sont possibles comme #pragma once" mais ne fonctionne qu'avec certains compilateurs

typedef struct {    // définition de la structure FiniteStateMachine à l'aide de typedef car typedef est une écriture moins lourde et plus lisible que 'struct FiniteStateMachgine'
    int nombre_etats;    // définition des variables structurées pour le nombre d'états, le nombre de symboles et un pointeur de pointeur pour la matrice de transition
    int nombre_symboles;
    int **matrice_transition;
} FiniteStateMachine;

FiniteStateMachine *creationFSM(int etats, int symboles);    // la fsm accede à la valeur de l'objet créé par la fonction creationFSM et ses proprités saisies ou importées
void saisieFSM(FiniteStateMachine *fsm);    //   
void affichageFSM(FiniteStateMachine *fsm);
void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier);
void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier);
void supprFSM(FiniteStateMachine *fsm);

#endif // fin de la condition si FSH_H n'est pas définie
