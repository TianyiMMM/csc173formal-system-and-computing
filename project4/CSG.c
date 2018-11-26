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

struct CSGNODE {
	int StudentId;
	CSGList csgs;
	CSGTREE leftChild, rightChild;
};

CSGTREE secondIndexCSG = NULL;

CSGTREE new_CSGTREE(int StudentId, CSG p){
	CSGTREE this = (CSGTREE) malloc(sizeof(struct CSGNODE));

	this->StudentId = StudentId;

	this->csgs = new_LinkedList();
	LinkedList_add_at_end(this->csgs, p);
	this->leftChild = NULL;
	this->rightChild = NULL;
	return this;
}

void free_CSGTREE(CSGTREE root){
	if (root != NULL){
		LinkedList_free(root->csgs, 1);
		print_CSGTREE(root->leftChild);
		print_CSGTREE(root->rightChild);
		free(root);
	}
}

void free_secondIndexCSG(){
	free_CSGTREE(secondIndexCSG);
}

void insert_Node_CSG(int StudentId, CSG p, CSGTREE root){
	if (root != NULL){
		if (StudentId == root->StudentId){
			LinkedList_add_at_end(root->csgs, p);
		} else {
			if (StudentId < root->StudentId){
				if (root->leftChild == NULL){
					root->leftChild = new_CSGTREE(StudentId, p);
				} else {
					insert_Node_CSG(StudentId, p, root->leftChild);
				}
			} else {
				if (root->rightChild == NULL){
					root->rightChild = new_CSGTREE(StudentId, p);
				} else {
					insert_Node_CSG(StudentId, p, root->rightChild);
				}
			}
		}
	}
}

void print_CSGTREE(CSGTREE root){
	if (root != NULL){
		printf("StudentId: %d ", root->StudentId);
		print_CSGList(root->csgs);
		print_CSGTREE(root->leftChild);
		print_CSGTREE(root->rightChild);
	}
}

void print_secondIndex_CSG(){
	print_CSGTREE(secondIndexCSG);
}

void findCSGList_helper(int StudentId, CSGTREE root, CSGList list){
	if (root != NULL){
		if (root->StudentId == StudentId){
			LinkedListIterator iterator = LinkedList_iterator(root->csgs);
			while (LinkedListIterator_hasNext(iterator)){
				CSG csg = LinkedListIterator_next(iterator);
				LinkedList_add_at_end(list, csg);
			}
			free(iterator);
		} else {
			if (StudentId < root->StudentId){
				findCSGList_helper(StudentId, root->leftChild, list);
			} else {
				findCSGList_helper(StudentId, root->rightChild, list);
			}
		}
	}
}

void findCSGList(int StudentId, CSGList list){
	findCSGList_helper(StudentId, secondIndexCSG, list);
}

char* getCourse_CSG(CSG csg){
	return csg->Course;
}

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
	key = key % 2;
	return key;
}

void free_CSGHashTable(CSGHashTable R){
	for (int i = 0; i < 2; i++){
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

char* getGrade_CSG(CSG csg){
	return csg->Grade;
}

void insert_CSG(CSG t, CSGHashTable R){
	int key = hash_CSG(t);
	if (R[key] == NULL){
		R[key] = new_LinkedList();
	}
	if (LinkedList_isEmpty(lookup_CSG(t, R))){
		LinkedList_add_at_end(R[key], t);
	}
	if (secondIndexCSG == NULL){
		secondIndexCSG = new_CSGTREE(t->StudentId, t);
	} else {
		insert_Node_CSG(t->StudentId, t, secondIndexCSG);
	}
}

// assume that the components of key attributes will always be given
void delete_CSG(CSG X, CSGHashTable R){
	int key = hash_CSG(X);
	if (R[key] != NULL){
		if (X->Grade[0]!='*'){
			LinkedList_remove(R[key], X);
		} else {
			while (!LinkedList_isEmpty(R[key])){
				LinkedList_pop(R[key]);
			}
		}
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
	for (int i = 0; i < 2; i++){
		if (R[i]!=NULL){
			print_CSGList(R[i]);
		}
	}
}

void fprint_CSGRelation(CSGHashTable R, FILE *f){
	fprintf(f, "Course StudentId Grade\n");
	for (int i = 0; i < 2; i++){
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




