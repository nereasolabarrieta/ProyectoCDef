#include "clsProveedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANYO 20
int num_proveedores = 0;
void introducirProveedor(Proveedor *nuevoProveedor) {
	nuevoProveedor->NIF = malloc(10 * sizeof(char));
	printf("Introduce NIF:\n");
	fflush(stdin);
	scanf("%s", nuevoProveedor->NIF);

	char *nom;
	nom = (char*) malloc(TAMANYO * sizeof(char));
	printf("Introduce NOMBRE\n");
	fflush(stdin);
	scanf("%s", nom);

	int len = strlen(nom);
	nuevoProveedor->nom = (char*) malloc(len * sizeof(char));
	strcpy(nuevoProveedor->nom, nom);

	fflush(stdin);

	escribirFic_bin_proveedores(nuevoProveedor, 1);
}

void escribirFic_bin_proveedores(Proveedor* p, int num_proveedores) {

	FILE *f;
	f = fopen("Proveedores.dat", "wb");
	fputc(num_proveedores, f);
	int len = 0;
	for (int i = 0; i < num_proveedores; i++) {

		len = strlen((p + i)->nom) + 1;
		fputc(len, f);
		fwrite((p + i)->nom, sizeof(char), len, f);
		len = strlen((p + i)->NIF) + 1;
		fputc(len, f);
		fwrite((p + i)->NIF, sizeof(char), len, f);

	}
	fclose(f);

}

void LeerFic_bin_proveedores(Proveedor *p) {

	FILE *f;
	f = fopen("Proveedores.dat", "rb");

	num_proveedores = fgetc(f);
	int len = 0;
	for (int i = 0; i < num_proveedores; i++) {

		len = fgetc(f);
		(p + i)->nom = malloc(len * sizeof(char));
		fread((p + i)->nom, sizeof(char), len, f);

		len = fgetc(f);
		(p + i)->NIF = malloc(len * sizeof(char));
		fread((p + i)->NIF, sizeof(char), len, f);

	}

	fclose(f);

}
void ImprimirProv(Proveedor prov) {
	printf("[Nombre: %s, NIF: %s ]\n", prov.nom, prov.NIF);
}

