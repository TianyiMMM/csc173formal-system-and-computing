#ifndef _DH_h_gf
#define _DH_h_gf

#include "LinkedList.h"

typedef struct DH* DH;

typedef LinkedList DHList;

typedef DHList DHHashTable[1009];

extern DH new_DH(char* Day, char* Hour);

extern int hash_DH(DH t);

extern void free_DHHashTable(DHHashTable R);

extern bool equal_DH(DH X, DH dh);

extern void insert_DH(DH t, DHHashTable R);

extern void delete_DH(DH X, DHHashTable R);

extern DHList lookup_DH(DH X, DHHashTable R);

extern void print_DH(DH dh);

extern void print_DHList(DHList list);

extern void print_DHRelation(DHHashTable R);

#endif
