#include <stdio.h>
#include"dfa.h"
#include<stdlib.h>
#include  <string.h>



struct DFA{
    int nstates;
    int** table;
    bool* accept;
};

/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA* new_DFA(int nstates) {
    DFA* object = (DFA*)malloc(sizeof(struct DFA));
    if (object != NULL) {
        object->nstates = nstates;
        object->table = (int**)calloc(nstates, sizeof(int*));
        
        for (int i =0; i < nstates; i++){
            object->table[i] = (int*)calloc(128, sizeof(int));
            for (int j = 0; j<128; j++){
                object->table[i][j] = -1;
            }
        }
    }
    object->accept = (bool*)calloc(nstates,sizeof(bool));
    return object;
}

//Free?

/**
 * Return the number of states in the given DFA->
 */
int DFA_get_size(DFA* dfa){
    return dfa->nstates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym->
 */
int DFA_get_transition(DFA* dfa, int src, char sym){
    return dfa->table[src][(int)sym];
    
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst->
 */
void DFA_set_transition(DFA* dfa, int src, char sym, int dst){
    dfa->table[src][(int)sym] = dst;
}
    
/**
 * Set whether the given DFA's state is accepting or not->
 */
void DFA_set_accepting(DFA* dfa, int state, bool value){
    dfa->accept[state] = value;
}

/**
 * Return true if the given DFA's state is an accepting state->
 */
bool DFA_get_accepting(DFA* dfa, int state){
    return dfa->accept[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false->
 */
bool DFA_execute(DFA* dfa, char *input){
    int current = 0;
    
    for (int i = 0; i<strlen(input);i++){
        current = dfa->table[current][(int)input[i]];
        if (current == -1){
        break;
        }
    }
    if(DFA_get_accepting(dfa, current)){
        return true;
    }else{
        return false;
    }
}
