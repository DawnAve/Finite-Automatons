#ifndef _NFA_to_DFA_h
#define _NFA_to_DFA_h

#include "dfa.h"
#include "nfa.h"

extern bool includes(IntHashSet* set, IntHashSet states);
extern DFA* NFA_to_DFA(NFA* nfa);
extern DFA* NFA_got_setup(DFA* dfa);
extern DFA* NFA_at_setup(DFA* dfa);

#endif
