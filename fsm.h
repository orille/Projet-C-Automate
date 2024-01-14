// fsm.h
// This header (.h) file contains the prototypes of the fsm functions
// The fsm.c file contains the definitions of these functions
#ifndef FSM_H    // Use of ifndef to avoid issues if this prototype file is included in multiple .h files at the same time; here, if the FSM_H variable is not defined, the header will be included, otherwise, it will be empty.
#define FSM_H
// Definition of the FSM_H variable; other solutions to this problem are possible, such as "#pragma once," but it only works with certain compilers

typedef struct {    // Definition of the FiniteStateMachine structure using typedef because typedef is a less cumbersome and more readable way than 'struct FiniteStateMachine'
    int nombre_etats;    // Definition of structured variables for the number of states, the number of symbols, a pointer to a pointer for the transition matrix, an accepting state count, and an accepting state (for word verification, but we didn't succeed)
    int nombre_symboles; 
    int **matrice_transition;
    int etats_accepteurs;
    int nb_etats_accepteurs;
} FiniteStateMachine;

FiniteStateMachine *creationFSM(int etats, int symboles);    // The creationFSM function will dynamically allocate memory to create an instance of the FiniteStateMachine structure and return a pointer to this instance
void saisieFSM(FiniteStateMachine *fsm);    // The prototype of the saisieFSM function takes a pointer to a created FiniteStateMachine structure as an argument and does not return any value
void afficherFSM(FiniteStateMachine *fsm);    // The prototype of the afficherFSM function takes a pointer to a created FiniteStateMachine structure as an argument and does not return any value
void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier);    // The prototype of the sauvegardeFSMfichier function takes a pointer to a created FiniteStateMachine structure and the name of the text file (constant and not modifiable) that will be created to save this fsm
void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier);    // The prototype of the chargerFSMfichier function takes a pointer to a pointer to a created FiniteStateMachine structure (allows modifying the original pointer to the fsm to dynamically allocate memory for the struct or its data) and the name of the text file (constant and not modifiable) containing the fsm to be loaded
void supprFSM(FiniteStateMachine *fsm);     // The prototype of the supprFSM function takes a pointer to a created FiniteStateMachine structure as an argument and does not return any value
bool VerifComplet(FiniteStateMachine *fsm);        // The prototype of the VerifComplet function takes a pointer to a created FiniteStateMachine structure as an argument and returns a boolean (true or false)
void CompleterFSM(FiniteStateMachine *fsm);    // The prototype of the CompleterFSM function takes a pointer to a created FiniteStateMachine structure as an argument and does not return any value
bool estReconnu(FiniteStateMachine* fsm, const char* mot);    // The prototype of the estReconnu function takes a pointer to a created FiniteStateMachine structure and the word to be recognized as arguments and returns a boolean (true or false)

#endif // End of the condition if FSM_H is not defined
