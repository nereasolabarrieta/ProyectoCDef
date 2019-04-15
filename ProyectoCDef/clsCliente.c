/*
 * clsCliente.c
 *
 *  Created on: 13/4/2019
 *      Author: ALUMNO
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "clsCliente.h"

#define TAMANYO 30
int num_clientes=0;

void introducirCliente(Cliente * nuevoCliente) {

	nuevoCliente->dni = malloc(10 * sizeof(char));
	printf("Introduce DNI:\n");
	fflush(stdin);
	scanf("%s", nuevoCliente->dni);

	char *nom;
	nom = (char*) malloc(TAMANYO * sizeof(char));
	printf("Introduce NOMBRE\n");
	fflush(stdin);
	scanf("%s", nom);

	int len = strlen(nom);
	nuevoCliente->nom = (char*) malloc(len * sizeof(char));
	strcpy(nuevoCliente->nom, nom);

	char *ape;
	ape = (char*) malloc(TAMANYO * sizeof(char));
	printf("Introduce APELLIDO\n");
	fflush(stdin);
	scanf("%s", ape);

	len = strlen(ape);
	nuevoCliente->ape = (char*) malloc(len * sizeof(char));
	strcpy(nuevoCliente->ape, ape);

	nuevoCliente->acumulado = 0.0;

	fflush(stdin);
	escribirFic_bin_clientes(nuevoCliente,1);


}

void escribirFic_bin_clientes(Cliente* c,int num_clientes) {

	FILE *f;
	f = fopen("Clientes.dat", "wb");
	fputc(num_clientes,f);
	int len=0;
	for(int i=0; i<num_clientes; i++)
	{

		fwrite(&((c+i)->acumulado),sizeof(float),1,f);
		len=strlen((c+i)->nom)+1;
		fputc(len,f);
		fwrite((c+i)->nom,sizeof(char),len,f);
		len=strlen((c+i)->ape)+1;
		fputc(len,f);
		fwrite((c+i)->ape,sizeof(char),len,f);
		fwrite((c+i)->dni,sizeof(char),11,f);

	}
	fclose(f);

}

void LeerFic_bin_clientes(Cliente *c) {

	FILE *f;
	f = fopen("Clientes.dat", "rb");

		num_clientes=fgetc(f);
		int len=0;
		for(int i=0;i<num_clientes;i++)
			{

			fread(&((c+i)->acumulado),sizeof(float),1,f);

			len=fgetc(f);
			(c+i)->nom=malloc(len*sizeof(char));
			fread((c+i)->nom,sizeof(char),len,f);

			len=fgetc(f);
			(c+i)->ape=malloc(len*sizeof(char));
			fread((c+i)->ape,sizeof(char),len,f);


			(c+i)->dni=malloc(11*sizeof(char));
			fread((c+i)->dni,sizeof(char),11,f);


	}

	fclose(f);

}


void imprimirCliente(Cliente cl) {
	printf("Nombre %s %s, dni: %s, dinero: %f euro\n", cl.nom, cl.ape, cl.dni,
			cl.acumulado);
}

