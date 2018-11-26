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

struct NODE {
	char Name[30];
	SNAPList snaps;
	TREE leftChild, rightChild;
};

TREE secondIndexSNAP = NULL;

TREE new_TREE(char* Name, SNAP p){
	TREE this = (TREE) malloc(sizeof(struct NODE));
	for (int i = 0; i < 30; i++){
		if (i < strlen(Name)){
			this->Name[i] = Name[i];
		} else {
			this->Name[i] = 0;
		}
	}
	this->snaps = new_LinkedList();
	LinkedList_add_at_end(this->snaps, p);
	this->leftChild = NULL;
	this->rightChild = NULL;
	return this;
}

void free_TREE(TREE root){
	if (root != NULL){
		free(root->Name);
		LinkedList_free(root->snaps, 1);
		print_TREE(root->leftChild);
		print_TREE(root->rightChild);
		free(root);
	}
}

void free_secondIndexSNAP(){
	free_TREE(secondIndexSNAP);
}

// determine if Name1 comes alphabetically earlier than Name2
bool cmpName(char* Name1, char* Name2){
	int len = 0;
	bool result = 1;
	bool end = 0;
	if (strlen(Name1) < strlen(Name2)){
		len = strlen(Name1);
	} else {
		len = strlen(Name2);
	}
	for (int i = 0; (i < len) && !end; i++){
		if (Name1[i] < Name2[i]){
			end = 1;
		} else if (Name1[i] > Name2[i]){
			end = 1;
			result = 0;
		}
	}
	return result;
}

void insert_Node(char* Name, SNAP p, TREE root){
	if (root != NULL){
		if (strcmp(Name, root->Name)==0){
			LinkedList_add_at_end(root->snaps, p);
		} else {
			if (cmpName(Name, root->Name)){
				if (root->leftChild == NULL){
					root->leftChild = new_TREE(Name, p);
				} else {
					insert_Node(Name, p, root->leftChild);
				}
			} else {
				if (root->rightChild == NULL){
					root->rightChild = new_TREE(Name, p);
				} else {
					insert_Node(Name, p, root->rightChild);
				}
			}
		}
	}
}

void print_TREE(TREE root){
	if (root != NULL){
		printf("Name: %s ", root->Name);
		print_SNAPList(root->snaps);
		print_TREE(root->leftChild);
		print_TREE(root->rightChild);
	}
}

void print_secondIndex_SNAP(){
	print_TREE(secondIndexSNAP);
}

void findSNAPList_helper(char* Name, TREE root, SNAPList list){
	if (root != NULL){
		if (strcmp(root->Name, Name)==0){
			LinkedListIterator iterator = LinkedList_iterator(root->snaps);
			while (LinkedListIterator_hasNext(iterator)){
				SNAP snap = LinkedListIterator_next(iterator);
				LinkedList_add_at_end(list, snap);
			}
			free(iterator);
		} else {
			if (cmpName(Name, root->Name)){
				findSNAPList_helper(Name, root->leftChild, list);
			} else {
				findSNAPList_helper(Name, root->rightChild, list);
			}
		}
	}
}

void findSNAPList(char* Name, SNAPList list){
	findSNAPList_helper(Name, secondIndexSNAP, list);
}

int getStudentId_SNAP(SNAP snap){
	return snap->StudentId;
}

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
	key = key % 2;
	return key;
}

void free_SNAPHashTable(SNAPHashTable R){
	for (int i = 0; i < 2; i++){
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
	if (LinkedList_isEmpty(lookup_SNAP(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
	if (secondIndexSNAP == NULL){
		secondIndexSNAP = new_TREE(t->Name, t);
	} else {
		insert_Node(t->Name, t, secondIndexSNAP);
	}
}

// assume that the components of key attributes will always be given
void delete_SNAP(SNAP X, SNAPHashTable R){
	int key = hash_SNAP(X);
	if (R[key] != NULL){
		if (X->Name[0]!='*' && X->Address[0]!='*' && X->Phone[0]!='*'){
			LinkedList_remove(R[key], X);
		} else if (X->Name[0] =='*' && X->Address[0] =='*' && X->Phone[0] =='*'){
			while (!LinkedList_isEmpty(R[key])){
				LinkedList_pop(R[key]);
			}
		} else {
			LinkedListIterator iterator = LinkedList_iterator(R[key]);
			while (LinkedListIterator_hasNext(iterator)){
				SNAP snap = LinkedListIterator_next(iterator);
				if (equal_SNAP(X, snap)){
					LinkedList_remove(R[key], snap);
				}
			}
			free(iterator);
		}
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
	for (int i = 0; i < 2; i++){
		if (R[i]!=NULL){
			print_SNAPList(R[i]);
		}
	}
}

void fprint_SNAPRelation(SNAPHashTable R, FILE *f){
	fprintf(f, "StudentId Name Address Phone\n");
	for (int i = 0; i < 2; i++){
		if (R[i]!=NULL){
			LinkedListIterator iterator = LinkedList_iterator(R[i]);
			while (LinkedListIterator_hasNext(iterator)){
				SNAP snap = LinkedListIterator_next(iterator);
				fprintf(f, "%d %s %s %s\n", snap->StudentId, snap->Name, snap->Address, snap->Phone);
			}
			free(iterator);
		}
	}
}

