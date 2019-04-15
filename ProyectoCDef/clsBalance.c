/*
 * clsBalance.c
 *
 *  Created on: 9 abr. 2019
 *      Author: nereasolabarrieta
 */

#include "clsBalance.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void introducir(Balance * nuevoBalance) {
	float importeStock;
	float importeRealizable;
	float importeDisponible;
	float importeANC;
	float importePC;
	float importePNC;
	float importePN;

	do {
		printf("Introducir STOCK\n");
		scanf("%f", &importeStock);

		printf("Introducir REALIZABLE\n");
		scanf("%f", &importeRealizable);

		printf("Introducir DISPONIBLE\n");
		scanf("%f", &importeDisponible);

		printf("Introducir ACTIVO NO CORRIENTE\n");
		scanf("%f", &importeANC);

		printf("Introducir PASIVO CORRIENTE\n");
		scanf("%f", &importePC);

		printf("Introducir PASIVO NO CORRIENTE\n");
		scanf("%f", &importePNC);

		printf("Introducir PATRIMONIO NETO\n");
		scanf("%f", &importePN);

		if (!cuadra(importeStock, importeRealizable, importeDisponible,
				importeANC, importePC, importePNC, importePN)) {
			printf(
					"El balance no cuadra. Por favor, introduce otra vez los datos:\n");
		}

	} while (!cuadra(importeStock, importeRealizable, importeDisponible,
			importeANC, importePC, importePNC, importePN));

	nuevoBalance->importeANC = importeANC;
	nuevoBalance->importeDisponible = importeDisponible;
	nuevoBalance->importePC = importePC;
	nuevoBalance->importePN = importePN;
	nuevoBalance->importePNC = importePNC;
	nuevoBalance->importeRealizable = importeRealizable;
	nuevoBalance->importeStock = importeStock;


	escribir_ficBin(*(nuevoBalance));

}
bool cuadra(float importeStock, float importeRealizable,
		float importeDisponible, float importeANC, float importePC,
		float importePNC, float importePN) {

	int activo = importeStock + importeRealizable + importeDisponible
			+ importeANC;
	int pasivo = importePC + importePNC + importePN;
	if (activo == pasivo)
		return true;
	else
		return false;
}


void escribir_ficBin (Balance balance)
{
	FILE *f;
	f = fopen ( "Balance.dat", "wb" );
	fwrite(&(balance.importeANC),sizeof(float),1,f);
	fwrite(&(balance.importeStock),sizeof(float),1,f);
	fwrite(&(balance.importeRealizable),sizeof(float),1,f);
	fwrite(&(balance.importeDisponible),sizeof(float),1,f);
	fwrite(&(balance.importePN),sizeof(float),1,f);
	fwrite(&(balance.importePNC),sizeof(float),1,f);
	fwrite(&(balance.importePC),sizeof(float),1,f);

	fclose(f);

}

void leerFichero(Balance * balance)
{
	FILE *f;
	f=fopen("Balance.dat","rb");
	fread(&(balance->importeANC), sizeof(float),1,f);
	fread(&(balance->importeStock), sizeof(float),1,f);
	fread(&(balance->importeRealizable), sizeof(float),1,f);
	fread(&(balance->importeDisponible), sizeof(float),1,f);
	fread(&(balance->importePN), sizeof(float),1,f);
	fread(&(balance->importePNC), sizeof(float),1,f);
	fread(&(balance->importePC), sizeof(float),1,f);

}
bool existsFile(char* filename) {
	FILE* f = NULL;
	f = fopen(filename, "r");
	if (f == NULL)
		return false;
	else {
		fclose(f);
		return true;
	}
}
