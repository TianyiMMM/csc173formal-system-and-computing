#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "tree.h"
#include "stack.h"
#include "table_driven_parsing.h"

struct NODE {
	char* label;
	TREE leftmostChild, rightSibling;
};


TREE parseTree; /* holds the result of the parse */
int next_Terminal = 0; /* current position in input string */
bool wellFormed = 1;
bool Tree_get_wellFormed(){
	return wellFormed;
}
void Tree_set_wellFormed(bool w){
	wellFormed = w;
}
void printErrorMessage(){
	if (wellFormed){
		wellFormed = 0;
		printf("Error: malformed expression. Stopping current parsing and starting parsing next expression. \n\n");
	}
}

TREE new_Tree() {
	TREE root;
	root = (TREE) malloc(sizeof(struct NODE));
	root->label = NULL;
	root->leftmostChild = NULL;
	root->rightSibling = NULL;
	return root;
}

void Tree_free(TREE tree){
	if (tree!=NULL){
	  //Tree_free(tree->leftmostChild);
	  //Tree_free(tree->rightSibling);
		free(tree);
	}
}

TREE makeNode0(char* x) {
	TREE root;
	root = (TREE) malloc(sizeof(struct NODE));
	root->label = x;
	root->leftmostChild = NULL;
	root->rightSibling = NULL;
	return root;
}

TREE makeNode1(char* x, TREE t) {
	TREE root;
	root = makeNode0(x);
	root->leftmostChild = t;
	return root;
}

TREE makeNode2(char* x, TREE t1, TREE t2) {
	TREE root;
	root = makeNode1(x, t1);
	t1->rightSibling = t2;
	return root;
}

TREE makeNode3(char* x, TREE t1, TREE t2, TREE t3) {
	TREE root;
	root = makeNode1(x, t1);
	t1->rightSibling = t2;
	t2->rightSibling = t3;
	return root;
}

TREE get_leftmostChild(TREE tree){
	return tree->leftmostChild;
}

TREE get_rightSibling(TREE tree){
	return tree->rightSibling;
}

char* get_label(TREE tree){
	return tree->label;
}

bool compareAll(char in){
	return ((in=='0') || (in=='1') || (in=='2') || (in=='3') || (in=='4') || (in=='5')
			 || (in=='6') || (in=='7') || (in=='8') || (in=='9') || (in=='(') || (in=='+')
			 || (in=='-') || (in=='*') || (in=='/'));
}

bool compareNum(char in){
	return ((in=='0') || (in=='1') || (in=='2') || (in=='3') || (in=='4') || (in=='5')
			 || (in=='6') || (in=='7') || (in=='8') || (in=='9'));
}


TREE D(char* in) {
	int currTerminal = next_Terminal;
	next_Terminal++;
	char sym = in[currTerminal];

	if (sym == '0'){
		return makeNode1("D", makeNode0("0"));
	} else if (sym == '1'){
		return makeNode1("D", makeNode0("1"));
	} else if (sym == '2'){
		return makeNode1("D", makeNode0("2"));
	} else if (sym == '3'){
		return makeNode1("D", makeNode0("3"));
	} else if (sym == '4'){
		return makeNode1("D", makeNode0("4"));
	} else if (sym == '5'){
		return makeNode1("D", makeNode0("5"));
	} else if (sym == '6'){
		return makeNode1("D", makeNode0("6"));
	} else if (sym == '7'){
		return makeNode1("D", makeNode0("7"));
	} else if (sym == '8'){
		return makeNode1("D", makeNode0("8"));
	} else if (sym == '9'){
		return makeNode1("D", makeNode0("9"));
	} else {
		printErrorMessage();
		return FAILED;
	}
}

TREE NT(char* in) {
	TREE tN;
	if (compareNum(in[next_Terminal])) { /* follow production 2 */
		tN = N(in);
		if (tN == FAILED){
			printErrorMessage();
			return FAILED;
		} else {
			TREE node = makeNode1("NT", tN);
			return node;
		}
	} else {/* the third or */
		return makeNode1("NT", makeNode0("e"));
	}
}

TREE N(char* in) {
	TREE tD, tNT;
		tD = D(in);
		if(tD != FAILED) {
			tNT = NT(in);
			if (tNT == FAILED){
				printErrorMessage();
				return FAILED;
			}else{
				TREE node = makeNode2("N", tD, tNT);
				return node;
			}
		} else {/* first call to D failed */
			printErrorMessage();
			return FAILED;
		}
}

TREE F(char* in) {
	TREE tN, tE;
	if (compareNum(in[next_Terminal])) { /* follow first "or" statement of production 5 */
		tN = N(in);
		if (tN == FAILED){
			printErrorMessage();
			return FAILED;
		} else{
			TREE node = makeNode1("F", tN);
			return node;
		}
	} else if (in[next_Terminal] == '('){ /* follow the other "or" statement in production 5 */
		next_Terminal++;
		tE = E(in);
		if (tE == FAILED){
			printErrorMessage();
			return FAILED;
		} else {
			if (in[next_Terminal] == ')'){
				next_Terminal++;
				TREE node = makeNode3("F", makeNode0("("), tE, makeNode0(")"));
				return node;
			} else {
				printErrorMessage();
				return FAILED;
			}
		}
	} else {
		printErrorMessage();
		return FAILED;
	}
}

TREE FT(char* in) {
	TREE tF, tFT;
	if ((in[next_Terminal]=='*') || (in[next_Terminal]=='/')) { /* follow production 2 */

		char sym = in[next_Terminal];

		next_Terminal++;
		tF = F(in);
		if(tF != FAILED) {
			tFT = FT(in);
			if (tFT == FAILED) {
				printErrorMessage();
				return FAILED;
			} else {
				if (sym == '*'){
					TREE node = makeNode3("FT", makeNode0("*"), tF, tFT);
					return node;
				} else {
					TREE node = makeNode3("FT", makeNode0("/"), tF, tFT);
					return node;
				}
			}
		} else {/* first call to T failed */
			printErrorMessage();
			return FAILED;
		}
	} else /* the third or */
		return makeNode1("FT", makeNode0("e"));
}

TREE T(char* in) {
	TREE tF, tFT;

	if (compareAll(in[next_Terminal])) { /* follow production 3 */
		tF = F(in);
		if(tF != FAILED) {
			tFT = FT(in);
			if (tFT == FAILED){
				printErrorMessage();
				return FAILED;
			} else {
			  //TREE node = makeNode2("T", tF, tFT);
				return makeNode2("T", tF, tFT);
			}
		} else { /* first call to F failed */
			printErrorMessage();
			return FAILED;
		}
	} else{
		printErrorMessage();
		return FAILED;
	}
}

TREE TT(char* in) {
	TREE tT, tTT;
	if ((in[next_Terminal]=='+') || (in[next_Terminal]=='-')) { /* follow production 2 */
		
		char sym = in[next_Terminal];

		next_Terminal++;
		tT = T(in);
		if(tT != FAILED) {
			tTT = TT(in);
			if (tTT == FAILED) {
				printErrorMessage();
				return FAILED;
			} else {
				if (sym == '+'){
					TREE node = makeNode3("TT", makeNode0("+"), tT, tTT);
					return node;
				} else {
					TREE node = makeNode3("TT", makeNode0("-"), tT, tTT);
					return node;
				}
			}
		} else {/* first call to T failed */
			printErrorMessage();
			return FAILED;
		}
	} else /* the third or */
		return makeNode1("TT", makeNode0("e"));
}

TREE E(char* in) {
	TREE tT, tTT;

	if (compareAll(in[next_Terminal])) { /* follow production 1 */
		tT = T(in);
		if(tT != FAILED) {
			tTT = TT(in);
			if (tTT == FAILED){
				printErrorMessage();
				return FAILED;
			} else {
			  //	TREE node = makeNode2("E", tT, tTT);
				return makeNode2("E", tT, tTT);
			}
		} else {/* first call to T failed */
		  Tree_free(tT);
			printErrorMessage();
			return FAILED;
		}
	} else { /* follow production 1 */
		printErrorMessage();
		return FAILED;
	}
}

bool failed(TREE tree){
	if (tree==FAILED){
		return 1;
	} else {
		return 0;
	}
}

void printTree(TREE tree, int height){
	if (tree!=NULL){
		for (int i = 0; i < height; i++){
			printf("	");
		}
		printf("%s\n", tree->label);
		int height_next = height+1;
		printTree(tree->leftmostChild, height_next);
		printTree(tree->rightSibling, height);
	}
}

bool find = 0;
void set_find(){
	find = 0;
}
void set_next_Terminal(){
	next_Terminal = 0;
}
void addNode(TREE root, TREE child){ 
	char* l = "";
	if (root!=NULL){
		l = root->label;
		addNode(root->leftmostChild, child);
		if (root->leftmostChild==NULL && isNonTerminal(l) && !find) { 
      		root->label = child->label;
      		root->leftmostChild = child->leftmostChild;
      		find=1;
    	}
    	addNode(root->rightSibling, child);
    }
}

bool isDigit(char l){
	return l=='0' || l=='1' || l=='2' || l=='3' || l=='4' || l=='5' 
		|| l=='6' || l=='7' || l=='8' || l=='9';
}
bool isOperator(char l){
	return l=='+' || l=='-' || l=='*' || l=='/' || l=='(' || l==')';
}

int operate(int a, int b, char operator){
	if (operator == '+'){
		return a+b;
	} else if (operator == '-'){
		return a-b;
	} else if (operator == '*'){
		return a*b;
	} else if (operator == '/'){
		return a/b;
	} else {
		return 0;
	}
}

int evaluate(TREE tree){
	if (tree!=NULL){
		char* l = tree->label;
		/* if a tree is not NULL, then it is either a syntactic category, or a leaf
		 * if it is a leaf, then it is either a digit, or an empty string "e"
		 * first suppose it is a leaf, aka, it doesn't have a leftmostChild
		 */
		if (tree->leftmostChild==NULL){ 
			if (l[0] != 'e'){
				return atoi(l);
			} else{
				return -1;
			}
		// next suppose it is a syntactic category
		} else if (isNonTerminal(l)) { 
			if (find_index(l)==0 || find_index(l)==2){ // if curr label is "E" or "T"
				char* operator = get_label(tree->leftmostChild->rightSibling->leftmostChild);
				int tf = evaluate(tree->leftmostChild);

				if (operator[0] != 'e'){
					int ttft = evaluate(tree->leftmostChild->rightSibling);
					return operate(tf, ttft, operator[0]);
				} else {
					return tf;
				}
			} else if (find_index(l)==1 || find_index(l)==3){ // if curr label is "TT" or "FT"

				TREE TorF = tree->leftmostChild->rightSibling; 
				int tf = evaluate(TorF); 
				char* operator = get_label(TorF->rightSibling->leftmostChild);

				/* peek next operator and perform arithmetic accordingly
				 * notice this action will only be called if the next operator exists
				 */
				if (operator[0] != 'e'){
					int ttft = evaluate(TorF->rightSibling);
					return operate(tf, ttft, operator[0]);
				} else {
					return tf;
				} 
			} else if (find_index(l)==4){ // if curr label is "F"
				char* nextl = get_label(tree->leftmostChild);

				// see if it is a number or a bracketed expression E
				if (nextl[0]=='N'){
					return evaluate(tree->leftmostChild);
				} else {
					TREE tE = tree->leftmostChild->rightSibling;
					return evaluate(tE);
				} 
			// if curr label is "N", calculate the first and rest of the digits and attach them together
			} else if (find_index(l)==5){
				TREE tD = tree->leftmostChild;
				TREE tNT = tree->leftmostChild->rightSibling;
				char* nextl = get_label(tNT->leftmostChild);
				int d = evaluate(tD);

				if (nextl[0]!='e'){
					int nt = evaluate(tNT);
					if (nt==0){
						return d*10;
					} else {
						float exp = log10(nt);

						/* the digit length of nt = exp+1, (e.g. (int)log10(42) = 1, (int)log10(100) = 2)
						 * and the digit length of concat(d, nt) = nt.digit_length+1
						 */
						d = d*pow(10, (int)exp+1);
						return d+nt;
					}
				} else {
					return d;
				}
			} else if (find_index(l)==6){ // if curr label is "NT", check if it is a number or is empty
				TREE left = tree->leftmostChild;
				char* leftl = get_label(left);
				if (leftl[0]!='e'){ // if NT is a number
					int leftInt = evaluate(left);
					return leftInt;
				} else {
					return -1;
				}
			} else if (find_index(l)==7){ // if curr label is "D", return the corresponding digit
				return evaluate(tree->leftmostChild);
			} else {
				return -1;
			}

		// if curr label non of the cases above, the tree is malformed
		} else {
			printErrorMessage();
			return -1;
		}
	// this is for the case when the tree is NULL, which won't happen
	} else {
		return -1;
	}
}

