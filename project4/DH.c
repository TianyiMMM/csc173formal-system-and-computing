#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "DH.h"

struct DH {
	char Day[3];
	char Hour[4];
};

DH new_DH(char* Day, char* Hour){
	DH this = (DH)malloc(sizeof(struct DH));

	for (int i = 0; i < 3; i++){
		if (i < strlen(Day)){
			this->Day[i] = Day[i];
		} else {
			this->Day[i] = 0;
		}
	}
	for (int i = 0; i < 4; i++){
		if (i < strlen(Hour)){
			this->Hour[i] = Hour[i];
		} else {
			this->Hour[i] = 0;
		}
	}
	return this;
}

int hash_DH(DH t){
	int key = (int)t->Day[0]+(int)t->Day[1];
	key = key % 1009;
	return key;
}

void free_DHHashTable(DHHashTable R){
	for (int i = 0; i < 1009; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_DH(DH X, DH dh){
	bool equal = 1;

	if (X->Day[0] != '*'){
		for (int i = 0; i < 3; i++){
			if (X->Day[i]!=dh->Day[i]){
				equal = 0;
			}
		}
	}
	if (X->Hour[0] != '*'){ // if the Hour is specified
		for (int i = 0; i < 4; i++){
			if (X->Hour[i]!=dh->Hour[i]){
				equal = 0;
			}
		}
	}
	return equal;
}

void insert_DH(DH t, DHHashTable R){
	int key = hash_DH(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_DH(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
}

// assume that the components of key attributes will always be given
void delete_DH(DH X, DHHashTable R){
	int key = hash_DH(X);
	if (R[key] != NULL){
		if (X->Hour[0]!='*'){
			LinkedList_remove(R[key], X);
		} else {
			while (!LinkedList_isEmpty(R[key])){
				LinkedList_pop(R[key]);
			}
		}
	}
}

// assume that the components of key attributes will always be given
DHList lookup_DH(DH X, DHHashTable R){
	int key = hash_DH(X);
	DHList list = new_LinkedList();
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			DH dh = LinkedListIterator_next(iterator);
			if (equal_DH(X, dh)){
				LinkedList_add_at_end(list, dh);
			}
		}
		free(iterator);
	}
	return list;
}
void print_DH(DH dh){
	printf("%s %s\n", dh->Day, dh->Hour);
}

void print_DHList(DHList list){
	LinkedListIterator iterator = LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator)){
		DH dh = LinkedListIterator_next(iterator);
		print_DH(dh);
	}
	free(iterator);
}

void print_DHRelation(DHHashTable R){
	printf("Day Hour\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			print_DHList(R[i]);
		}
	}
}


