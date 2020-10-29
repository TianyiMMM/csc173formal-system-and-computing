/*
 * File: nfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:54:41 2016
 * Time-stamp: <Tue Aug  8 11:45:49 EDT 2017 ferguson>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "IntHashSet.h"
#include "dfa.h"
#include "nfa.h"


/**
 * The data structure used to represent a nondeterministic finite automaton.
 * @see FOCS Section 10.3
 * @see Comments for DFA in dfa.h
 */
struct NFA {
	int nstates;
	IntHashSet trans[63][128];
	IntHashSet s0;
	bool acc[63];
};


/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nstates){
	NFA this = (NFA)malloc(sizeof(struct NFA));
	this->nstates = nstates;
	for (int i = 0; i < nstates; i++){
		this->acc[i]=0;
		for (int j = 0; j< 128; j++){
			this->trans[i][j] = new_IntHashSet(nstates);
		}
	}
	this->s0 = new_IntHashSet(nstates);
	IntHashSet_insert(this->s0, 0);
	return this;
}


/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa){
	if (nfa == NULL) {
		return;
	}
	IntHashSet_free(nfa->s0);
	for (int i = 0; i < nfa->nstates; i++){
		for (int j = 0; j< 128; j++){
			IntHashSet_free(nfa->trans[i][j]);
		}
	}
	free(nfa);
}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa){
	return nfa->nstates;
}

/**
 * Return set of initial states in the given NFA.
 */
IntHashSet NFA_get_s0(NFA nfa){
	return nfa->s0;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
IntHashSet NFA_get_transitions(NFA nfa, int state, char sym){
	int index = (int)sym;
	IntHashSet dst = nfa->trans[state][index];
	return dst;
}

IntHashSet NFA_get_transitions_byIndex(NFA nfa, int state, int index){
	return nfa->trans[state][index];
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
	//printf("NFA_add_transition(%d, %c, %d)\n", src, sym, dst);
	int index = (int)sym;
	IntHashSet_insert(nfa->trans[src][index], dst);
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
	for (int i=0; i < strlen(str); i++)
		NFA_add_transition(nfa, src, str[i], dst);
}

/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst){
	//printf("NFA_add_transition_all(%d, %d)\n", src, dst);
	for (int j = 0; j < 128; j++){
		IntHashSet_insert(nfa->trans[src][j], dst);
	}
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value){
	nfa->acc[state] = value;
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state){
	return nfa->acc[state];
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input){
	// initialize curr states with the initial states of the given nfa
	IntHashSet state = new_IntHashSet(nfa->nstates);
	IntHashSetIterator tmpIterator = IntHashSet_iterator(nfa->s0);
	int s;
	while (IntHashSetIterator_hasNext(tmpIterator)){
		s = IntHashSetIterator_next(tmpIterator);
		IntHashSet_insert(state, s);
	}
	free(tmpIterator);

	bool sol = 0;

	// calculate the final set of possible states
	for (int i=0; (i < strlen(input)) && (!IntHashSet_isEmpty(state)); i++){
		IntHashSetIterator iterator = IntHashSet_iterator(state);
		IntHashSet state_next = new_IntHashSet(nfa->nstates);
		int src;
		while (IntHashSetIterator_hasNext(iterator)){
			src = IntHashSetIterator_next(iterator);
			IntHashSet_union(state_next, NFA_get_transitions(nfa, src, input[i]));
		}
		free(iterator);
		IntHashSet_free(state);
		state = new_IntHashSet(nfa->nstates);
		IntHashSetIterator iterator2 = IntHashSet_iterator(state_next);
		while (IntHashSetIterator_hasNext(iterator2)){
		  src = IntHashSetIterator_next(iterator2);
		  IntHashSet_insert(state, src);
		}
		free(iterator2);
		IntHashSet_free(state_next);
	}

	// check if the final set of possible states includes any accepting state
	IntHashSetIterator iterator = IntHashSet_iterator(state);
	while (IntHashSetIterator_hasNext(iterator)){
		int src = IntHashSetIterator_next(iterator);
		//printf("%d ", src);
		if (NFA_get_accepting(nfa, src)){
			sol = 1;
		}
	}
	free(iterator);
	IntHashSet_free(state);

	return sol;
}

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa){
	for (int i = 0; i < nfa->nstates; i++){
		for (int j = 0; j < 128; j++){
			if (!IntHashSet_isEmpty(nfa->trans[i][j])){
				printf("%d", i);
				printf("%s", ", ");
				printf("%c", (char)j);
				printf("%s", ": ");
				char* str = IntHashSet_toString(nfa->trans[i][j]);
				printf("%s", str);
				free(str);
				printf("%s", "\n");
			}
		}
	}
}



