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

void afisareVectorDrone(Drona* drone, int nrDrone) {
	for (int i = 0; i < nrDrone; i++) {
		printf("Drona %d:\n", i + 1);
		afisareDrona(drone[i]);
	}
}

void afisareDrona(Drona d) {

	printf("Id: %d\n", d.id);
	printf("Denumire: %s\n", d.denumire);
	printf("Greutate: %.2f\n", d.capacitate);
	printf("Autonomie: %.2f\n", d.autonomie);
	printf("Pret: %.2f\n", d.pret);

}

void dezalocareDrona(Drona* d) {
	if (d->denumire != NULL) {
		free(d->denumire);
		d->denumire = NULL;
	}
}

int main()
{
	Drona d;
	int n = 5;
	Drona* drone = (Drona*)malloc(n * sizeof(Drona));
	for (int i = 0; i < n; i++) {
		drone[i] = initializareDrona(i + 1, "Drona", 5.0, 10.0, 100.0);
	}


	
	d = citireDronaTastatura(d);
	afisareDrona(d);
	printf("\n");
	printf("Performanta dronei este: %.2f\n", performanta(d));
	d = actualizarePret(d, 55.5);
	printf("\n");
	afisareDrona(d);
	
	return 0;
}


