#include <stdio.h>

#include <stdlib.h>

 

typedef struct {

    int etat_depart;

    char symbole;

    int etat_arrivee;

} Transition;

 

typedef struct {

    int *etats;

    int nombre_etats;

    char *symboles;

    int nombre_symboles;

    Transition *transitions;

    int etat_initial;

    int *etats_finaux;

} AEF;

 

void saisir(AEF *aef) {

    printf("Combien d'états a votre AEF ? ");

    scanf("%d", &(aef->nombre_etats));

 

    aef->etats = malloc(aef->nombre_etats * sizeof(int));

    printf("Entrez les états de votre AEF : ");

    for (int i = 0; i < aef->nombre_etats; i++) {

        scanf("%d", &(aef->etats[i]));

    }

 

    printf("Combien de symboles d'entrée a votre AEF ? ");

    scanf("%d", &(aef->nombre_symboles));

 

    aef->symboles = malloc(aef->nombre_symboles * sizeof(char));

    printf("Entrez les symboles d'entrée de votre AEF : ");

    for (int i = 0; i < aef->nombre_symboles; i++) {

        scanf(" %c", &(aef->symboles[i]));

    }

}

 

void sauvegarder(AEF *aef, char *fichier) {

    FILE *f = fopen(fichier, "w");

    if (f == NULL) {

        perror("Erreur lors de l'ouverture du fichier");

        return;

    }

 

    for (int i = 0; i < aef->nombre_etats; i++) {

        fprintf(f, "%d ", aef->etats[i]);

    }

    fprintf(f, "\n");

 

    for (int i = 0; i < aef->nombre_symboles; i++) {

        fprintf(f, "%c ", aef->symboles[i]);

    }

    fprintf(f, "\n");

 

    fclose(f);

}

 

int main() {

   AEF aef;

   saisir(&aef);

   sauvegarder(&aef, "aef.txt");

}
