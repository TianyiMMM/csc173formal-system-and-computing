
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CSG.h"
#include "SNAP.h"
#include "CP.h"

void loading(CSGHashTable csgR, SNAPHashTable snapR, CPHashTable cpR, CPHashTable cdhR, CPHashTable crR){
	enum relation{CSG, SNAP, CP, CDH, CR};
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("registrar.txt", "r");
	if (fp == NULL)
	    exit(EXIT_FAILURE);

	enum relation r;
	while ((read = getline(&line, &len, fp)) != -1) {
	    if(strcmp(line, "Course StudentId Grade\n")){
	    	r = CSG;
	    } else if (strcmp(line, "StudentId Name Address Phone\n")){
	    	r = SNAP;
	    } else if (strcmp(line, "Course Prerequisite\n")){
	    	r = CP;
	    } else if (strcmp(line, "Course Date Hour\n")){
	    	r = CDH;
	    } else if (strcmp(line, "Course Room\n")){
	    	r = CR;
	    } else if (r == CSG){
	    	insert_CSG()
	    }
	    printf("%s", line);
	}

	fclose(fp);
	if (line)
	    free(line);
	exit(EXIT_SUCCESS);
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

	// adding data to CSG relation table
	CSG csg1 = new_CSG("CS101", 12345, "A");
	CSG csg2 = new_CSG("CS101", 67890, "B");
	CSG csg3 = new_CSG("EE200", 12345, "C");
	CSG csg4 = new_CSG("EE200", 22222, "B+");
	CSG csg5 = new_CSG("CS101", 33333, "A-");
	CSG csg6 = new_CSG("PH100", 67890, "C+");
	insert_CSG(csg1, csgR);
	insert_CSG(csg2, csgR);
	insert_CSG(csg3, csgR);
	insert_CSG(csg4, csgR);
	insert_CSG(csg5, csgR);
	insert_CSG(csg6, csgR);
	print_CSGRelation(csgR);

	// looking up CSG tuple ("CS101", 12345, "*") in the table
	CSG csg = new_CSG("CS101", 12345, "*");
	CSGList list2 = lookup_CSG(csg, csgR);
	printf("lookup_CSG: ");
	print_CSGList(list2);

	// adding data to SNAP relation table
	SNAP snap1 = new_SNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
	SNAP snap2 = new_SNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
	SNAP snap3 = new_SNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
	insert_SNAP(snap1, snapR);
	insert_SNAP(snap2, snapR);
	insert_SNAP(snap3, snapR);
	print_SNAPRelation(snapR);

	// adding data to CP relation table
	CP cp1 = new_CP("CS101", "CS100");
	CP cp1 = new_CP("CS101", "CS100");

}


