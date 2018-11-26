#ifndef _SNAP_h_gf
#define _SNAP_h_gf

#include "LinkedList.h"

typedef struct SNAP* SNAP;

typedef LinkedList SNAPList;

typedef SNAPList SNAPHashTable[1009];

typedef struct NODE *TREE;

extern TREE new_TREE(char* Name, SNAP p);

extern bool cmpName(char* Name1, char* Name2);

extern void insert_Node(char* Name, SNAP p, TREE root);

extern void print_TREE(TREE root);

extern void print_secondIndex_SNAP();

extern void findSNAPList_helper(char* Name, TREE root, SNAPList list);

extern void findSNAPList(char* Name, SNAPList list);

extern int getStudentId_SNAP(SNAP snap);

extern SNAP new_SNAP(int StudentId, char* Name, char* Address, char* Phone);

extern int hash_SNAP(SNAP t);

extern void free_SNAPHashTable(SNAPHashTable R);

extern bool equal_SNAP(SNAP X, SNAP snap);

extern void insert_SNAP(SNAP t, SNAPHashTable R);

extern void delete_SNAP(SNAP X, SNAPHashTable R);

extern SNAPList lookup_SNAP(SNAP X, SNAPHashTable R);

extern void print_SNAP(SNAP snap);

extern void print_SNAPList(SNAPList list);

extern void print_SNAPRelation(SNAPHashTable R);

extern void fprint_SNAPRelation(SNAPHashTable R, FILE *f);

#endif
