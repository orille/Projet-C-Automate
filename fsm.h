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

FiniteStateMachine *creationFSM(int etats, int symboles);    // la fonction creationFSM va allouer dynamiquement de la mémoire pour crééer une instance de la structure FiniteStateMachine et renverra un pointeur vers cette instance 
void saisieFSM(FiniteStateMachine *fsm);    // le prototype de la fonction saisieFSM prend en argument un pointeur vers une strucure FiniteStateMAchine créée et ne retourne aucune valeur   
void affichageFSM(FiniteStateMachine *fsm);    // le prototype de la fonction affichageFSM prend en argument un pointeur vers une strucure FiniteStateMAchine créée et ne retourne aucune valeur 
void sauvegardeFSMfichier(FiniteStateMachine *fsm, const char *nom_fichier);    // le prototype de la fonction sauvegardeFSMfichier prend en argument un pointeur vers une strucure FiniteStateMAchine créée et le nom du fichier texte (constante donc non modifiable) qui sera créée pour sauvegarder cette fsm
void chargerFSMfichier(FiniteStateMachine **fsm, const char *nom_fichier);    // le prototype de la fonction chargerFSMfichier prend en argument un pointeur de pointeur vers une strucure FiniteStateMAchine créée (permet de modifier le pointeur originel vers la fsm pour allouer dynamiquement de la mémoire pour la struct ou ses données) et le nom du fichier texte (constante donc non modifiable) contenant la fsm qui sera chargée
void supprFSM(FiniteStateMachine *fsm);     // le prototype de la fonction supprFSM prend en argument un pointeur vers une strucure FiniteStateMAchine créée et ne retourne aucune valeur   

#endif // fin de la condition si FSH_H n'est pas définie
