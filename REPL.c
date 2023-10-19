#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "NFA_to_DFA.h"
#include "IntHashSet.h"
#include  <stdbool.h>

DFA* DFA_for_CSC(){
    DFA* CSC = new_DFA(4);
    DFA_set_accepting(CSC, 3, true);
    DFA_set_transition(CSC, 0, 'C', 1);
    DFA_set_transition(CSC, 1, 'S', 2);
    DFA_set_transition(CSC, 2, 'C', 3);
    return CSC;
}

DFA* DFA_for_end(){
    DFA* end = new_DFA(4);
    for (int j = 0; j<128; j++){
        end->table[0][j] = 0;
        end->table[1][j] = 0;
        end->table[2][j] = 0;
        end->table[3][j] = 3;
    }
    DFA_set_accepting(end, 3, true);
    DFA_set_transition(end, 0, 'e', 1);
    DFA_set_transition(end, 1, 'n', 2);
    DFA_set_transition(end, 1, 'e', 1);
    DFA_set_transition(end, 2, 'd', 3);
    DFA_set_transition(end, 2, 'e', 1);
    return end;
}

DFA* DFA_for_vowel(){
    DFA* vowel = new_DFA(2);
    for (int j = 0; j<128; j++){
        vowel->table[1][j] = 1;
    }
    DFA_set_accepting(vowel, 1, true);
    DFA_set_transition(vowel, 0, 'a', 1);
    DFA_set_transition(vowel, 0, 'e', 1);
    DFA_set_transition(vowel, 0, 'i', 1);
    DFA_set_transition(vowel, 0, 'o', 1);
    DFA_set_transition(vowel, 0, 'u', 1);
    DFA_set_transition(vowel, 0, 'A', 1);
    DFA_set_transition(vowel, 0, 'E', 1);
    DFA_set_transition(vowel, 0, 'I', 1);
    DFA_set_transition(vowel, 0, 'O', 1);
    DFA_set_transition(vowel, 0, 'U', 1);
    return vowel;
}

DFA* DFA_for_even(){
    DFA* even = new_DFA(4);
    DFA_set_accepting(even, 0, true);
    DFA_set_transition(even, 0, '0', 1);
    DFA_set_transition(even, 0, '1', 2);
    DFA_set_transition(even, 1, '1', 3);
    DFA_set_transition(even, 1, '0', 0);
    DFA_set_transition(even, 3, '1', 1);
    DFA_set_transition(even, 3, '0', 2);
    DFA_set_transition(even, 2, '0', 3);
    DFA_set_transition(even, 2, '1', 0);
    return even;
}

void DFA_repl(DFA* dfa){
    char input[100];
    
    printf("Enter an input (\"quit\" to quit): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    
    
    while(strcmp (input, "quit")!=0){
        bool flag =DFA_execute(dfa, (char*)input);
        const char* output = "false";
        if (flag){
            output = "true";
        }
        
        printf("Result for input \"%s\" is: %s\n", input, output);
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
    }
}

NFA* NFA_for_at(){
    NFA* at = new_NFA(3);
    
    NFA_set_accepting(at, 2, true);
    NFA_add_transition(at, 0, 'a', 1);
    NFA_add_transition(at, 1, 't', 2);
    //state 0
    for (int i = 0; i<128; i++){
        IntHashSet_insert(at->table[0][i], 0);
    }
    return at;
}

NFA* NFA_for_got(){
    NFA* got = new_NFA(4);
    NFA_set_accepting(got, 3,true);
    NFA_add_transition(got, 0, 'g', 1);
    NFA_add_transition(got, 1, 'o', 2);
    NFA_add_transition(got, 2, 't', 3);
    for (int i = 0; i<128; i++){
        IntHashSet_insert(got->table[0][i], 0);
        IntHashSet_insert(got->table[3][i], 3);
    }
    return got;
}

NFA* NFA_for_partC(){
    NFA* partC = new_NFA(17);
    NFA_set_accepting(partC, 2, true);
    NFA_set_accepting(partC, 4, true);
    NFA_set_accepting(partC, 6, true);
    NFA_set_accepting(partC, 8, true);
    NFA_set_accepting(partC, 10, true);
    NFA_set_accepting(partC, 13, true);
    NFA_set_accepting(partC, 16, true);
    
    NFA_add_transition(partC, 0, 'a', 1);
    NFA_add_transition(partC, 1, 'a', 2);
    NFA_add_transition(partC, 0, 'e', 3);
    NFA_add_transition(partC, 3, 'e', 4);
    NFA_add_transition(partC, 0, 'h', 5);
    NFA_add_transition(partC, 5, 'h', 6);
    NFA_add_transition(partC, 0, 'i', 7);
    NFA_add_transition(partC, 7, 'i', 8);
    NFA_add_transition(partC, 0, 'g', 9);
    NFA_add_transition(partC, 9, 'g', 10);
    NFA_add_transition(partC, 0, 'n', 11);
    NFA_add_transition(partC, 11, 'n', 12);
    NFA_add_transition(partC, 12, 'n', 13);
    NFA_add_transition(partC, 0, 'p', 14);
    NFA_add_transition(partC, 14, 'p', 15);
    NFA_add_transition(partC, 15, 'p', 16);
    
    for (int i = 0; i<128; i++){
        IntHashSet_insert(partC->table[0][i], 0);
        IntHashSet_insert(partC->table[2][i], 2);
        IntHashSet_insert(partC->table[4][i], 4);
        IntHashSet_insert(partC->table[6][i], 6);
        IntHashSet_insert(partC->table[8][i], 8);
        IntHashSet_insert(partC->table[10][i], 10);
        IntHashSet_insert(partC->table[13][i], 13);
        IntHashSet_insert(partC->table[16][i], 16);
        if(i != 'a'){
            IntHashSet_insert(partC->table[1][i], 1);
        }
        if(i != 'e'){
            IntHashSet_insert(partC->table[3][i], 3);
        }
        if(i != 'h'){
            IntHashSet_insert(partC->table[5][i], 5);
        }
        if(i != 'i'){
            IntHashSet_insert(partC->table[7][i], 7);
        }
        if(i != 'g'){
            IntHashSet_insert(partC->table[9][i], 9);
        }
        if(i != 'n'){
            IntHashSet_insert(partC->table[11][i], 11);
            IntHashSet_insert(partC->table[12][i], 12);
        }
        if(i != 'p'){
            IntHashSet_insert(partC->table[14][i], 14);
            IntHashSet_insert(partC->table[15][i], 15);
        }
    }
    return partC;
}

void NFA_repl(NFA* nfa){
    char input[100];
    
    printf("Enter an input (\"quit\" to quit): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    
    
    while(strcmp (input, "quit")!=0){
        bool flag =NFA_execute(nfa, (char*)input);
        const char* output = "false";
        if (flag){
            output = "true";
        }
        
        printf("Result for input \"%s\" is: %s\n", input, output);
        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
    }
}


int main(){
    
    //DFA
    printf("Testing DFA that recognizes only CSC\n");
    DFA* CSC = DFA_for_CSC();
    DFA_repl(CSC);
    printf("Testing DFA that recognizes sequnce of end\n");
    DFA* end = DFA_for_end();
    DFA_repl(end);
    printf("Testing DFA that recognizes string that starts with a vowel\n");
    DFA* vowel = DFA_for_vowel();
    DFA_repl(vowel);
    printf("Testing DFA that recognizes even number of 0's and 1's\n");
    DFA* even = DFA_for_even();
    DFA_repl(even);
    //NFA
    printf("Testing NFA that recognizes ending in \"at\"\n");
    NFA* at = NFA_for_at();
    NFA_repl(at);
    
    printf("Testing NFA that recognizes containing \"got\"\n");
    NFA* got = NFA_for_got();
    NFA_repl(got);
    
    printf("Testing NFA that recognizes part C\n");
    NFA* partC = NFA_for_partC();
    NFA_repl(partC);
    
    printf("Testing DFA transformed from NFA_at\n");
    DFA* NFA_1 = NFA_to_DFA(at);
    NFA_1 = NFA_at_setup(NFA_1);
    DFA_repl(NFA_1);
    
    printf("Testing DFA transformed from NFA_got\n");
    DFA* NFA_2 = NFA_to_DFA(got);
    NFA_2 = NFA_got_setup(NFA_2);
    DFA_repl(NFA_2);
    return 0;
}
