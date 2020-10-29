/*
 * File: dfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:45:52 2016
 * Time-stamp: <Tue Aug  8 11:30:46 EDT 2017 ferguson>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "dfa.h"

/**
 * The data structure used to represent a deterministic finite automaton.
 * @see FOCS Section 10.2
 * Note that YOU must specify this data structure, although you can hide
 * (encapsulate) its implementation behind the declared API functions and
 * only provide a partial declaration in the header file.
 */

struct DFA {
	int nstates;
	int trans[63][128];
	int s0;
	bool acc[63];
};

/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA new_DFA(int nstates){
	DFA this = (DFA)malloc(sizeof(struct DFA));
	this->nstates = nstates;

	for (int i = 0; i < nstates; i++){
		this->acc[i]=0;
		for (int j = 0; j< 128; j++){
			this->trans[i][j] = -1;
		}
	}
	this->s0 = 0;
	return this;
}


/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa){
	if (dfa == NULL) {
		return;
	}
	free(dfa);
}

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa){
	return dfa->nstates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 *
 * iterate through each possible transition from state src
 * if the transition symbol matches sym, return #next state
 * else, move on to the next possible transition
 * return NULL if there is no possible destination state
 */
int DFA_get_transition(DFA dfa, int src, char sym){
	int index = (int)sym;
	int dst = dfa->trans[src][index];
	return dst;
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst){
	int index = (int)sym;
	dfa->trans[src][index] = dst;
}

void DFA_set_transition_byIndex(DFA dfa, int src, int sym, int dst){
	dfa->trans[src][sym] = dst;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){
	for (int i=0; i < strlen(str); i++)
		DFA_set_transition(dfa, src, str[i], dst);
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst){
	for (int j = 0; j < 128; j++){
		dfa->trans[src][j] = dst;
	}
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value){
	dfa->acc[state] = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
extern bool DFA_get_accepting(DFA dfa, int state){
	return dfa->acc[state];
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input){
	int state = dfa->s0;
	bool sol = 0;
	for (int i=0; (i < strlen(input)) && (state != -1); i++){
		state = DFA_get_transition(dfa, state, input[i]);
	}
	if (DFA_get_accepting(dfa, state)){
		sol = 1;
	}
	return sol;
}

/**
 * Print the given DFA to System.out.
 */
void DFA_print(DFA dfa){
	for (int i = 0; i < dfa->nstates; i++){
		for (int j = 0; j < 128; j++){
			if (dfa->trans[i][j] != -1){
				printf("%d", i);
				printf("%s", ", ");
				printf("%c", (char)j);
				printf("%s", ": ");
				printf("%d", dfa->trans[i][j]);
				printf("%s", "\n");
			}
		}
	}
}
