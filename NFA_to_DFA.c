#include <stdio.h>
#include <string.h>
#include  <stdbool.h>
#include"IntHashSet.h"
#include "NFA_to_DFA.h"

#include "dfa.h"
#include "nfa.h"




bool includes(IntHashSet* set, IntHashSet states){
    for (int i = 0; i<9; i++){
        if (IntHashSet_equals(set[i], states)){
            return true;
        }
    }
    return false;
}

DFA* NFA_to_DFA(NFA* nfa){
    IntHashSet* temp = (IntHashSet*)calloc(10, sizeof(IntHashSet));

    for (int i = 0; i<10; i++){
        temp[i] = new_IntHashSet(1);

    }
    
    int place = 0;
    int new_place = 1;
    for (int i = 0; i<128; i++){
        if (includes(temp, nfa->table[0][i])==false){
            temp[place]=nfa->table[0][i];
            place = place + 1;
        }
    }
    while (place>new_place){
    //when final is less than temp
        int check = place;

        for (int i = new_place; i<check; i++){
        //make up the difference
            for (int j = 0; j<128; j++){
            
                IntHashSet theState = new_IntHashSet(1);
                IntHashSetIterator iterator = IntHashSet_iterator(temp[i]);
                while (IntHashSetIterator_hasNext(iterator)) {
                    int element = IntHashSetIterator_next(iterator);
                    //iterate through the hash set
                    IntHashSet_union(theState, nfa->table[element][j]);
                }
                if(iterator != NULL){
                    free(iterator);
                }
                if (includes(temp, theState)==false){
                    temp[place]=theState;
                    place = place + 1; 
                }
            }
        }
        new_place = check;
    }
    DFA* dfa = new_DFA(place);
    return dfa;
}
    
DFA* NFA_got_setup(DFA* dfa){

    DFA_set_accepting(dfa, 4, true);
    DFA_set_accepting(dfa, 5, true);
    DFA_set_accepting(dfa, 3, true);

    DFA_set_transition(dfa, 0, 'g', 1);
    DFA_set_transition(dfa, 1, 'o', 2);
    DFA_set_transition(dfa, 2, 't', 3);
    DFA_set_transition(dfa, 3, 'g', 4);
    DFA_set_transition(dfa, 4, 'g', 4);
    DFA_set_transition(dfa, 4, 'o', 5);
    DFA_set_transition(dfa, 5, 'g', 4);
    DFA_set_transition(dfa, 2, 'g', 1);
    DFA_set_transition(dfa, 1, 'g', 1);
        
    for (int i = 0; i<128; i++){
        if(i!='g' && i!='o' && i!='t'){
            dfa->table[2][i] = 1;
        }
        if(i!='g' && i!='o'){
            dfa->table[1][i] = 0;
            dfa->table[4][i] = 3;
        }
        if (i!='g'){
            dfa->table[0][i] = 0;
            dfa->table[3][i] = 3;
            dfa->table[5][i] = 3;
        }
    }
    return dfa;
}

DFA* NFA_at_setup(DFA* dfa){
    DFA_set_accepting(dfa, 2, true);
    
    DFA_set_transition(dfa, 0, 'a', 1);
    DFA_set_transition(dfa, 1, 'a', 1);
    DFA_set_transition(dfa, 1, 't', 2);
    DFA_set_transition(dfa, 2, 'a', 1);
    
    for (int i = 0; i<128; i++){
        if(i!='a' && i!='t'){
            dfa->table[1][i] = 0;
        }
        if(i!='a'){
            dfa->table[0][i] = 0;
            dfa->table[0][i] = 0;
        }
    }
    return dfa;
}
