#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "stack.h"

#ifndef _parsing_table_h_gf
#define _parsing_table_h_gf

#include <stdbool.h>


extern void parseTable(int parsing_table[8][128]);
extern bool isNonTerminal(char* s);
extern int find_index(char* s);
extern Stack add_production(int grammar);
extern TREE makeNode(int grammar);
extern TREE parse(char*in);



#endif
