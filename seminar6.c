#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod nod;
struct Nod {
	Masina info;
	nod* next;
};

//creare structura pentru un nod dintr-o lista simplu inlantuita

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	nod** vector;
};

typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(nod *cap) {
	
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(nod** cap, Masina masinaNoua) {
	
	nod* temp = (nod*)malloc(sizeof(nod));
	temp->info = masinaNoua;
	temp->next = NULL;
	if (*cap == NULL) {
		*cap = temp;
	}
	else
	{
		nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = temp;
		
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.vector = (nod*)malloc(dimensiune*sizeof(nod*));
	for (int i = 0;i < dimensiune;i++) {
		ht.vector[i] = NULL;
	}
	ht.dim = dimensiune;

	return ht;
}

int calculeazaHash(const char* numeSofer , int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
	// sum caractere ascii & dimensiune
	int suma = 0;
	if (dimensiune < 0)
		return -1;
	for (int i = 0;i < strlen(numeSofer);i++) {
		suma +=(int) numeSofer[i];
	}
	
	return suma % dimensiune; // hashcode
} 

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	//verif se face si in adaugaMasinaInLista
	int pozitie = calculeazaHash(masina.numeSofer, hash.dim);
	if (hash.vector[pozitie] == NULL)
	{ //nu avem coliziune
		adaugaMasinaInLista((&hash.vector[pozitie]), masina);

	}
	else
	{
		//avem coliziune
		adaugaMasinaInLista((&hash.vector[pozitie]), masina);
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier,int dim) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(dim);

	while (!feof(file)) {
		Masina m = citireMasinaDinFisier(file);
		inserareMasinaInTabela(ht, m);

	}
	return ht;
	fclose(file);

}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate
	for (int i = 0;i < ht.dim;i++) {
		if (ht.vector[i] != NULL) {
			printf("Clusterul %d \n", i);
			afisareListaMasini(ht.vector[i]);
		}
	}	
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie

}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	return NULL;
}

Masina getMasinaDupaCheie(HashTable ht, const char* numeSofer) {
	Masina m;
	m.id = -1;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	int pozitie = calculeazaHash(numeSofer, ht.dim);
	nod* temp = ht.vector[pozitie];
	while (temp) {
		if (strcmp(temp->info.numeSofer, numeSofer) == 0) {
			m = temp->info;
			m.numeSofer = (char*)malloc(strlen(temp->info.numeSofer) + 1);
			strcpy_s(m.numeSofer, strlen(temp->info.numeSofer) + 1, temp->info.numeSofer);
			m.model = (char*)malloc(strlen(temp->info.model) + 1);
			strcpy_s(m.model, strlen(temp->info.model) + 1, temp->info.model);
			m.nrUsi = temp->info.nrUsi;
			m.pret = temp->info.pret;
			m.serie = temp->info.serie;
			m.id = temp->info.id;
			return m;
		}
		temp = temp->next;
	}

	return m;
	
}

int main() {

	HashTable ht = citireMasiniDinFisier("masini.txt", 9);
	afisareTabelaDeMasini(ht);
	
	Masina cautata = getMasinaDupaCheie(ht, "alex");
	if (cautata.id != -1)
	{
		printf("Masina lui eefef este: \n");
		afisareMasina(cautata);
	}
	else
		printf("Masina nu a fost gasita\n");
	 
	return 0;
}