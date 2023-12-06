#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ETATS 100
#define MAX_SYMBOLES 256  // Nombre maximum de symboles (caractères ASCII)

typedef struct {
    int nombreEtats;
    int nombreSymboles;
    int **matriceTransition;
} AutomateEtatsFinis;

// Créer un nouvel AEF
AutomateEtatsFinis *creerAEF(int etats, int symboles) {
    AutomateEtatsFinis *aef = malloc(sizeof(AutomateEtatsFinis));
    aef->nombreEtats = etats;
    aef->nombreSymboles = symboles;
    aef->matriceTransition = malloc(etats * sizeof(int *));
    for (int i = 0; i < etats; i++) {
        aef->matriceTransition[i] = malloc(symboles * sizeof(int));
        for (int j = 0; j < symboles; j++) {
            aef->matriceTransition[i][j] = -1; // -1 indique qu'il n'y a pas de transition
        }
    }
    return aef;
}

// Saisir les transitions de l'AEF
void saisirTransitionsAEF(AutomateEtatsFinis *aef) {
    printf("Entrer les transitions pour chaque état et symbole :\n");
    for (int i = 0; i < aef->nombreEtats; i++) {
        for (int j = 0; j < aef->nombreSymboles; j++) {
            printf("Transition de l'état %d avec le symbole '%c' : ", i, j);
            int etatSuivant;
            scanf("%d", &etatSuivant);
            aef->matriceTransition[i][j] = etatSuivant;
        }
    }
}

// Afficher la matrice de transition de l'AEF
void afficherAEF(AutomateEtatsFinis *aef) {
    printf("Matrice de transition de l'AEF :\n");
    for (int i = 0; i < aef->nombreEtats; i++) {
        for (int j = 0; j < aef->nombreSymboles; j++) {
            printf("%d ", aef->matriceTransition[i][j]);
        }
        printf("\n");
    }
}

// Enregistrer l'AEF dans un fichier
void sauvegarderAEF(AutomateEtatsFinis *aef, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(fichier, "%d %d\n", aef->nombreEtats, aef->nombreSymboles);
    for (int i = 0; i < aef->nombreEtats; i++) {
        for (int j = 0; j < aef->nombreSymboles; j++) {
            fprintf(fichier, "%d ", aef->matriceTransition[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
    printf("AEF enregistré dans le fichier '%s'.\n", nomFichier);
}

// Charger l'AEF depuis un fichier
void chargerAEFDepuisFichier(AutomateEtatsFinis **aef, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int etats, symboles;
    fscanf(fichier, "%d %d", &etats, &symboles);
    *aef = creerAEF(etats, symboles);
    for (int i = 0; i < etats; i++) {
        for (int j = 0; j < symboles; j++) {
            fscanf(fichier, "%d", &(*aef)->matriceTransition[i][j]);
        }
    }
    fclose(fichier);
    printf("AEF chargé depuis le fichier '%s'.\n", nomFichier);
}

// Supprimer l'AEF
void supprimerAEF(AutomateEtatsFinis *aef) {
    for (int i = 0; i < aef->nombreEtats; i++) {
        free(aef->matriceTransition[i]);
    }
    free(aef->matriceTransition);
    free(aef);
    printf("AEF supprimé.\n");
}

// Vérifier si un mot est reconnu par l'AEF
int motReconnuParAEF(AutomateEtatsFinis *aef, const char *mot) {
    int etatCourant = 0;

    for (int i = 0; i < strlen(mot); i++) {
        int symbole = (int)mot[i];
        if (symbole < 0 || symbole >= MAX_SYMBOLES || aef->matriceTransition[etatCourant][symbole] == -1) {
            return 0; // Transition non valide, mot non reconnu
        }
        etatCourant = aef->matriceTransition[etatCourant][symbole];
    }

    // Ajouter ici la logique pour vérifier si etatCourant est un état acceptant
    // Retourner 1 (vrai) si l'état est acceptant, sinon 0 (faux)
    // Pour l'instant, nous supposons que le dernier état est l'état acceptant
    return etatCourant == aef->nombreEtats - 1;
}

int main() {
    int choix;
    printf("Choisir une option :\n");
    printf("1. Saisir un nouvel AEF\n");
    printf("2. Charger un AEF depuis un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    AutomateEtatsFinis *aef;

    if (choix == 1) {
        int etats, symboles;
        printf("Nombre d'états : ");
        scanf("%d", &etats);
        printf("Nombre de symboles : ");
        scanf("%d", &symboles);

        aef = creerAEF(etats, symboles);
        saisirTransitionsAEF(aef);
        afficherAEF(aef);
        sauvegarderAEF(aef, "aef.txt");
    } else if (choix == 2) {
        char nomFichier[100];
        printf("Entrez le nom du fichier à charger : ");
        scanf("%s", nomFichier);
        chargerAEFDepuisFichier(&aef, nomFichier);
        afficherAEF(aef);
    } else {
        printf("Choix non valide.\n");
        return 1;
    }

    char mot[100];
    printf("Entrez un mot pour le tester avec l'AEF : ");
    scanf("%s", mot);
    if (motReconnuParAEF(aef, mot)) {
        printf("Le mot '%s' est reconnu par l'AEF.\n", mot);
    } else {
        printf("Le mot '%s' n'est pas reconnu par l'AEF.\n", mot);
    }

    supprimerAEF(aef);
    return 0;
}
