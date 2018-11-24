#ifndef _CSG_h_gf
#define _CSG_h_gf

#include "LinkedList.h"

typedef struct CSG* CSG;

typedef LinkedList CSGList;

typedef CSGList CSGHashTable[1009];

extern CSG new_CSG(char* Course, int StudentId, char* Grade);

extern int hash_CSG(CSG t);

extern void free_HashTable();

extern bool equal_CSG(CSG X, CSG csg);

extern void insert_CSG(CSG t, CSGHashTable R);

extern void delete_CSG(CSG X, CSGHashTable R);

extern CSGList lookup_CSG(CSG X, CSGHashTable R);

extern void print_CSG(CSG csg);

extern void print_CSGList(CSGList list);

extern void print_CSGRelation(CSGHashTable R);

#endif
