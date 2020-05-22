#include "graphs.h"

//exercice 2 question 2
person* new_person(char* name, sex_t sex){
	person* p = malloc(sizeof(person));
	p->name = malloc(255*sizeof(char));
	strcpy(p->name, name);
	p->sex = sex;
	p->father = NULL;
	p->mother = NULL;
	p->father_child = p;
	p->mother_child = p;
	p->child = NULL;
	p->next = p;
	return p;
}

//exercice 2 question 3
int insert_person(person* new_p, person* last_p){
	new_p->next = last_p->next;
	last_p->next = new_p;
	return 0;
}

//exercice 2 question 4
int father_to_child(person* father, person* child){
	child->father = father;
	if (father->child != NULL){
		child->father_child = father->child;
	}
	father->child = child;
	return 0;
}

//exercice 2 question 5
int mother_to_child(person* mother, person* child){
	child->mother = mother;
	if (mother->child != NULL){
		child->mother_child = mother->child;
	}
	mother->child = child;
	return 0;
}

/*exercice 2 question 6
Je rappelle que strcmp(str1, str2) renvoie 0 si str1 == str2 
caractère par caractère*/
person* find_by_name(char* name, person* node){

	/*Ici j'utilise une fonction récursive auxiliaire
	pour garder en mémoire le premier noeud parcouru*/
	person* find_by_name_rec(person* actual_node){
		if (actual_node == NULL || 
			!strcmp(node->name, actual_node->name)){ 
			/*si node.name == actual_node.name alors 
			on a visité tout le graphe et la personne 
			cherchée n'y est pas*/
			return NULL;
		} else if (!strcmp(name, actual_node->name)) {
			//si on trouve un noeud du même nom alors on le renvoie
			return actual_node;
		} else {
			/*Si on a pas fini de parcourir le graphe et que
			l'on a pas trouvé un noeud du nom recherché, alors
			on continue de chercher sur le noeud suivant*/
			return find_by_name_rec(actual_node->next);
		}
	}
	if (!strcmp(name, node->name)){
		return node;
	} else {
		return find_by_name_rec(node->next);
	}
}

// exercice 2 question 7
char* str_sex(person* node){
	if (node->sex == F)
		return "Femme";
	else
		return "Homme";
}

int print_graph(person* node){
	printf("=========================================\n");
	printf("========== Affichage du graphe ==========\n");
	printf("=========================================\n");
	person* actual_node = node;
	char* name = (char*)malloc(255*sizeof(char));
	char* sex = (char*)malloc(255*sizeof(char));
	char* father = (char*)malloc(255*sizeof(char));
	char* mother = (char*)malloc(255*sizeof(char));
	char* father_child = (char*)malloc(255*sizeof(char));
	char* mother_child = (char*)malloc(255*sizeof(char));
	char* child = (char*)malloc(255*sizeof(char));
	char* next = (char*)malloc(255*sizeof(char));
	do {
		name = actual_node->name;
		sex = str_sex(actual_node);
		if (actual_node->father != NULL)
			strcpy(father, actual_node->father->name);
		else
			strcpy(father, "NULL");
		if (actual_node->mother != NULL)
			strcpy(mother, actual_node->mother->name);
		else
			strcpy(mother, "NULL");
		if (actual_node->father_child != NULL)
			strcpy(father_child, actual_node->father_child->name);
		else
			strcpy(father_child, "NULL");
		if (actual_node->mother_child != NULL)
			strcpy(mother_child, actual_node->mother_child->name);
		else
			strcpy(mother_child, "NULL");
		if (actual_node->child != NULL)
			strcpy(child, actual_node->child->name);
		else
			strcpy(child, "NULL");
		if (actual_node->next != NULL)
			strcpy(next, actual_node->next->name);
		else
			strcpy(next, "NULL");
		printf("----- Nouveau noeud -----\n");
		printf("nom: %s\n", name);
		printf("sexe: %s\n", sex);
		printf("père: %s\n", father);
		printf("mère: %s\n", mother);
		printf("enfant du père: %s\n", father_child);
		printf("enfant de la mère: %s\n", mother_child);
		printf("enfant: %s\n", child);
		printf("suivant: %s\n", next);
		printf("-------------------------\n");
		actual_node = actual_node->next;
	} while (strcmp(actual_node->name, node->name) != 0);
	return 0;
	//pas besoin de free les char* car le strcpy est sympa
}

//exercice 2 question 8
int free_person(person* p){
	free(p->father);
	free(p->mother);
	free(p->child);
	free(p->father_child);
	free(p->mother_child);
	free(p->next);
	free(p->name);
	free(p);
	return 0;
}

person* create_graph_from_file(char* file_name){
	FILE* file = fopen(file_name, "r");
	char* name = malloc(255*sizeof(char));
	char* father = malloc(255*sizeof(char));
	char* mother = malloc(255*sizeof(char));
	sex_t sex;
	char line[1000];
	char* str_token;
	const char* separators = ";";
	person* p;
	int nline = 1;
	int father_add = 0;
	int mother_add = 0;

	if (file != NULL){
		//Parcours du fichier, on récupère les 4 champs
		while (fgets(line, 1000, file) != NULL){
			str_token = strtok(line, separators);
			if (!strcmp(str_token, "F"))
				sex = F;
			else
				sex = M;
			str_token = strtok(NULL, separators);
			strcpy(name, str_token);
			str_token = strtok(NULL, separators);
			strcpy(father, str_token);
			str_token = strtok(NULL, separators);
			strcpy(mother, str_token);

			//si 1ere ligne alors initialisation
			if (nline == 1){
				p = new_person(name, sex);
				father_to_child(new_person(father, M), p);
				insert_person(p->father, p);
				mother_to_child(new_person(mother, F), p);
				insert_person(p->mother, p->father);
				p = p->mother;
			} else {
				insert_person(new_person(name, sex), p);
				p = p->next;
				if (find_by_name(father, p) == NULL){
					father_to_child(new_person(father, M), p);
					insert_person(p->father, p);
					father_add = 1;
				}
				else 
					father_to_child(find_by_name(father, p), p);
				if (find_by_name(mother, p) == NULL){
					mother_to_child(new_person(mother, F), p);
					if (father_add)
						insert_person(p->mother, p->father);
					else
						insert_person(p->mother, p);
					mother_add = 1;
				}
				else
					mother_to_child(find_by_name(mother, p), p);
				
			}
			if (father_add && !mother_add)
				p = p->father;
			if (mother_add)
				p = p->mother;
			++nline;
			father_add = 0;
			mother_add = 0;
		}
		fclose(file);
	} else {
		printf("Impossible d'ouvrir le fichier !\n");
		p = NULL;
	}
	free(name);
	free(father);
	free(mother);
	return p;
}

int main(){
	person* p = create_graph_from_file("./registre.txt");
	print_graph(p);
	free_person(p);
	return 0;
}