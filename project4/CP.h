#ifndef _CP_h_gf
#define _CP_h_gf

#include "LinkedList.h"

typedef struct CP* CP;

typedef LinkedList CPList;

typedef CPList CPHashTable[1009];

extern CP new_CP(char* Course, char* Prerequisite);

extern int hash_CP(CP t);

extern void free_HashTable();

extern bool equal_CP(CP X, CP CP);

extern void insert_CP(CP t, CPHashTable R);

extern void delete_CP(CP X, CPHashTable R);

extern CPList lookup_CP(CP X, CPHashTable R);

extern void print_CP(CP CP);

extern void print_CPList(CPList list);

extern void print_CPRelation(CPHashTable R);

#endif
