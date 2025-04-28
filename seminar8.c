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

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Masina info;
	struct Nod* st;
	struct Nod* dr;
};


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore(Nod** nod, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID


	if ((*nod) != NULL) {
	if (masinaNoua.id > (*nod)->info.id)
	{
		adaugaMasinaInArbore(&(*nod)->dr, masinaNoua);

	}

	if (masinaNoua.id < (*nod)->info.id)
	{
		adaugaMasinaInArbore(&(*nod)->st, masinaNoua);
	}

	if (masinaNoua.id == (*nod)->info.id)
	{
		printf("Masina cu id-ul %d exista deja in arbore!\n", masinaNoua.id);
		return;
	}
 }
	else
	{
		(*nod) = (Nod*)malloc(sizeof(Nod));
		(*nod)->info = masinaNoua;
		(*nod)->st = NULL;
		(*nod)->dr = NULL;
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");

	Nod* nod = NULL;
	if (f == NULL) {
		printf("Eroare la deschiderea fisierului %s\n", numeFisier);
		return NULL;
	}

	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		if (m.id != 0) {
			adaugaMasinaInArbore(&nod, m);
		}
	}
	fclose(f);
	return nod;


}

void afisareMasiniDinArbore(/*arbore de masini*/) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere

}
void afisarePreordine(Nod* nod) {
	if (nod != NULL) {
		afisareMasina(nod->info);
		afisarePreordine(nod->st);
		afisarePreordine(nod->dr);
	}
}
void afisareInordine(Nod* nod) {
	if (nod != NULL) {
		afisareInordine(nod->st);
		afisareMasina(nod->info);
		afisareInordine(nod->dr);
	}
}
void afisarePostordine(Nod* nod) {
	if (nod != NULL) {
		afisarePostordine(nod->st);
		afisarePostordine(nod->dr);
		afisareMasina(nod->info);
	}
}
void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

Masina getMasinaByID(Nod* radacina ,int id) {
	Masina m;
	if (radacina!=NULL)
	{
		if (radacina->info.id == id)
		{
			return radacina->info;
		}
		else
		{
			if (id < radacina->info.id)
			{
				m = getMasinaByID(radacina->st, id);
			}
			else
			{
				m = getMasinaByID(radacina->dr, id);
			}
		}
	}
	else
	{
		m.id = 0;
		m.nrUsi = 0;
		m.pret = 0;
		m.model = NULL;
		m.numeSofer = NULL;
		m.serie = 0;
		printf("Masina cu id-ul %d nu exista in arbore!\n", id);
	}
	
	
	return m;
}

int determinaNumarNoduri(Nod* rad) {
	//calculeaza numarul total de noduri din arborele binar de cautare

	if (rad == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + determinaNumarNoduri(rad->st) + determinaNumarNoduri(rad->dr);
	}
	
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

	Nod* rad=citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisarePreordine(rad); 
	return 0;
}