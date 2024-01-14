// fsm.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // library for boolean
#include "fsm.h"

// Create a new instance of the FiniteStateMachine structure and initialize variables, returning a pointer to this new structure
FiniteStateMachine *creationFSM(int etats, int symboles) {
    FiniteStateMachine *fsm = malloc(sizeof(FiniteStateMachine));    // dynamic memory allocation for the new FiniteStateMachine instance
    // initialize structure variables with the integer values passed as arguments to this function
    fsm->nombre_etats = etats;    
    fsm->nombre_symboles = symboles;
    // dynamic memory allocation for the transition matrix
    fsm->matrice_transition = malloc(etats * sizeof(int *));
    for (int i = 0; i < etats; i++) {
        fsm->matrice_transition[i] = malloc(symboles * sizeof(int));    // for each row of the matrix
        for (int j = 0; j < symboles; j++) {
            fsm->matrice_transition[i][j] = -1;    // default value for each element of the matrix is -1 
        }
    }
    return fsm;    // return a pointer to the new FiniteStateMachine instance
}

// Function to input transitions for each state and symbol of the created fsm
void saisieFSM(FiniteStateMachine *fsm) {
    printf("Entrer les transitions pour chaque état et symbole :\n");
    // read each state of the fsm using the number_states variable of the structure
    for (int i = 0; i < fsm->nombre_etats; i++) {
        // read each symbol of the fsm using the number_symbols variable of the structure
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            printf("Transition de l'état %d avec le symbole %d: ", i, j);    // the user must input the transition for each state i and symbol j
            scanf("%d", &fsm->matrice_transition[i][j]);    // apply these transitions to the transition_matrix variable of the structure
        }
    }
}

// Function to display the transition matrix of the fsm
void afficherFSM(FiniteStateMachine *fsm) {
    printf("Matrice de transition de la FSM :\n");
    // read each state
    for (int i = 0; i < fsm->nombre_etats; i++) {
        // read each symbol for state i
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            // display transition for state i and symbol j
            printf("%d ", fsm->matrice_transition[i][j]);
        }
        // newline after all transitions for a state are displayed
        printf("\n");
    }
}

// Function to save the number of states, the number of symbols, and the transition matrix of a FiniteStateMachine struct to a text file
void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");    // open a text file in write mode "w" and named by the value of the filename argument
    // check if the file opening is successful or not
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");    // message displayed in the console if opening the file fails
        return;
    }
    // fprintf writes the number of states and symbols of the fsm to the file and then moves to a new line for the other data to be written
    fprintf(fichier, "%d %d\n", fsm->nombre_etats, fsm->nombre_symboles);
    // read each state of the fsm
    for (int i = 0; i < fsm->nombre_etats; i++) {
        // read each symbol for state i
        for (int j = 0; j < fsm->nombre_symboles; j++) {
            fprintf(fichier, "%d ", fsm->matrice_transition[i][j]); // write the transition value to the file and add a space
        }
        fprintf(fichier, "\n"); // once all transitions for a state are written, return to a new line to repeat the action for each state
    }
    fclose(fichier);    // once all data is written, close the file
    printf("FSM enregistrée dans le fichier '%s'.\n", nom_fichier);    // message to the user informing that their file is saved
}

// Function to load and read a file and get the fsm data from that file (number of states, number of symbols, and transitions)
void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");    // open a text file in read mode "r"
    // check if the file opening is successful or not
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");    // message displayed in the console if opening the file fails
        return;
    }
    int etats, symboles;
    fscanf(fichier, "%d %d", &etats, &symboles); // read the first line of the file containing the number of states and symbols separated by a space (the loaded file must follow this writing rule)
    *fsm = creationFSM(etats, symboles);    // create a new instance of the fsm from the read number of states and symbols
    // read each state of the fsm
    for (int i = 0; i < etats; i++) {
        // read each symbol for state i
        for (int j = 0; j < symboles; j++) {
            fscanf(fichier, "%d", &(*fsm)->matrice_transition[i][j]); // read the transition value from the file and store it in the transition matrix
        }
    }
    fclose(fichier); // once all data is read from the file and assigned to variables in the new fsm instance, close the file
    printf("FSM chargée depuis le fichier '%s'.\n", nom_fichier);    // message to the user informing that their file is loaded successfully
}

// Function to free the memory allocated to an instance of the FiniteStateMachine struct and its transition matrix
void supprFSM(FiniteStateMachine *fsm) {
    // read each row of the transition matrix
    for (int i = 0; i < fsm->nombre_etats; i++) {
        free(fsm->matrice_transition[i]);    // free the memory allocated for row i of the transition matrix
    }
    free(fsm->matrice_transition);    // free the memory allocated for the transition matrix
    free(fsm);    // free the memory allocated for the FiniteStateMachine structure
    printf("FSM supprimée.\n");    // message to the user informing that the fsm is successfully deleted
}

// Function to check if an fsm is complete or not (Question 3) returning a boolean
bool VerifComplet(FiniteStateMachine *fsm) {    
    int etat, symbole;
    for (etat = 0; etat < fsm->nombre_etats; etat++) {    // read each state of the fsm
        for (symbole = 0; symbole < fsm->nombre_symboles; symbole++) {    // read each symbol for each state of the fsm
            if (fsm->matrice_transition[etat][symbole] == -1) { // -1 represents a missing transition, so if there is at least one missing transition, the function returns false, fsm not complete
                return false;
            }
        }
    }
    return true;    // if after traversing all transitions there is no missing transition, the function returns true, fsm complete
}

// Function to complete the fsm in argument (Question 4) 
void CompleterFSM(FiniteStateMachine *fsm) {
    int etat, symbole;
    for (etat = 0; etat < fsm->nombre_etats; etat++) {    // read each state of the fsm
        for (symbole = 0; symbole < fsm->nombre_symboles; symbole++) {    // read each symbol for each state of the fsm
            if (fsm->matrice_transition[etat][symbole] == -1) {     // If there is a missing transition
                fsm->matrice_transition[etat][symbole] = 0;    // then this transition will take the value 0 
            }
        }
    }
}

// Function to check if a word is recognized by the fsm (Question 2) returning a boolean
bool estReconnu(FiniteStateMachine* fsm, const char* mot) {
    int etatActuel = 0; // Start from the initial state

    for (int i = 0; i < strlen(mot); i++) {    // read each letter of the input word
        int symbole = mot[i] - '0'; // Convert the character to an integer
        // Transition to the next state based on the symbol
        etatActuel = fsm->matrice_transition[etatActuel][symbole];
        if (etatActuel == -1) {
            // Invalid transition, the word is not recognized
            return false;
        }
    }
    // Check if the final state is one of the accepted states
    for (int i = 0; i < fsm->nombre_etats_accepteurs; i++) {
        if (etatActuel == fsm->etats_accepteurs[i]) {
            // The word is recognized
            return true;
        }
    }
    // The word is not recognized
    return false;
}

