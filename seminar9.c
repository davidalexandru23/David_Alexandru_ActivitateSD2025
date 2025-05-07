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
struct Nod
{
	Masina info;
	struct Nod* stanga;
	struct Nod* dreapta;
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
void rotireStanga(Nod** nod)
{
	Nod* nodAux = (*nod)->dreapta;
	(*nod)->dreapta = nodAux->stanga;
	nodAux->stanga = (*nod);
	(*nod) = nodAux;
}
void rotireDreapta(Nod** nod)
{
	Nod* nodAux = (*nod)->stanga;
	(*nod)->stanga = nodAux->dreapta;
	nodAux->dreapta = (*nod);
	(*nod) = nodAux;
}

void adaugaMasinaInArboreEchilibrat(Nod**  arbore , Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if ((*arbore)!=NULL)
	{ 
		if ((*arbore)->info.id < masinaNoua.id)
		{
			adaugaMasinaInArboreEchilibrat((&(*arbore)->dreapta), masinaNoua);

		}
		else
		{
			adaugaMasinaInArboreEchilibrat((&(*arbore)->stanga), masinaNoua);
		}
		int e = calculeazaEchilibru((*arbore));
		if (e == 2)
		{
			if (calculeazaEchilibru((*arbore)->stanga == 1))
			{
				rotireStanga(&(*arbore)->stanga);
				rotireDreapta(&(*arbore));

			}
		
		}
		else if (e == -2)
		{
			if (calculeazaEchilibru((*arbore)->stanga == -1))
			{
				rotireDreapta(&(*arbore)->dreapta);
				rotireStanga(&(*arbore));
			}
		}
	}
	else
	{
		(*arbore) = malloc(sizeof(Nod));
		(*arbore)->info = masinaNoua;
		(*arbore)->stanga = NULL;
		(*arbore)->dreapta = NULL;
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");

	Nod* nou = NULL;
	if (f == NULL) {
		printf("Eroare la deschiderea fisierului %s\n", numeFisier);
		return NULL;
	}

	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		if (m.id != 0) {
			adaugaMasinaInArboreEchilibrat(&nou, m);
		}
	}
	fclose(f);
	return nou;


}

void afisarePreordine(Nod* nod) {
	if (nod != NULL) {
		afisareMasina(nod->info);
		afisarePreordine(nod->stanga);
		afisarePreordine(nod->dreapta);
	}
}
void afisareInordine(Nod* nod) {
	if (nod != NULL) {
		afisareInordine(nod->stanga);
		afisareMasina(nod->info);
		afisareInordine(nod->dreapta);
	}
}
void afisarePostordine(Nod* nod) {
	if (nod != NULL) {
		afisarePostordine(nod->stanga);
		afisarePostordine(nod->dreapta);
		afisareMasina(nod->info);
	}
}

void afisareMasiniDinArbore(/*arbore de masini*/) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

Masina getMasinaByID(/*arborele de masini*/int id) {
	Masina m;

	return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(Nod* nod) {

	if (nod == NULL) {
		return 0;
	}
	else
	{int inaltimeStanga = 0;
	int inaltimeDreapta = 0;

	inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
	inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);
	return 1 + (inaltimeStanga > inaltimeDreapta ? inaltimeStanga : inaltimeDreapta);
	}
	 
}

//calculeaza grad de echilibru al arborelui

int calculeazaEchilibru(Nod* nod)
{
	if (nod == NULL) {
		return 0;
	}
	else
	{
		int inaltimeStanga = 0;
		int inaltimeDreapta = 0;
		inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
		inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);
		return inaltimeStanga - inaltimeDreapta;
	}
}

//rotire arbore 



float calculeazaPretTotal(Nod* nod) {
	//calculeaza pretul tuturor masinilor din arbore.
	if (nod == NULL)
	{
		return 0;
	}
	else
	{
		float sumas = calculeazaPretTotal(nod->stanga);
		float sumad = calculeazaPretTotal(nod->dreapta);
		
		return sumas + sumad;

		
	}
	
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
	afisareInordine(&arbore);

	return 0;
}