#ifndef _SNAP_h_gf
#define _SNAP_h_gf

#include "LinkedList.h"

typedef struct SNAP* SNAP;

typedef LinkedList SNAPList;

typedef SNAPList SNAPHashTable[1009];

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
