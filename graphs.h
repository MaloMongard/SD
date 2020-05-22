#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	F, M,
} sex_t;

//exercice 2 question 1
typedef struct person {
	char* name;
	sex_t sex;
	struct person* father;			// vers le père
	struct person* mother;			// vers la mère
	struct person* father_child; 	// enfant du père
	struct person* mother_child; 	// enfant de la mère
	struct person* child;	  		// vers un de ses enfants
	struct person* next;	  		// vers le membre suivant
} person;

person* new_person(char* name, sex_t sex);
int insert_person(person* new_p, person* last_p);
int father_to_child(person* father, person* child);
int mother_to_child(person* mother, person* child);
person* find_by_name(char* name, person* node);
char* str_sex(person* node);
char* field_or_null(person* field);
int print_graph(person* node);
int free_graph(person* g);
person* create_graph_from_file(char* file_name);

#endif