#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "SNAP.h"

struct SNAP {
	int StudentId;
	char Name[30];
	char Address[50];
	char Phone[8];
};

SNAP new_SNAP(int StudentId, char* Name, char* Address, char* Phone){

	SNAP this = (SNAP)malloc(sizeof(struct SNAP));

	this->StudentId = StudentId;

	for (int i = 0; i < 30; i++){
		if (i < strlen(Name)){
			this->Name[i] = Name[i];
		} else {
			this->Name[i] = 0;
		}
	}

	for (int i = 0; i < 50; i++){
		if (i < strlen(Address)){
			this->Address[i] = Address[i];
		} else {
			this->Address[i] = 0;
		}
	}

	for (int i = 0; i < 8; i++){
		if (i < strlen(Phone)){
			this->Phone[i] = Phone[i];
		} else {
			this->Phone[i] = 0;
		}
	}

	return this;
}

int hash_SNAP(SNAP t){
	int key = t->StudentId;
	key = key % 1009;
	return key;
}

void free_SNAPHashTable(SNAPHashTable R){
	for (int i = 0; i < 1009; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_SNAP(SNAP X, SNAP snap){
	bool equal = 1;
	if (X->StudentId != snap->StudentId){
		equal = 0;
	}
	if (X->Name[0] != '*'){
		for (int i = 0; i < 30; i++){
			if (X->Name[i]!=snap->Name[i]){
				equal = 0;
			}
		}
	}
	if (X->Address[0] != '*'){ // if the address is specified
		for (int i = 0; i < 50; i++){
			if (X->Address[i]!=snap->Address[i]){
				equal = 0;
			}
		}
	}
	if (X->Phone[0] != '*'){
		for (int i = 0; i < 50; i++){
			if (X->Phone[i]!=snap->Phone[i]){
				equal = 0;
			}
		}
	}
	return equal;
}

void insert_SNAP(SNAP t, SNAPHashTable R){
	int key = hash_SNAP(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	LinkedList_add_at_end(R[key], t);
}

// assume that the components of key attributes will always be given
void delete_SNAP(SNAP X, SNAPHashTable R){
	int key = hash_SNAP(X);
	if (R[key] != NULL){
		LinkedList_remove(R[key], X);
	}
}

// assume that the components of key attributes will always be given
SNAPList lookup_SNAP(SNAP X, SNAPHashTable R){
	int key = hash_SNAP(X);
	SNAPList list = new_LinkedList();
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			SNAP snap = LinkedListIterator_next(iterator);
			if (equal_SNAP(X, snap)){
				LinkedList_add_at_end(list, snap);
			}
		}
		free(iterator);
	}
	return list;
}
void print_SNAP(SNAP snap){
	printf("%d %s %s %s\n", snap->StudentId, snap->Name, snap->Address, snap->Phone);
}

void print_SNAPList(SNAPList list){
	LinkedListIterator iterator = LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator)){
		SNAP snap = LinkedListIterator_next(iterator);
		print_SNAP(snap);
	}
	free(iterator);
}

void print_SNAPRelation(SNAPHashTable R){
	printf("StudentId Name Address Phone\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			print_SNAPList(R[i]);
		}
	}
}




