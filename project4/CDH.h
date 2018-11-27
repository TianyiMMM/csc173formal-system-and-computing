#ifndef _CDH_h_gf
#define _CDH_h_gf

#include "LinkedList.h"

typedef struct CDH* CDH;

typedef LinkedList CDHList;

typedef CDHList CDHHashTable[1009];

extern CDH new_CDH(char* Course, char* Day, char* Hour);

extern int hash_CDH(CDH t);

extern void free_CDHHashTable(CDHHashTable R);

extern bool equal_CDH(CDH X, CDH cdh);

extern void insert_CDH(CDH t, CDHHashTable R);

extern void delete_CDH(CDH X, CDHHashTable R);

extern CDHList lookup_CDH(CDH X, CDHHashTable R);

extern char* getCourse_CDH(CDH X);

extern char* getDay_CDH(CDH X);

extern char* getHour_CDH(CDH X);

extern void print_CDH(CDH cdh);

extern void print_CDHList(CDHList list);

extern void print_CDHRelation(CDHHashTable R);

extern void fprint_CDHRelation(CDHHashTable R, FILE *f);

#endif
