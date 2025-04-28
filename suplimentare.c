#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	





struct Drona {
    int id;
    char* denumire;
    float capacitate; // kg
    float autonomie; // minute
	float pret;
};


typedef struct Drona Drona;

Drona initializareDrona(int id, const char* denumire, float capacitate, float autonomie, float pret) {
	Drona d;
	d.id = id;
	d.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(d.denumire, strlen(denumire) + 1, denumire);
	d.capacitate = capacitate;
	d.autonomie = autonomie;
	d.pret = pret;
	return d;
}

Drona citireDronaTastatura(Drona d) {
	printf("Introduceti id-ul dronei: ");
	scanf("%d", &d.id);
	printf("Introduceti denumirea dronei: ");
	d.denumire = malloc(100);
	scanf("%s", d.denumire);
	printf("Introduceti greutatea dronei: ");
	scanf("%f", &d.capacitate);
	printf("Introduceti autonomia dronei: ");
	scanf("%f", &d.autonomie);
	printf("Introduceti pretul dronei: ");
	scanf("%f", &d.pret);
	return d;
}

float performanta(Drona d) {
	float p;

	p = (d.capacitate * d.autonomie) / d.pret;
	return p;
}

Drona actualizarePret(Drona d, float pretNou) {
	if (pretNou > 0) {
		d.pret = pretNou;
	}
	return d;
}
Drona* adaugareDronaInVector(Drona* drone, int* nrDrone, Drona d) {
	Drona* temp = (Drona*)malloc((*nrDrone + 1) * sizeof(Drona));
	for (int i = 0; i < *nrDrone; i++) {
		temp[i] = drone[i];
	}
	temp[*nrDrone] = d;
	(*nrDrone)++;
	free(drone);
	return temp;
}
Drona vectorDroneAlese(Drona* drone, int nrDrone, int* nrDroneAlese,float perf) {
	Drona* droneAlese = (Drona*)malloc(nrDrone * sizeof(Drona));
	*nrDroneAlese = 0;
	for (int i = 0; i < nrDrone; i++) {
		if (performanta(drone[i]) > perf) {
			droneAlese[*nrDroneAlese] = drone[i];
			(*nrDroneAlese)++;
		}
	}
	return *droneAlese;
}

Drona vectorDroneAlesePret(Drona* drone, int nrDrone, int* nrDroneAlese, float pret) {
	Drona* droneAlese = (Drona*)malloc(nrDrone * sizeof(Drona));
	*nrDroneAlese = 0;
	for (int i = 0; i < nrDrone; i++) {
		if (drone[i].pret > 400) {
			droneAlese[*nrDroneAlese] = drone[i];
			(*nrDroneAlese)++;
		}
	}
	return *droneAlese;
}

Drona concatenareDrone(Drona* drone1, int nrDrone1, Drona* drone2, int nrDrone2) {
	Drona* droneConcatenate = (Drona*)malloc((nrDrone1 + nrDrone2) * sizeof(Drona));
	for (int i = 0; i < nrDrone1; i++) {
		droneConcatenate[i] = drone1[i];
	}
	for (int i = 0; i < nrDrone2; i++) {
		droneConcatenate[nrDrone1 + i] = drone2[i];
	}
	return *droneConcatenate;
}

void afisareDrona(Drona d) {

	printf("Id: %d\n", d.id);
	printf("Denumire: %s\n", d.denumire);
	printf("Greutate: %.2f\n", d.capacitate);
	printf("Autonomie: %.2f\n", d.autonomie);
	printf("Pret: %.2f\n", d.pret);

}

void afisareVectorDrone(Drona* drone, int nrDrone) {
	for (int i = 0; i < nrDrone; i++) {
		printf("Drona %d:\n", i + 1);
		afisareDrona(drone[i]);
	}
}



Drona citireDronaDinFisier(FILE* file) {
	
	
	char sep[3] = ",\n";
	char line[101];
	char* buffer;
	fgets(line, 100, file);
	Drona temp;
	buffer = strtok(line, sep);
	temp.id = atoi(buffer);
	
	buffer = strtok(NULL, sep);
	if (buffer == NULL) return temp;
	temp.denumire = malloc(strlen(buffer) + 1);
	strcpy_s(temp.denumire, (strlen(buffer) + 1), buffer);

	temp.capacitate = atof(strtok(NULL, sep));
	temp.autonomie = atof(strtok(NULL, sep));
	temp.pret = atof(strtok(NULL, sep));

	



	return temp;
}

Drona* citireDronaInVectorFisier(const char* fisier, int *nrDrone) {
	FILE* file = fopen(fisier, "r");
	if (!file) {
		printf("Nu s-a putut deschide fisierul.\n");
		return NULL;
	}
	char line[101];
	Drona* drone = NULL;
	Drona temp;
	int n = 0;
	//while (!feof(file)) {
	while (fgets(line, sizeof(line), file)){
		temp = citireDronaDinFisier(file);
		drone=adaugareDronaInVector(drone, &n, temp);

	}
	*nrDrone = n;
	fclose(file);
	return drone;
}

Drona** grupareDronePeCapacitate(Drona* drone, int nrDrone, int* nrLinii, int** nrElemPeLinie) {
	*nrLinii = 3; // 
	Drona** matrice = (Drona**)malloc((*nrLinii) * sizeof(Drona*));
	*nrElemPeLinie = (int*)calloc(*nrLinii, sizeof(int)); 

	
	for (int i = 0; i < nrDrone; i++) {
		float c = drone[i].capacitate;
		int index = (c < 2) ? 0 : (c <= 3 ? 1 : 2);
		(*nrElemPeLinie)[index]++;
	}

	
	for (int i = 0; i < *nrLinii; i++) {
		matrice[i] = (Drona*)malloc((*nrElemPeLinie)[i] * sizeof(Drona));
		(*nrElemPeLinie)[i] = 0; 
	}

	
	for (int i = 0; i < nrDrone; i++) {
		float c = drone[i].capacitate;
		int index = (c < 2) ? 0 : (c <= 3 ? 1 : 2);
		matrice[index][(*nrElemPeLinie)[index]++] = initializareDrona(
			drone[i].id, drone[i].denumire, drone[i].capacitate, drone[i].autonomie, drone[i].pret
		);
	}

	return matrice;
}

void afisareMatriceDrone(Drona** matrice, int nrLinii, int* nrElemPeLinie) {
	for (int i = 0; i < nrLinii; i++) {
		printf("Cluster %d (%d drone):\n", i + 1, nrElemPeLinie[i]);
		for (int j = 0; j < nrElemPeLinie[i]; j++) {
			afisareDrona(matrice[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

void sortareLiniiDupaNumarDrone(Drona*** matrice, int* nrLinii, int** nrElemPeLinie) {
	for (int i = 0; i < *nrLinii - 1; i++) {
		for (int j = i + 1; j < *nrLinii; j++) {
			if ((*nrElemPeLinie)[i] > (*nrElemPeLinie)[j]) {
				
				int aux = (*nrElemPeLinie)[i];
				(*nrElemPeLinie)[i] = (*nrElemPeLinie)[j];
				(*nrElemPeLinie)[j] = aux;

				
				Drona* temp = (*matrice)[i];
				(*matrice)[i] = (*matrice)[j];
				(*matrice)[j] = temp;
			}
		}
	}
}


void dezalocareDrona(Drona* d) {
	if (d->denumire != NULL) {
		free(d->denumire);
		d->denumire = NULL;
	}
}

int main()
{/*
	Drona d;
	int n = 5;
	Drona* drone = (Drona*)malloc(n * sizeof(Drona));
	for (int i = 0; i < n; i++) {
		drone[i] = initializareDrona(i + 1, "Drona", 5.0, 10.0, 100.0);
	}*/
	Drona* drone = NULL;
	int n = 0;
	
	drone = citireDronaInVectorFisier("drone.txt", &n);
	afisareVectorDrone(drone, n);
	int nrLinii;
	int* nrElemPeLinie;
	Drona** matrice = grupareDronePeCapacitate(drone, n, &nrLinii, &nrElemPeLinie);

	printf("\nMatrice originala:\n");
	afisareMatriceDrone(matrice, nrLinii, nrElemPeLinie);

	sortareLiniiDupaNumarDrone(&matrice, &nrLinii, &nrElemPeLinie);

	printf("\nMatrice dupa sortare:\n");
	afisareMatriceDrone(matrice, nrLinii, nrElemPeLinie);
	
	/*d = citireDronaTastatura(d);
	afisareDrona(d);
	printf("\n");
	printf("Performanta dronei este: %.2f\n", performanta(d));
	d = actualizarePret(d, 55.5);
	printf("\n");
	afisareDrona(d);*/
	
	return 0;
}


