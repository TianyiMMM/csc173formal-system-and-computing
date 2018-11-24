#ifndef _SNAP_h_gf
#define _SNAP_h_gf

#include "LinkedList.h"

typedef struct SNAP* SNAP;

typedef LinkedList SNAPList;

typedef SNAPList SNAPHashTable[1009];

extern SNAP new_SNAP(int StudentId, char* Name, char* Address, char* Phone);

extern int hash_SNAP(SNAP t);

extern void free_HashTable();

extern bool equal_SNAP(SNAP X, SNAP SNAP);

extern void insert_SNAP(SNAP t, SNAPHashTable R);

extern void delete_SNAP(SNAP X, SNAPHashTable R);

extern SNAPList lookup_SNAP(SNAP X, SNAPHashTable R);

extern void print_SNAP(SNAP SNAP);

extern void print_SNAPList(SNAPList list);

extern void print_SNAPRelation(SNAPHashTable R);

#endif
