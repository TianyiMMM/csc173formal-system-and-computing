#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CDH.h"

struct CDH {
	char Course[6];
	char Day[3];
	char Hour[4];
};

CDH new_CDH(char* Course, char* Day, char* Hour){
	CDH this = (CDH)malloc(sizeof(struct CDH));

	for (int i = 0; i < 5; i++){
		if (i < strlen(Course)){
			this->Course[i] = Course[i];
		} else {
			this->Course[i] = 0;
		}
	}

	for (int i = 0; i < 2; i++){
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

int hash_CDH(CDH t){
	char Course[4];
	for (int i = 0; i < 3; i++){
		Course[i] = t->Course[i+2];
	}
	Course[3] = '\0';
	int key = atoi(Course);
	key = key % 1009;
	return key;
}

void free_CDHHashTable(CDHHashTable R){
	for (int i = 0; i < 1009; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_CDH(CDH X, CDH cdh){
	bool equal = 1;

	for (int i = 0; i < 5; i++){
		if (X->Course[i]!=cdh->Course[i]){
			equal = 0;
		}
	}
	if (X->Day[0] != '*'){ // if the Day is specified
		for (int i = 0; i < 2; i++){
			if (X->Day[i]!=cdh->Day[i]){
				equal = 0;
			}
		}
	}
	if (X->Hour[0] != '*'){ // if the Hour is specified
			for (int i = 0; i < 4; i++){
				if (X->Day[i]!=cdh->Day[i]){
					equal = 0;
				}
			}
		}
	return equal;
}

void insert_CDH(CDH t, CDHHashTable R){
	int key = hash_CDH(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_CDH(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
}

// assume that the components of key attributes will always be given
void delete_CDH(CDH X, CDHHashTable R){
	int key = hash_CDH(X);
	if (R[key] != NULL){
		if (X->Day[0]!='*' && X->Hour[0]!='*'){
			LinkedList_remove(R[key], X);
		} else if (X->Day[0]=='*' && X->Hour[0]=='*'){
			while (!LinkedList_isEmpty(R[key])){
				LinkedList_pop(R[key]);
			}
		} else {
			LinkedListIterator iterator = LinkedList_iterator(R[key]);
			while (LinkedListIterator_hasNext(iterator)){
				CDH cdh = LinkedListIterator_next(iterator);
				if (equal_CDH(X, cdh)){
					LinkedList_remove(R[key], cdh);
				}
			}
			free(iterator);
		}
	}
}

// assume that the components of key attributes will always be given
CDHList lookup_CDH(CDH X, CDHHashTable R){
	int key = hash_CDH(X);
	CDHList list = new_LinkedList();
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			CDH cdh = LinkedListIterator_next(iterator);
			if (equal_CDH(X, cdh)){
				LinkedList_add_at_end(list, cdh);
			}
		}
		free(iterator);
	}
	return list;
}
void print_CDH(CDH cdh){
	printf("%s %s %s\n", cdh->Course, cdh->Day, cdh->Hour);
}

void print_CDHList(CDHList list){
	LinkedListIterator iterator = LinkedList_iterator(list);
	while (LinkedListIterator_hasNext(iterator)){
		CDH cdh = LinkedListIterator_next(iterator);
		print_CDH(cdh);
	}
	free(iterator);
}

void print_CDHRelation(CDHHashTable R){
	printf("Course Day Hour\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			print_CDHList(R[i]);
		}
	}
}

void fprint_CDHRelation(CDHHashTable R, FILE *f){
	fprintf(f, "Course Day Hour\n");
	for (int i = 0; i < 1009; i++){
		if (R[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(R[i]);
			while (LinkedListIterator_hasNext(iterator)){
				CDH cdh = LinkedListIterator_next(iterator);
				fprintf(f, "%s %s %s\n", cdh->Course, cdh->Day, cdh->Hour);
			}
			free(iterator);
		}
	}
}




