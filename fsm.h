// fsm.h

#ifndef FSM_H
#define FSM_H

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
