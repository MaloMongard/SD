#ifndef GRAPHES_H
#define GRAPHES_h

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	F, M,
} sexe_t;

typedef struct Personne {
	char* nom;
	sexe_t sexe;
	struct Personne* pere;		  // vers le père
	struct Personne* mere;		  // vers la mère
	struct Personne* enfant_pere; // enfant provenant du même père
	struct Personne* enfant_mere; // enfant provenant de la même mère
	struct Personne* enfant;	  // vers un de ses enfants
	struct Personne* suivant;	  // vers le membre suivant
} Personne;

Personne* Personne_creer(char* nom, int sexe);
int Personne_seule(Personne* person);		// peut-être à enlever
void Personne_ajout(Personne* dernier, Personne* person);
void Personne_filiationPereEnfant(Personne* pere, Personne* enfant);
void Personne_filiationMereEnfant(Personne* mere, Personne* enfant);
void Personne_filiationParentsEnfant(Personne* pere, Personne* mere, Personne* enfant);
Personne* Personne_recherche(Personne* person, char* nom);
void Personne_afficher(Personne* person);
void Personne_suivantes(Personne* person);
Personne* Arbre_creer(char* nomFichier);

#endif