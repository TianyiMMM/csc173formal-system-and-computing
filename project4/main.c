
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CSG.h"
#include "SNAP.h"
#include "CP.h"
#include "CDH.h"
#include "CR.h"

void loading(CSGHashTable csgR, SNAPHashTable snapR, CPHashTable cpR, CDHHashTable cdhR, CRHashTable crR){
	enum relation{CSGrel, SNAPrel, CPrel, CDHrel, CRrel};
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("registrar.txt", "r");
	if (fp == NULL)
	    exit(EXIT_FAILURE);

	enum relation r;
	char* delim = ",";
	while ((read = getline(&line, &len, fp)) != -1) {
		if (line[0]!='\n'){

	    if(strcmp(line, "Course StudentId Grade\n")==0){
	    	r = CSGrel;
	    } else if (strcmp(line, "StudentId Name Address Phone\n")==0){
	    	r = SNAPrel;
	    } else if (strcmp(line, "Course Prerequisite\n")==0){
	    	r = CPrel;
	    } else if (strcmp(line, "Course Day Hour\n")==0){
	    	r = CDHrel;
	    } else if (strcmp(line, "Course Room\n")==0){
	    	r = CRrel;
	    } else if (r == CSGrel){
	    	char* Course = strtok(line, delim);
	    	char* StudentIdstr = strtok(NULL, delim);
	    	int StudentId = atoi(StudentIdstr);
	    	char* Grade = strtok(NULL, delim);
	    	int len = strlen(Grade);
	    	if (Grade[strlen(Grade)-1]=='\n'){
	    		Grade[len-1] = 0;
	    	}
	    	CSG csg = new_CSG(Course, StudentId, Grade);
	    	insert_CSG(csg, csgR);
	    } else if (r == SNAPrel){
	    	char* StudentIdstr = strtok(line, delim);
	    	int StudentId = atoi(StudentIdstr);
	    	char* Name = strtok(NULL, delim);
	    	char* Address = strtok(NULL, delim);
	    	char* Phone = strtok(NULL, delim);
	    	int len = strlen(Phone);
	    	if (Phone[strlen(Phone)-1]=='\n'){
	    		Phone[len-1] = 0;
	    	}
	    	SNAP snap = new_SNAP(StudentId, Name, Address, Phone);
	    	insert_SNAP(snap, snapR);
	    } else if (r == CPrel){
	    	char* Course = strtok(line, delim);
	    	char* Prerequisite = strtok(NULL, delim);
	    	int len = strlen(Prerequisite);
	    	if (Prerequisite[strlen(Prerequisite)-1]=='\n'){
	    		Prerequisite[len-1] = 0;
	    	}
	    	CP cp = new_CP(Course, Prerequisite);
	    	insert_CP(cp, cpR);
	    } else if (r == CDHrel){
	    	char* Course = strtok(line, delim);
	    	char* Day = strtok(NULL, delim);
	    	char* Hour = strtok(NULL, delim);
	    	int len = strlen(Hour);
	    	if (Hour[strlen(Hour)-1]=='\n'){
	    		Hour[len-1] = 0;
	    	}
	    	CDH cdh = new_CDH(Course, Day, Hour);
	    	insert_CDH(cdh, cdhR);
	    } else if (r == CRrel){
	    	char* Course = strtok(line, delim);
	    	char* Room = strtok(NULL, delim);
	    	int len = strlen(Room);
	    	if (Room[strlen(Room)-1]=='\n'){
	    		Room[len-1] = 0;
	    	}
	    	CR cr = new_CR(Course, Room);
	    	insert_CR(cr, crR);
	    }

		}
	}

	fclose(fp);
	if (line)
	    free(line);
}

void saving(CSGHashTable csgR, SNAPHashTable snapR, CPHashTable cpR, CDHHashTable cdhR, CRHashTable crR){
	FILE *f = fopen("registrar.txt", "w"); // open an empty text file "registrar.txt"
	printf("printing\n");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}

	fprint_CSGRelation(csgR, f);
	fprintf(f, "\n");
	fprint_SNAPRelation(snapR, f);
	fprintf(f, "\n");
	fprint_CPRelation(cpR, f);
	fprintf(f, "\n");
	fprint_CDHRelation(cdhR, f);
	fprintf(f, "\n");
	fprint_CRRelation(crR, f);

	fclose(f);
}

int main(int argc, char** argv) {
	printf("CSC173 Project 4 by Tianyi Ma\n\n");

	CSGHashTable csgR;
	SNAPHashTable snapR;
	CPHashTable cpR;
	CPHashTable cdhR;
	CPHashTable crR;
	// initiating relation tables
	for (int i = 0; i < 1009; i++){
		csgR[i] = NULL;
		snapR[i] = NULL;
		cpR[i] = NULL;
		cdhR[i] = NULL;
		crR[i] = NULL;
	}

	loading(csgR, snapR, cpR, cdhR, crR);

	printf("Demonstrating basic single-relation operations...\n");
	// looking up CSG tuple ("CS101", 12345, "*") in the table
	CSG csg = new_CSG("CS101", 12345, "*");
	CP cp1 = new_CP("CS205", "CS120");
	CP cp2 = new_CP("CS205", "CS101");
	CR cr = new_CR("CS101", "*");

	CSGList lookup1 = lookup_CSG(csg, csgR);
	CSGList lookup2 = lookup_CP(cp1, cpR);
	printf("looking up (CS101, 12345, *): ");
	print_CSGList(lookup1);
	printf("looking up (CS205, CS120): ");
	print_CSGList(lookup2);

	printf("\nCourse-Room relation: \n");
	print_CRRelation(crR);
	printf("\n");
	delete_CR(cr, crR);
	printf("deleting (CS101, *): \n");
	print_CRRelation(crR);
	printf("\n");

	printf("Course-Prerequisite relation: \n");
	print_CPRelation(cpR);
	printf("\n");
	insert_CP(cp1, cpR);
	printf("inserting (CS205, CS120): \n");
	print_CPRelation(cpR);
	printf("\n");
	insert_CP(cp2, cpR);
	printf("inserting (CS205, CS101): \n");
	print_CPRelation(cpR);
	printf("\n");


	free_CSGHashTable(csgR);
	free_SNAPHashTable(snapR);
	free_CPHashTable(cpR);
	free_CDHHashTable(cdhR);
	free_CRHashTable(crR);
}


