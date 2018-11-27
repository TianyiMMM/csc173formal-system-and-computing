#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CRDH.h"
#include "CR.h"
#include "CDH.h"
#include "DH.h"

struct CRDH {
	char Course[6];
	char Room[20];
	char Day[3];
	char Hour[4];
};

struct CRDHNODE {
	char Room[20];
	CRDHList crdhs;
	CRDHTREE leftChild, rightChild;
};

CRDHTREE secondIndexCRDH = NULL;

CRDHTREE new_CRDHTREE(char* Room, CRDH p){
	CRDHTREE this = (CRDHTREE) malloc(sizeof(struct CRDHNODE));

	for (int i = 0; i < 20; i++){
		if (i < strlen(Room)){
			this->Room[i] = Room[i];
		} else {
			this->Room[i] = 0;
		}
	}

	this->crdhs = new_LinkedList();
	LinkedList_add_at_end(this->crdhs, p);
	this->leftChild = NULL;
	this->rightChild = NULL;
	return this;
}

void free_CRDHTREE(CRDHTREE root){
	if (root != NULL){
		LinkedList_free(root->crdhs, 1);
		print_CRDHTREE(root->leftChild);
		print_CRDHTREE(root->rightChild);
		free(root);
	}
}

void free_secondIndexCRDH(){
	free_CRDHTREE(secondIndexCRDH);
}

bool cmpRoom(char* Room1, char* Room2){
	int len = 0;
	bool result = 1;
	bool end = 0;
	if (strlen(Room1) < strlen(Room2)){
		len = strlen(Room1);
	} else {
		len = strlen(Room2);
	}
	for (int i = 0; (i < len) && !end; i++){
		if (Room1[i] < Room2[i]){
			end = 1;
		} else if (Room1[i] > Room2[i]){
			end = 1;
			result = 0;
		}
	}
	return result;
}

void insert_Node_CRDH(char* Room, CRDH p, CRDHTREE root){
	if (root != NULL){
		if (strcmp(Room, root->Room)==0){
			LinkedList_add_at_end(root->crdhs, p);
		} else {
			if (cmpRoom(Room, root->Room)){
				if (root->leftChild == NULL){
					root->leftChild = new_CRDHTREE(Room, p);
				} else {
					insert_Node_CRDH(Room, p, root->leftChild);
				}
			} else {
				if (root->rightChild == NULL){
					root->rightChild = new_CRDHTREE(Room, p);
				} else {
					insert_Node_CRDH(Room, p, root->rightChild);
				}
			}
		}
	}
}

void print_CRDHTREE(CRDHTREE root){
	if (root != NULL){
		printf("Room: %s ", root->Room);
		print_CRDHList(root->crdhs);
		print_CRDHTREE(root->leftChild);
		print_CRDHTREE(root->rightChild);
	}
}

void print_secondIndex_CRDH(){
	print_CRDHTREE(secondIndexCRDH);
}

void findCRDHList_helper(char* Room, CRDHTREE root, CRDHList list){
	if (root != NULL){
		if (strcmp(Room, root->Room)==0){
			LinkedListIterator iterator = LinkedList_iterator(root->crdhs);
			while (LinkedListIterator_hasNext(iterator)){
				CRDH crdh = LinkedListIterator_next(iterator);
				LinkedList_add_at_end(list, crdh);
				//print_CRDHList(list);
			}
			free(iterator);
		} else {
			if (cmpRoom(Room, root->Room)){
				findCRDHList_helper(Room, root->leftChild, list);
			} else {
				findCRDHList_helper(Room, root->rightChild, list);
			}
		}
	}
}

void findCRDHList(char* Room, CRDHList list){
	findCRDHList_helper(Room, secondIndexCRDH, list);
}

CRDH new_CRDH(char* Course, char* Room, char* Day, char* Hour){
	CRDH this = (CRDH)malloc(sizeof(struct CRDH));
	int lenCourse = strlen(Course);
	for (int i = 0; i < 5; i++){
		if (i < lenCourse){
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

int hash_CRDH(CRDH t){
	char Course[4];
	for (int i = 0; i < 3; i++){
		Course[i] = t->Course[i+2];
	}
	Course[3] = '\0';
	int key = atoi(Course);
	key = key % 2;
	return key;
}

void free_CRDHHashTable(CRDHHashTable R){
	for (int i = 0; i < 2; i++){
		if (R[i] != NULL){
			LinkedList_free(R[i], 1);
		}
	}
}

bool equal_CRDH(CRDH X, CRDH crdh){
	bool equal = 1;

	if (X->Course[0] != '*'){
		for (int i = 0; i < 5; i++){
			if (X->Course[i]!=crdh->Course[i]){
				equal = 0;
			}
		}
	}
	if (X->Room[0] != '*'){ // if the Room is specified
		for (int i = 0; i < 2; i++){
			if (X->Room[i]!=crdh->Room[i]){
				equal = 0;
			}
		}
	}
	if (X->Day[0] != '*'){ // if the Day is specified
		for (int i = 0; i < 2; i++){
			if (X->Day[i]!=crdh->Day[i]){
				equal = 0;
			}
		}
	}
	if (X->Hour[0] != '*'){ // if the Hour is specified
			for (int i = 0; i < 4; i++){
				if (X->Day[i]!=crdh->Day[i]){
					equal = 0;
				}
			}
		}
	return equal;
}

void insert_CRDH(CRDH t, CRDHHashTable R){
	int key = hash_CRDH(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_CRDH(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
	if (secondIndexCRDH == NULL){
		secondIndexCRDH = new_CRDHTREE(t->Room, t);
	} else {
		insert_Node_CRDH(t->Room, t, secondIndexCRDH);
	}
}

// assume that the components of key attributes will always be given
void delete_CRDH(CRDH X, CRDHHashTable R){
	int key = hash_CRDH(X);
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
CRDHList lookup_CRDH(CRDH X, CRDHHashTable R){
	CRDHList list = new_LinkedList();

	if (X->Course[0] == '*'){
		for (int key = 0; key < 2; key ++){
			LinkedListIterator iterator = LinkedList_iterator(R[key]);
			while (LinkedListIterator_hasNext(iterator)){
				CRDH crdh = LinkedListIterator_next(iterator);
				if (equal_CRDH(X, crdh)){
					LinkedList_add_at_end(list, crdh);
				}
			}
			free(iterator);
		}
	}

	int key = hash_CRDH(X);
	if (R[key] != NULL){
		LinkedListIterator iterator = LinkedList_iterator(R[key]);
		while (LinkedListIterator_hasNext(iterator)){
			CRDH crdh = LinkedListIterator_next(iterator);
			if (equal_CRDH(X, crdh)){
				LinkedList_add_at_end(list, crdh);
			}
		}
		free(iterator);
	}
	return list;
}
void print_CRDH(CRDH crdh){
	printf("%s %s %s %s\n", crdh->Course, crdh->Room, crdh->Day, crdh->Hour);
}

void print_CRDHList(CRDHList list){
	if (!LinkedList_isEmpty(list)){
		LinkedListIterator iterator = LinkedList_iterator(list);
		while (LinkedListIterator_hasNext(iterator)){
			CRDH crdh = LinkedListIterator_next(iterator);
			print_CRDH(crdh);
		}
		free(iterator);
	} else {
		printf("\n");
	}
}

void print_CRDHRelation(CRDHHashTable R){
	printf("Course Room Day Hour\n");
	for (int i = 0; i < 2; i++){
		if (R[i]!=NULL){
			print_CRDHList(R[i]);
		}
	}
}

void projectDayHour_CRDH(CRDHHashTable R, DHHashTable dhR){
	for (int i = 0; i < 2; i++){
		if (R[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(R[i]);
			while (LinkedListIterator_hasNext(iterator)){
				CRDH crdh = LinkedListIterator_next(iterator);
				DH dh = new_DH(crdh->Day, crdh->Hour);
				insert_DH(dh, dhR);
			}
			free(iterator);
		}
	}
}

void join_CR_CDH(CRHashTable crR, CDHHashTable cdhR, CRDHHashTable R){
	for (int i = 0; i < 1009; i++){
		if (cdhR[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(cdhR[i]);
			while (LinkedListIterator_hasNext(iterator)){
				CDH cdh = LinkedListIterator_next(iterator);
				char* Course = getCourse_CDH(cdh);
				CR cr = new_CR(Course, "*");
				CRList lookup = lookup_CR(cr, crR);
				LinkedListIterator iterator2 = LinkedList_iterator(lookup);
				while (LinkedListIterator_hasNext(iterator2)){
					CR cr2 = LinkedListIterator_next(iterator2);
					char* Day = getDay_CDH(cdh);
					char* Hour = getHour_CDH(cdh);
					char* Room = getRoom_CR(cr2);
					CRDH crdh = new_CRDH(Course, Room, Day, Hour);
					insert_CRDH(crdh, R);
				}
				free(iterator2);
			}
			free(iterator);
		}
	}
}


