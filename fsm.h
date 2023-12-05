// fsm.h

#ifndef FSM_H
#define FSM_H

typedef struct {
    int numberOfStates;
    int numberOfSymbols;
    int **transitionMatrix;
} FiniteStateMachine;

FiniteStateMachine *createFSM(int states, int symbols);
void inputFSM(FiniteStateMachine *fsm);
void printFSM(FiniteStateMachine *fsm);
void saveFSMToFile(FiniteStateMachine *fsm, const char *filename);
void loadFSMFromFile(FiniteStateMachine **fsm, const char *filename);
void deleteFSM(FiniteStateMachine *fsm);

#endif // FSM_H
