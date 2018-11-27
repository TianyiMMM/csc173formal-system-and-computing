#ifndef _CSG_h_gf
#define _CSG_h_gf

#include "LinkedList.h"

typedef struct CSG* CSG;

typedef LinkedList CSGList;

typedef LinkedList SList;

typedef CSGList CSGHashTable[2];

typedef struct CSGNODE *CSGTREE;

extern CSGTREE new_CSGTREE(int StudentId, CSG p);

extern void insert_Node_CSG(int StudentId, CSG p, CSGTREE root);

extern void print_CSGTREE(CSGTREE root);

extern void print_secondIndex_CSG();

extern void findCSGList_helper(int StudentId, CSGTREE root, CSGList list);

extern void findCSGList(int StudentId, CSGList list);

extern char* getCourse_CSG(CSG csg);

extern CSG new_CSG(char* Course, int StudentId, char* Grade);

extern int hash_CSG(CSG t);

extern void free_CSGHashTable(CSGHashTable R);

extern bool equal_CSG(CSG X, CSG csg);

extern char* getGrade_CSG(CSG csg);

extern void insert_CSG(CSG t, CSGHashTable R);

extern void delete_CSG(CSG X, CSGHashTable R);

extern CSGList lookup_CSG(CSG X, CSGHashTable R);

extern void print_CSG(CSG csg);

extern void print_CSGList(CSGList list);

extern void print_CSGRelation(CSGHashTable R);

extern void fprint_CSGRelation(CSGHashTable R, FILE *f);

extern void select_CSC(char* Name, int StudentId, char* Grade, CSGHashTable R, CSGHashTable select);

extern SList projectStudentId_CSG(CSGHashTable R);

extern void print_SList(SList s);

#endif
