#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CP.h"

struct CP {
	char Course[6];
	char Prerequisite[5];
};

CP new_CP(char* Course, char* Prerequisite){
	CP this = (CP)malloc(sizeof(struct CP));

	for (int i = 0; i < 5; i++){
		if (i < strlen(Course)){
			this->Course[i] = Course[i];
			this->Prerequisite[i] = Prerequisite[i];
		} else {
			this->Prerequisite[i] = 0;
			this->Course[i] = 0;
		}
	}
	return this;
}

int hash_CP(CP t){
	char Course[4];
	for (int i = 0; i < 3; i++){
		Course[i] = t->Course[i+2];
	}
	Course[3] = '\0';
	int key = atoi(Course);
	key = key % 1009;
	return key;
}

void free_CPHashTable(CPHashTable R){
	for (int i = 0; i < 1009; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_CP(CP X, CP cp){
	bool equal = 1;

	for (int i = 0; i < 5; i++){
		if (X->Course[i]!=cp->Course[i]){
			equal = 0;
		}
	}
	if (X->Prerequisite[0] != '*'){ // if the Prerequisite is specified
		for (int i = 0; i < 5; i++){
			if (X->Prerequisite[i]!=cp->Prerequisite[i]){
				equal = 0;
			}
		}
	}
	return equal;
}

void insert_CP(CP t, CPHashTable R){
	int key = hash_CP(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_CP(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
}

// assume that the components of key attributes will always be given
void delete_CP(CP X, CPHashTable R){
	int key = hash_CP(X);
	if (R[key] != NULL){
		if (X->Prerequisite[0]!='*'){
			LinkedList_remove(R[key], X);
		} else {
			while (!LinkedList_isEmpty(R[key])){
				LinkedList_pop(R[key]);
			}
		}
	}
}

// assume that the components of key attributes will always be given
CPList lookup_CP(CP X, CPHashTable R){
	int key = hash_CP(X);
	CPList list = new_LinkedList();
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			CP cp = LinkedListIterator_next(iterator);
			if (equal_CP(X, cp)){
				LinkedList_add_at_end(list, cp);
			}
		}
		free(iterator);
	}
	return list;
}
void print_CP(CP cp){
	printf("%s %s\n", cp->Course, cp->Prerequisite);
}

void print_CPList(CPList list){
	LinkedListIterator iterator = LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator)){
		CP cp = LinkedListIterator_next(iterator);
		print_CP(cp);
	}
	free(iterator);
}

void print_CPRelation(CPHashTable R){
	printf("Course Prerequisite\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			print_CPList(R[i]);
		}
	}
}


void fprint_CPRelation(CPHashTable R, FILE *f){
	fprintf(f, "Course Prerequisite\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(R[i]);
			while (LinkedListIterator_hasNext(iterator)){
				CP cp = LinkedListIterator_next(iterator);
				fprintf(f, "%s %s\n", cp->Course, cp->Prerequisite);
			}
			free(iterator);
		}
	}
}

