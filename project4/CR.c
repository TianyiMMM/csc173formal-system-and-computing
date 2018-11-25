#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CR.h"

struct CR {
	char Course[6];
	char Room[20];
};

CR new_CR(char* Course, char* Room){
	CR this = (CR)malloc(sizeof(struct CR));

	for (int i = 0; i < 5; i++){
		if (i < strlen(Course)){
			this->Course[i] = Course[i];
		} else {
			this->Course[i] = 0;
		}
	}

	for (int i = 0; i < 20; i++){
		if (i < strlen(Room)){
			this->Room[i] = Room[i];
		} else {
			this->Room[i] = 0;
		}
	}
	return this;
}

int hash_CR(CR t){
	char Course[4];
	for (int i = 0; i < 3; i++){
		Course[i] = t->Course[i+2];
	}
	Course[3] = '\0';
	int key = atoi(Course);
	key = key % 1009;
	return key;
}

void free_CRHashTable(CRHashTable R){
	for (int i = 0; i < 1009; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_CR(CR X, CR cr){
	bool equal = 1;

	for (int i = 0; i < 5; i++){
		if (X->Course[i]!=cr->Course[i]){
			equal = 0;
		}
	}
	if (X->Room[0] != '*'){ // if the Room is specified
		for (int i = 0; i < 20; i++){
			if (X->Room[i]!=cr->Room[i]){
				equal = 0;
			}
		}
	}
	return equal;
}

void insert_CR(CR t, CRHashTable R){
	int key = hash_CR(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_CR(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
}

// assume that the components of key attributes will always be given
void delete_CR(CR X, CRHashTable R){
	int key = hash_CR(X);
	if (R[key] != NULL){
		if (X->Room[0]!='*'){
			LinkedList_remove(R[key], X);
		} else {
			while (!LinkedList_isEmpty(R[key])){
				LinkedList_pop(R[key]);
			}
		}
	}
}

// assume that the components of key attributes will always be given
CRList lookup_CR(CR X, CRHashTable R){
	int key = hash_CR(X);
	CRList list = new_LinkedList();
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			CR cr = LinkedListIterator_next(iterator);
			if (equal_CR(X, cr)){
				LinkedList_add_at_end(list, cr);
			}
		}
		free(iterator);
	}
	return list;
}
void print_CR(CR cr){
	printf("%s %s\n", cr->Course, cr->Room);
}

void print_CRList(CRList list){
	LinkedListIterator iterator = LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator)){
		CR cr = LinkedListIterator_next(iterator);
		print_CR(cr);
	}
	free(iterator);
}

void print_CRRelation(CRHashTable R){
	printf("Course Room\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			print_CRList(R[i]);
		}
	}
}


void fprint_CRRelation(CRHashTable R, FILE *f){
	fprintf(f, "Course Room\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(R[i]);
			while (LinkedListIterator_hasNext(iterator)){
				CR cr = LinkedListIterator_next(iterator);
				fprintf(f, "%s %s\n", cr->Course, cr->Room);
			}
			free(iterator);
		}
	}
}

