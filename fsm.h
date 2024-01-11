// fsm.h
// Ce fichier .h (header) contient les prototypes des fonctions de la fsm
// Le fichier fsm.c contient lui les définitions de ces foncions
#ifndef FSM_H    // utilisation de ifndef pour éviter problème si ce fichier de prototype est importé dans plusieurs fichier .h à la fois, ici si la variable FSM_H n'est pas définie alors le header sera inclus sinon il sera vide
#define FSM_H
// définition de cette variavble FSM_H, d'autres solutions à ce problème sont possibles comme #pragma once" mais ne fonctionne qu'avec certains compilateurs

typedef struct {
    int nombre_etats;
    int nombre_symboles;
    int **matrice_transition;
} FiniteStateMachine;

FiniteStateMachine *creationFSM(int etats, int symboles);
void saisieFSM(FiniteStateMachine *fsm);
void affichageFSM(FiniteStateMachine *fsm);
void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier);
void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier);
void supprFSM(FiniteStateMachine *fsm);

#endif // FSM_H
