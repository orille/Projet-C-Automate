// main.c
#include <stdio.h>
#include <stdbool.h> // Boolean library
#include <string.h>    // String manipulation and memory allocation library
#include "fsm.h"    // Include the .h file containing the data structure and prototypes
#include "fsm.c"    // Include the .c file containing the definitions of all used functions

int main() {   // User interface via the console to determine their choice between entering the FSM manually or importing it from a text file
    int choix;
    printf("Choisir une option :\n");
    printf("1. Saisir une nouvelle FSM\n");
    printf("2. Charger une FSM depuis un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choix);    // User's choice retrieval 
    
    FiniteStateMachine *fsm; // FSM pointer declaration
    if (choix == 1) {    // User's choice to enter the properties and values of their FSM manually
        int etats, symboles;    // Integer variable declaration for the number of states and symbols of the FSM
        printf("Nombre d'états : ");    // User enters the number of states
        scanf("%d", &etats);            // Modify the states variable             
        printf("Nombre de symboles : ");    // User enters the number of symbols
        scanf("%d", &symboles);    // Modify the symbols variable

        fsm = creationFSM(etats, symboles); // Use the creationFSM function (definition in fsm.h) to create the FSM with the properties (states and symbols) entered by the user
        saisieFSM(fsm);    // Use the saisieFSM function (definition in fsm.h) to enter the values of the FSM
        afficherFSM(fsm);    // Use the affichageFSM function (definition in fsm.h) to display the FSM once the entries are completed
        sauvegardeFSMfichier(fsm, "fsm.txt");    // Use the saveFSMfichier function (definition in fsm.h) to save this FSM in a new text file named "fsm.txt"
    } else if (choix == 2) {    // User's choice to import the properties and values of their FSM from a file  
        char nom_fichier[50];    // Definition of a char variable with a size of 50 characters (no need for more) for the name of the text file to be imported
        printf("Entrez le nom du fichier à charger : ");    // User enters the name of the text file to be imported
        scanf("%s", nom_fichier);    // Assign the entered value to the file_name variable
        chargerFSMfichier(&fsm, nom_fichier);    // Use the chargerFSMfichier function (declaration in fsm.h) to load this text file and the FSM
        afficherFSM(fsm);
        // We should ask the user if they are satisfied with their FSM, then save it. If not, offer to modify it, and then save it with sauvegardeFSMfichier.
    } else {    // Another case if the user does not enter choice 1 or 2
        printf("Choix non valide.\n");    // Error message display
        return 1;
    }

    if (VerifComplet(fsm)) {    // Call the function to check if the FSM is complete; this function returns a boolean
        printf("L'automate est complet.\n");    // Display a message in case the FSM is complete
    } else {    // Otherwise, display a message to inform the user
        printf("L'automate n'est pas complet.\n");
        printf("Souhaitez-vous le rendre complet ? (oui ou non) ");    // Ask the user if they want to complete it
        char answer[3];    // Definition of a variable with 3 characters
        scanf("%s", answer);    // Retrieve the response in the char variable
        if (answer == "oui") {    
            CompleterFSM(fsm);    // Call the function to complete the FSM if the user answered oui/yes
            printf("Votre FSM a été complétée avec succès !\n");
            afficherFSM(fsm); // Display the completed FSM
        } else {
            printf("Ok.\n");
        }
    }
    
    printf("Entrez un mot à vérifier : ");    // Ask the user to enter a word to see if the FSM recognizes it
    char mot[100]; // Definition of the variable with a maximum of 100 characters for the word to be verified
    scanf("%s", mot);
    
    if (estReconnu(fsm, mot)) {    // Call the function to recognize the word
        printf("Le mot est reconnu par la FSM.\n");    // Success message
    } else {
        printf("Le mot n'est pas reconnu par la FSM.\n");    // Error message
    }

    supprFSM(fsm); // Deletion of the FSM after all modifications made by the user

return 0; }

