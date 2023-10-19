//
//  nfa.c
//  ExampleProject
//
//  Created by apple on 2023/1/29.
//

#include <stdio.h>
#include "nfa.h"
#include<stdlib.h>
//#include "IntHashSet.c"
#include<string.h>



struct NFA{
    IntHashSet** table;
    int nstates;
    bool* accept;
};

NFA* new_NFA(int nstates){
    
    NFA* object = (NFA*)malloc(sizeof(struct NFA));
    if (object != NULL) {
        object->nstates = nstates;
        object->table = (IntHashSet**)calloc(nstates, sizeof(IntHashSet*));
        
        for (int i =0; i < nstates; i++){
            object->table[i] = (IntHashSet*)calloc(128, sizeof(IntHashSet));
            for (int j = 0; j<128; j++){
                object->table[i][j] = new_IntHashSet(1);
                IntHashSet_insert(object->table[i][j], 0);
            }
        }
    }
    object->accept = (bool*)calloc(nstates,sizeof(bool));
    return object;
}

int NFA_get_size(NFA* nfa){
    return nfa->nstates;
}

void NFA_add_transition(NFA* nfa, int src, char sym, int dst){
    IntHashSet_insert(nfa->table[src][(int)sym], dst);
}

void NFA_set_accepting(NFA* nfa, int state, bool value){
    nfa->accept[state] = value;
}

bool NFA_get_accepting(NFA* nfa, int state){
    return nfa->accept[state];
}

bool NFA_execute(NFA* nfa, char *input){
    IntHashSet current_Hash = new_IntHashSet(1);
    IntHashSet temp = new_IntHashSet(1);
    IntHashSet_union(current_Hash, nfa->table[0][(int)input[0]]);

    for (int i = 1; i<strlen(input);i++){
        
        IntHashSetIterator iterator = IntHashSet_iterator(current_Hash);
        while (IntHashSetIterator_hasNext(iterator)) {
            int element = IntHashSetIterator_next(iterator);
            IntHashSet_union(temp, nfa->table[element][(int)input[i]]);
        }
        current_Hash = temp;
        temp = new_IntHashSet(1);
        free(iterator);
    }
    
    for (int i = 0; i<nfa->nstates; i++){
        if (nfa->accept[i] == true){
            if (IntHashSet_lookup(current_Hash, i)){
                return true;
            }
        }
    }
    return false;
}
