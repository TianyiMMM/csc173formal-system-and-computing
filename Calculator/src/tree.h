#include <stdbool.h>

#ifndef _tree_h
#define _tree_h
#define FAILED NULL

typedef struct NODE *TREE;

extern TREE new_Tree();
extern void Tree_free(TREE tree);
extern TREE makeNode0(char* x);
extern TREE makeNode1(char* x, TREE t);
extern TREE makeNode2(char* x, TREE t1, TREE t2);
extern TREE makeNode3(char* x, TREE t1, TREE t2, TREE t3);
extern TREE get_leftmostChilde(TREE tree);
extern TREE get_rightSiblings(TREE tree);
extern char* get_label(TREE tree);
extern bool compareAll(char in);
extern bool compareNum(char in);

extern bool Tree_get_wellFormed();
extern void Tree_set_wellFormed(bool w);
extern void printErrorMessage();

extern TREE D(char* in);
extern TREE NT(char* in);
extern TREE N(char* in);
extern TREE F(char* in);
extern TREE FT(char* in);
extern TREE T(char* in);
extern TREE TT(char* in);
extern TREE E(char* in);

extern bool failed();
extern void printTree(TREE tree, int height);
extern void addNode(TREE root, TREE child);
extern void set_find();
extern void set_next_Terminal();
extern bool isDigit(char l);
extern bool isOperator(char l);
extern int operate(int a, int b, char operator);
extern int evaluate(TREE tree);

#endif
