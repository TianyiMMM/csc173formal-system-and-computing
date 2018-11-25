#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CSG.h"

struct CSG {
	char Course[5];
	int StudentId;
	char Grade[2];
};

CSG new_CSG(char* Course, int StudentId, char* Grade){
	CSG this = (CSG)malloc(sizeof(struct CSG));
	int lenCourse = strlen(Course);
	for (int i = 0; i < 5; i++){
		if (i < lenCourse){
			this->Course[i] = Course[i];
		} else {
			this->Course[i] = 0;
		}
	}

	this->StudentId = StudentId;
	for (int i = 0; i < 2; i++){
		if (i < strlen(Grade)){
			this->Grade[i] = Grade[i];
		} else {
			this->Grade[i] = 0;
		}
	}
	return this;
}

int hash_CSG(CSG t){
	char Course[4];
	for (int i = 0; i < 3; i++){
		Course[i] = t->Course[i+2];
	}
	Course[3] = '\0';
	int key = atoi(Course);
	key += t->StudentId;
	key = key % 1009;
	return key;
}

void free_CSGHashTable(CSGHashTable R){
	for (int i = 0; i < 1009; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_CSG(CSG X, CSG csg){
	bool equal = 1;
	if (X->StudentId != csg->StudentId){
		equal = 0;
	}
	for (int i = 0; i < 5; i++){
		if (X->Course[i]!=csg->Course[i]){
			equal = 0;
		}
	}
	if (X->Grade[0] != '*'){ // if the grade is specified
		for (int i = 0; i < 2; i++){
			if (X->Grade[i]!=csg->Grade[i]){
				equal = 0;
			}
		}
	}
	return equal;
}

void insert_CSG(CSG t, CSGHashTable R){
	int key = hash_CSG(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_CSG(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
}

// assume that the components of key attributes will always be given
void delete_CSG(CSG X, CSGHashTable R){
	int key = hash_CSG(X);
	if (R[key] != NULL){
		LinkedList_remove(R[key], X);
	} else {
		printf("delete: don't have that element");
	}
}

// assume that the components of key attributes will always be given
CSGList lookup_CSG(CSG X, CSGHashTable R){
	CSGList list = new_LinkedList();
	int key = hash_CSG(X);
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			CSG csg = LinkedListIterator_next(iterator);
			if (equal_CSG(X, csg)){
				LinkedList_add_at_end(list, csg);
			}
		}
		free(iterator);
	}
	return list;
}
void print_CSG(CSG csg){
	printf("%s %d %s\n", csg->Course, csg->StudentId, csg->Grade);
}

void print_CSGList(CSGList list){
	if (!LinkedList_isEmpty(list)){
		LinkedListIterator iterator = LinkedList_iterator(list);
		while (LinkedListIterator_hasNext(iterator)){
			CSG csg = LinkedListIterator_next(iterator);
			print_CSG(csg);
		}
		free(iterator);
	} else {
		printf("\n");
	}
}

void print_CSGRelation(CSGHashTable R){
	printf("Course StudentId Grade\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			print_CSGList(R[i]);
		}
	}
}

void fprint_CSGRelation(CSGHashTable R, FILE *f){
	fprintf(f, "Course StudentId Grade\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(R[i]);
			while (LinkedListIterator_hasNext(iterator)){
				CSG csg = LinkedListIterator_next(iterator);
				fprintf(f, "%s %d %s\n", csg->Course, csg->StudentId, csg->Grade);
			}
			free(iterator);
		}
	}
}




