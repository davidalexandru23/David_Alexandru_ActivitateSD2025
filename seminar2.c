#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <string.h>
struct Masina {
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};
struct Masina initializare(int id, int nrKm, const char* model, float pret, char tipMotor)
{
	struct Masina m;
	m.id = id;
	m.nrKm = nrKm;
	m.pret = pret;
	m.tipMotor = tipMotor;
	m.model = (const char*)malloc(strlen(model) * sizeof(const char) + 1);
	strcpy_s(m.model,strlen(model)+1, model);
	return m;
}

void afisare(struct Masina m)
{
	printf("ID: %d\nNrKm: %d\nModel: %s\nPret: %.2f\nTipMotor: %c\n\n", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	struct Masina* vectorNou = malloc(sizeof(struct Masina) * nrElementeCopiate);
	if (vector != NULL && nrElementeCopiate > 0)
	{
		if (nrElementeCopiate > nrElemente) {
			nrElementeCopiate = nrElemente;
		}
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = initializare(vector[i].id, vector[i].nrKm, vector[i].model, vector[i].pret, vector[i].tipMotor);


		
		}
	}
	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	for (int i = 0;i < (*nrElemente);i++)
	{
		if ((*vector)[i].model != NULL)
		{
			free((*vector)[i].model);
			
		}
		
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaMasiniIeftine(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {

	for (int i = 0;i < nrElemente;i++)
	{
		if (vector[i].pret < prag)
		{
			
		}
	}
}
	


int main() {
	int n = 3;

	struct Masina *vec;
	vec = malloc(sizeof(struct Masina) * n);
	vec[0] = initializare(1, 100, "Audi", 10000, 'D');
	vec[1] = initializare(2, 200, "BMW", 20000, 'B');
	vec[2] = initializare(3, 300, "Logan", 30000, 'D');
	afisareVector(vec, n);

	int nrElementeCopiate = 2;
	struct Masina* vectorNou = copiazaPrimeleNElemente(vec, n, nrElementeCopiate);
	printf("\n\elemente copiate:\n");
	afisareVector(vectorNou, nrElementeCopiate);
	dezalocare(&vectorNou, &nrElementeCopiate);
	return 0;
}