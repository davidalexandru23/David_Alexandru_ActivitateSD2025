#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Cladire {
	int id;
	char* nume;
	int an;
};


typedef struct Cladire Cladire;

struct Nod {
	Cladire info;
	struct Nod* next;
};

typedef struct Nod nod;

struct HashTable {
	int dim;
	nod** vector;
};

typedef struct HashTable HashTable;



Cladire citireCladireDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ".\n";
	char* aux;
	fgets(buffer, 100, file);
	Cladire c;
	aux = strtok(buffer, sep);
	c.id = atoi(aux);
	aux = strtok(NULL, sep);
	c.nume = malloc(strlen(aux)+1);
	strcpy_s(c.nume, strlen(aux) + 1, aux);
	c.an = atoi(strtok(NULL, sep));

	return c;


}


void afisareCladire(Cladire c)
{
	printf("Id: %d\n", c.id);
	printf("Nume: %s\n", c.nume);
	printf("An: %d\n", c.an);
	
}

void afisareListaCladiri(nod* cap)
{
	while (cap) {
		afisareCladire(cap->info);
		cap = cap->next;
	}
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.vector = (nod*)malloc(dimensiune * sizeof(nod*));
	for (int i = 0;i < dimensiune;i++) {
		ht.vector[i] = NULL;
	}
	ht.dim = dimensiune;

	return ht;
}

void inserareCladiriInTabela(HashTable ht, Cladire c)
{

}

HashTable citireCladiriDinFisier(const char* fisier, int dim)
{
	FILE* file;
	fopen(fisier, "r");
	HashTable ht = initializareHashTable(dim);
	while (!feof(file))
	{
		Cladire c = citireCladireDinFisier(file);
		inserareCladiriInTabela(ht, c);
	}

	return ht;
	fclose(file);
}


int main()
{
	HashTable ht = citireCladiriDinFisier("cladiri.txt", 10);

}


