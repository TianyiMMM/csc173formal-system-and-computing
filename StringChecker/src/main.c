/*
 * File: project1.c
 * Creator: Tianyi Ma
 * Created: Tue Sep 18 11:01:52 2018
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dfa.h"
#include "nfa.h"
#include "translator.h"

DFA dfa1(){
	DFA pattern1 = new_DFA(4);
	DFA_set_transition(pattern1, 0, 'z', 1);
	DFA_set_transition(pattern1, 1, 'x', 2);
	DFA_set_transition(pattern1, 2, 'y', 3);
	DFA_set_accepting(pattern1, 3, 1);
	return pattern1;
}

DFA dfa2(){
	DFA pattern2 = new_DFA(4);
	DFA_set_transition(pattern2, 0, 'a', 1);
	DFA_set_transition(pattern2, 1, 'b', 2);
	DFA_set_transition(pattern2, 2, 'c', 3);
	DFA_set_transition_all(pattern2, 3, 3);
	DFA_set_accepting(pattern2, 3, 1);
	return pattern2;
}

DFA dfa3(){
	DFA pattern3 = new_DFA(2);
	DFA_set_transition(pattern3, 0, '0', 1);
	DFA_set_transition(pattern3, 1, '0', 0);
	DFA_set_transition(pattern3, 1, '1', 1);
	DFA_set_transition(pattern3, 0, '1', 0);
	DFA_set_accepting(pattern3, 1, 1);
	return pattern3;
}

DFA dfa4(){
	DFA dfa = new_DFA(4);
	DFA_set_transition(dfa, 0, '0', 2);
	DFA_set_transition(dfa, 0, '1', 1);
	DFA_set_transition(dfa, 1, '0', 3);
	DFA_set_transition(dfa, 1, '1', 0);
	DFA_set_transition(dfa, 2, '0', 0);
	DFA_set_transition(dfa, 2, '1', 3);
	DFA_set_transition(dfa, 3, '0', 1);
	DFA_set_transition(dfa, 3, '1', 2);
	DFA_set_accepting(dfa, 3, 1);
	return dfa;
}

// recognizes binary input with an even number of 0's
DFA dfa5(){
	DFA dfa = new_DFA(3);
	DFA_set_transition(dfa, 0, '1', 1);
	DFA_set_transition(dfa, 0, '0', 2);
	DFA_set_transition(dfa, 1, '1', 1);
	DFA_set_transition(dfa, 2, '1', 2);
	DFA_set_transition(dfa, 1, '0', 2);
	DFA_set_transition(dfa, 2, '0', 1);
	DFA_set_accepting(dfa, 1, 1);
	return dfa;
}

NFA nfa1(){
	NFA pattern5 = new_NFA(4);
	NFA_add_transition(pattern5, 0, 'c', 1);
	NFA_add_transition(pattern5, 1, 'a', 2);
	NFA_add_transition(pattern5, 2, 'r', 3);
	NFA_add_transition_all(pattern5, 0, 0);
	NFA_set_accepting(pattern5, 3, 1);
	return pattern5;
}

NFA nfa2(){
	NFA pattern6 = new_NFA(4);
	NFA_add_transition(pattern6, 0, 'c', 1);
	NFA_add_transition(pattern6, 1, 'a', 2);
	NFA_add_transition(pattern6, 2, 'r', 3);
	NFA_add_transition_all(pattern6, 0, 0);
	NFA_add_transition_all(pattern6, 3, 3);
	NFA_set_accepting(pattern6, 3, 1);
	return pattern6;
}

NFA nfa3(){
	NFA pattern7 = new_NFA(20);
		int s1[] = {0, 2, 4, 6, 8, 11, 13, 15, 17, 19};
		int s2[] = {1, 3, 5, 7, 9, 10, 12, 14, 16, 18};
		char s3[] = {'a', 'g', 'h', 'i', 'n', 'n', 'o', 's', 't', 'w'};
		NFA_add_transition(pattern7, 0, 'a', 1);
		NFA_add_transition(pattern7, 1, 'a', 2);
		NFA_add_transition(pattern7, 0, 'g', 3);
		NFA_add_transition(pattern7, 3, 'g', 4);
		NFA_add_transition(pattern7, 0, 'h', 5);
		NFA_add_transition(pattern7, 5, 'h', 6);
		NFA_add_transition(pattern7, 0, 'i', 7);
		NFA_add_transition(pattern7, 7, 'i', 8);
		NFA_add_transition(pattern7, 0, 'n', 9);
		NFA_add_transition(pattern7, 9, 'n', 10);
		NFA_add_transition(pattern7, 10, 'n', 11);
		NFA_add_transition(pattern7, 0, 'o', 12);
		NFA_add_transition(pattern7, 12, 'o', 13);
		NFA_add_transition(pattern7, 0, 's', 14);
		NFA_add_transition(pattern7, 14, 's', 15);
		NFA_add_transition(pattern7, 0, 't', 16);
		NFA_add_transition(pattern7, 16, 't', 17);
		NFA_add_transition(pattern7, 0, 'w', 18);
		NFA_add_transition(pattern7, 18, 'w', 19);
		for (int i=0; i < 10; i++){
			NFA_add_transition_all(pattern7, s1[i], s1[i]);
			if (s1[i] != 0){
				NFA_set_accepting(pattern7, s1[i], 1);
			}
			for (int j=0; j < 128; j++){
				if (j != (int)s3[i]){
					NFA_add_transition(pattern7, s2[i], j, s2[i]);
				}
			}
		}
		return pattern7;
}

// recognizes binary input with "00" or "11" as a substring
NFA nfa4(){
	NFA nfa = new_NFA(4);
	NFA_add_transition(nfa, 0, '0', 1);
	NFA_add_transition(nfa, 0, '0', 0);
	NFA_add_transition(nfa, 1, '0', 3);
	NFA_add_transition(nfa, 0, '1', 2);
	NFA_add_transition(nfa, 0, '1', 0);
	NFA_add_transition(nfa, 2, '1', 3);
	NFA_add_transition(nfa, 3, '0', 3);
	NFA_add_transition(nfa, 3, '1', 3);
	NFA_set_accepting(nfa, 3, 1);
	return nfa;
}

DFA nfa_to_dfa1(){
	NFA nfa = nfa1();
	return NFA_translator(nfa);
}

DFA nfa_to_dfa2(){
	NFA nfa = nfa2();
	return NFA_translator(nfa);
}

void DFA_repl(DFA dfa, char* pattern){
	bool check = 0;
	char* quit = "quit";
	printf("Testing DFA that recognizes %s...\n", pattern);
	while (!check){
	  char in[256];
	  in[0] = '\0';
		printf("Enter an input (\"quit\" to quit): ");
		scanf("%s", in);
		if (strlen(in)==4){
		  check = 1;
		  for (int i = 0; i < 4; i++){
		    if (in[i] != quit[i]){
		      check = 0;
		    }
		  }
		}
		if (!check){
			printf("Result for input \"%s\": ", in);
			printf(DFA_execute(dfa, in) ? "true\n" : "false\n");
		}
	}
	DFA_free(dfa);
	printf("\n");
}

void NFA_repl(NFA nfa, char* pattern){
	bool check = 0;
	char* quit = "quit";
	printf("Testing NFA that recognizes %s...\n", pattern);
	while (!check){
		char in[256];
		in[0] = '\0';
		printf("Enter an input (\"quit\" to quit): ");
		scanf("%s", in);
		if (strlen(in)==4){
		  check = 1;
		  for (int i = 0; i < 4; i++){
		    if (in[i] != quit[i]){
		      check = 0;
		    }
		  }
		}
		if (!check){
			printf("Result for input \"%s\": ", in);
			printf(NFA_execute(nfa, in) ? "true\n" : "false\n");
		}
	}
	NFA_free(nfa);
	printf("\n");
}



int main(int argc, char** argv) {
	printf("CSC173 Project 1 by Tianyi Ma\n\n");

	DFA_repl(dfa1(), "exactly the string \"zxy\"");
	DFA_repl(dfa2(), "any string that starts with the characters \"abc\"");
	DFA_repl(dfa3(), "binary input with an odd number of 0’s");
	DFA_repl(dfa4(), "binary input with an odd number of both 0’s and 1's");
	DFA_repl(dfa5(), "binary input with an even number of 0's");

	NFA_repl(nfa1(), "strings ending in \"car\"");
	NFA_repl(nfa2(), "strings contains \"car\"");
	NFA_repl(nfa3(), "strings with more than one a, g, h, i, o, s, t, or w, or more than two n’s");
	NFA_repl(nfa4(), "binary input with \"00\" or \"11\" as a substring");

	DFA_repl(nfa_to_dfa1(), "strings ending in \"car\"(nfa_to_dfa_translator)");
	DFA_repl(nfa_to_dfa2(), "strings contains \"car\"(nfa_to_dfa_translator)");

}
