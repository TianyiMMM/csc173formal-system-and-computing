#ifndef _CR_h_gf
#define _CR_h_gf

#include "LinkedList.h"

typedef struct CR* CR;

typedef LinkedList CRList;

typedef CRList CRHashTable[1009];

extern CR new_CR(char* Course, char* Room);

extern int hash_CR(CR t);

extern void free_CRHashTable(CRHashTable R);

extern bool equal_CR(CR X, CR cr);

extern void insert_CR(CR t, CRHashTable R);

extern void delete_CR(CR X, CRHashTable R);

extern CRList lookup_CR(CR X, CRHashTable R);

extern void print_CR(CR cr);

extern void print_CRList(CRList list);

extern void print_CRRelation(CRHashTable R);

extern void fprint_CRRelation(CRHashTable R, FILE *f);

#endif
