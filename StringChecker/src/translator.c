#include "translator.h"

/**
 * Translate an NFA into a DFA
 */
DFA NFA_translator(NFA nfa){
	IntHashSet dfa_states[63];
	for (int i = 0; i < 63; i++){
		dfa_states[i] = new_IntHashSet(NFA_get_size(nfa));
	}
	int dfa_nstates = 0;
	int dfa_trans[63][128];
	bool processed[63];

	// initialize curr states with the initial states of the given nfa
	IntHashSet state = new_IntHashSet(NFA_get_size(nfa));
	IntHashSetIterator tmpIterator = IntHashSet_iterator(NFA_get_s0(nfa));
	int s;
	while (IntHashSetIterator_hasNext(tmpIterator)){
		s = IntHashSetIterator_next(tmpIterator);
		IntHashSet_insert(state, s);
	}
	free(tmpIterator);

	// initialize bool processed[]
	for (int i=0; i<63; i++){
		processed[i]=1;
	}
	processed[dfa_nstates]=0;


	/* calculate possible next states for each alphabet symbol,
	 * given a source set of states
	 */
	bool finished = 0;
	int currState = dfa_nstates;

	while (!finished){

	for (int i=0; (i < 128) && (!IntHashSet_isEmpty(state)); i++){
		IntHashSetIterator iterator = IntHashSet_iterator(state);
		IntHashSet state_next = new_IntHashSet(NFA_get_size(nfa));

		int src;
		while (IntHashSetIterator_hasNext(iterator)){
			src = IntHashSetIterator_next(iterator);
			IntHashSet_insert(dfa_states[currState], src);
			IntHashSet_union(state_next, NFA_get_transitions_byIndex(nfa, src, i));
		}
		free(iterator);
		/* check if state_next is contained in dfa_state[]
		 * if it is contained, set dfa_trans[src][i] = j (i is (int)input_symbol)
		 * if not, add it to dfa_state[], #dfa_nstates++, set dfa_trans[src][i] = dfa_nstates
		 * and set that particular dfa_state to "not processed"
		 */
		bool contain = 0;
		for (int j=0; j < dfa_nstates+1; j++){
			if (IntHashSet_equals(dfa_states[j], state)){ // set curr state to "processed"
				src = j;
				processed[src] = 1;
			}
			if (IntHashSet_equals(dfa_states[j], state_next)){
				contain = 1;
				dfa_trans[src][i] = j;
			}
		}
		if (!contain){
			dfa_nstates++;
			dfa_trans[src][i] = dfa_nstates;
			IntHashSetIterator tmpIterator2 = IntHashSet_iterator(state_next);
			while (IntHashSetIterator_hasNext(tmpIterator2)){
				s = IntHashSetIterator_next(tmpIterator2);
				IntHashSet_insert(dfa_states[dfa_nstates], s); // add state_next to dfa_state[]
			}
			free(tmpIterator2);
			processed[dfa_nstates] = 0; // since state_next is a new possible set of states, it is not processed
		}
		IntHashSet_free(state_next);
	}

	/* check if every dfa_state[] is processed
	 * if one of them is not processed, the translation process is not finished,
	 * so we proceed to process that set of states
	 * if all of them are processed, then we have finished translate the given nfa to dfa
	 */
	finished = 1;
	for (int i=0; i < dfa_nstates+1; i++){
		if (!processed[i]){
			currState = i;
			finished = 0;
			IntHashSet_free(state);
			state = new_IntHashSet(NFA_get_size(nfa));
			IntHashSetIterator iterator2 = IntHashSet_iterator(dfa_states[i]);
			while (IntHashSetIterator_hasNext(iterator2)){
			  s = IntHashSetIterator_next(iterator2);
			  IntHashSet_insert(state, s);
			}
			free(iterator2);
			break;
		}
	}
	if (finished){ // if finished translating, free state
		IntHashSet_free(state);
	}

	} // end of while loop


	// copy the result dfa transition table to the new dfa
	DFA dfa = new_DFA(dfa_nstates+1);
	for (int i = 0; i < dfa_nstates+1; i++){
		for (int j = 0; j< 128; j++){
			DFA_set_transition(dfa, i, j, (char)dfa_trans[i][j]);
		}
		/* check if i-th set of possible states includes any accepting state
		 * if includes, set i state in dfa to accepting state
		 */
		IntHashSetIterator iterator = IntHashSet_iterator(dfa_states[i]);
		while (IntHashSetIterator_hasNext(iterator)){
			int src = IntHashSetIterator_next(iterator);
			if (NFA_get_accepting(nfa, src)){
				DFA_set_accepting(dfa, i, 1);
			}
		}
		free(iterator);
	}

	for (int i = 0; i < 63; i++){
		IntHashSet_free(dfa_states[i]);
	}
	NFA_free(nfa);
	return dfa;
}
