#ifndef _CRDH_h_gf
#define _CRDH_h_gf

#include "LinkedList.h"
#include "CR.h"
#include "CDH.h"
#include "DH.h"

typedef struct CRDH* CRDH;

typedef LinkedList CRDHList;

typedef CRDHList CRDHHashTable[2];

typedef struct CRDHNODE *CRDHTREE;

extern CRDHTREE new_CRDHTREE(char* Room, CRDH p);

extern bool cmpRoom(char* Room1, char* Room2);

extern void insert_Node_CRDH(char* Room, CRDH p, CRDHTREE root);

extern void print_CRDHTREE(CRDHTREE root);

extern void print_secondIndex_CRDH();

extern void findCRDHList_helper(char* Room, CRDHTREE root, CRDHList list);

extern void findCRDHList(char* Room, CRDHList list);

extern CRDH new_CRDH(char* Course, char* Room, char* Day, char* Hour);

extern int hash_CRDH(CRDH t);

extern void free_CRDHHashTable(CRDHHashTable R);

extern bool equal_CRDH(CRDH X, CRDH crdh);

extern void insert_CRDH(CRDH t, CRDHHashTable R);

extern void delete_CRDH(CRDH X, CRDHHashTable R);

extern CRDHList lookup_CRDH(CRDH X, CRDHHashTable R);

extern void print_CRDH(CRDH crdh);

extern void print_CRDHList(CRDHList list);

extern void print_CRDHRelation(CRDHHashTable R);

extern void projectDayHour_CRDH(CRDHHashTable R, DHHashTable dhR);

extern void join_CR_CDH(CRHashTable crR, CDHHashTable cdhR, CRDHHashTable R);

#endif
