/*
 * clsArticulo.c
 *
 *  Created on: 14/4/2019
 *      Author: ALUMNO
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "clsArticulo.h"
#include "clsBalance.h"
#include "clsCliente.h"
#define TAMANYO 20
int num_complementos = 0;

void anyadirComplemento(Complemento * complementos, int tamanyo,
		Balance * balance) {

	char codigo[10];
	printf("Introduce el codigo:\n");
	fflush(stdin);
	scanf("%s", codigo);

	if (comprobar_complemento(complementos, tamanyo, codigo)) {
		char cod_vacio[] = "0000000000";
		for (int i = 0; i < tamanyo; i++) {
			if (strcmp((complementos + i)->articulo.codigo, cod_vacio) == 0) {

				char *nom;
				nom = (char*) malloc(TAMANYO * sizeof(char));
				printf("Introduce el nombre:\n");
				fflush(stdin);
				scanf("%s", nom);

				int len = strlen(nom);
				((complementos + i)->articulo).nombre = (char*) malloc(
						len * sizeof(char));
				strcpy(((complementos + i)->articulo).nombre, nom);

				((complementos + i)->articulo).codigo = malloc(
						10 * sizeof(char));
				strcpy(((complementos + i)->articulo).codigo, codigo);

				float precio;
				printf("Introduce el precio:\n");
				scanf("%f", &precio);
				fflush(stdin);
				(complementos + i)->articulo.precio = precio;

				int stock;
				printf("Introduce stock\n");
				scanf("%i", &stock);

				(complementos + i)->stock = stock;
				escribir_fic_bin_complementos(complementos, i + 1);
				free(nom);
				Contabilizar_complemento(*(complementos + i), stock, balance);
				break;
			}
		}

	} else {
		for (int i = 0; i < tamanyo; i++) {
			if (strcmp((complementos + i)->articulo.codigo, codigo) == 0) {
				printf("El articulo que ha comprado es el siguiente: \n");
				Imprimir_complemento(*(complementos + i));

				printf("Cuantos articulos ha comprado?\n");
				fflush(stdin);
				int compra;
				scanf("%i", &compra);
				(complementos + i)->stock = ((complementos + i)->stock)
						+ compra;
				escribir_fic_bin_complementos(complementos, i + 1);
				Contabilizar_complemento(*(complementos + i), compra, balance);

			}

		}
	}
}
void anyadirTextil(Textil * textiles, int tamanyo, Balance * balance) {
	char codigo[10];
	printf("Introduce el codigo:\n");

	scanf("%s", codigo);
	fflush(stdin);
	if (comprobar_textil(textiles, tamanyo, codigo)) {

		char cod_vacio[] = "0000000000";

		for (int i = 0; i < tamanyo; i++) {

			if (strcmp((textiles + i)->articulo.codigo, cod_vacio) == 0) {

				char *nom;
				nom = (char*) malloc(TAMANYO * sizeof(char));
				printf("Introduce el nombre:\n");
				fflush(stdin);
				scanf("%s", nom);

				int len = strlen(nom);
				((textiles + i)->articulo).nombre = (char*) malloc(
						len * sizeof(char));
				strcpy(((textiles + i)->articulo).nombre, nom);

				float precio;
				printf("Introduce el precio:\n");
				scanf("%f", &precio);
				fflush(stdin);

				int stockXS;
				printf("Introduce stock de talla XS\n");
				scanf("%i", &stockXS);

				int stockS;
				printf("Introduce stock de talla S\n");
				scanf("%i", &stockS);

				int stockM;
				printf("Introduce stock de talla M\n");
				scanf("%i", &stockM);

				int stockL;
				printf("Introduce stock de talla L\n");
				scanf("%i", &stockL);

				char *col;
				col = (char*) malloc(TAMANYO * sizeof(char));
				printf("Introduce color del articulo\n");
				scanf("%s", col);

				len = strlen(col);
				(textiles + i)->color = (char*) malloc(len * sizeof(char));
				strcpy((textiles + i)->color, col);

				((textiles + i)->articulo).codigo = malloc(10 * sizeof(char));
				strcpy(((textiles + i)->articulo).codigo, codigo);

				(textiles + i)->articulo.precio = precio;
				(textiles + i)->stockXS = stockXS;
				(textiles + i)->stockS = stockS;
				(textiles + i)->stockM = stockM;
				(textiles + i)->stockL = stockL;

				escribir_fic_bin_textil(textiles, i + 1);
				int compra = stockXS + stockS + stockM + stockL;
				Contabilizar_textil(*(textiles + i), compra, balance);

				break;
			}
		}

	} else {
		for (int i = 0; i < tamanyo; i++) {
			if (strcmp((textiles + i)->articulo.codigo, codigo) == 0) {
				printf("El articulo que ha comprado es el siguiente: \n");
				Imprimir_textil(*(textiles + i));
				int compraXS;
				int compraS;
				int compraM;
				int compraL;

				printf("Cuantos articulos ha comprado de la talla XS?\n");
				fflush(stdin);
				scanf("%i", &compraXS);

				printf("Y de la talla S?\n");
				fflush(stdin);
				scanf("%i", &compraS);

				printf("Y de la talla M?\n");
				fflush(stdin);
				scanf("%i", &compraM);

				printf("Y de la talla L?\n");
				fflush(stdin);
				scanf("%i", &compraL);

				(textiles + i)->stockXS = ((textiles + i)->stockXS) + compraXS;
				(textiles + i)->stockS = ((textiles + i)->stockS) + compraS;
				(textiles + i)->stockM = ((textiles + i)->stockM) + compraM;
				(textiles + i)->stockL = ((textiles + i)->stockL) + compraL;
				escribir_fic_bin_textil(textiles, i + 1);

				int compra = compraXS + compraS + compraM + compraL;
				Contabilizar_textil(*(textiles + i), compra, balance);

			}

		}
	}
}

bool comprobar_textil(Textil * textiles, int tamanyo, char * codigo) {
	char cod_vacio[] = "0000000000";
	bool unico = true;
	for (int i = 0; i < tamanyo; i++) {
		if (strcmp((textiles + i)->articulo.codigo, cod_vacio) != 0) {
			if (strcmp((textiles + i)->articulo.codigo, codigo) == 0) {
				unico = false;
			}

		}
	}
	return unico;
}

bool comprobar_complemento(Complemento * complementos, int tamanyo,
		char * codigo) {
	char cod_vacio[] = "0000000000";
	bool unico = true;
	for (int i = 0; i < tamanyo; i++) {
		if (strcmp((complementos + i)->articulo.codigo, cod_vacio) != 0) {
			if (strcmp((complementos + i)->articulo.codigo, codigo) == 0) {
				unico = false;
			}

		}
	}
	return unico;
}

void Contabilizar_complemento(Complemento complemento, int cantidad,
		Balance * balance) {

	float precio = complemento.articulo.precio;
	float cuantia = cantidad * precio;
	(balance->importePC) = (balance->importePC) + cuantia;
	(balance->importeStock) = (balance->importeStock) + cuantia;
	escribir_ficBin(*(balance));
}

void Contabilizar_textil(Textil textil, int cantidad, Balance * balance) {
	float precio = textil.articulo.precio;
	float cuantia = cantidad * precio;
	balance->importePC = balance->importePC + cuantia;
	balance->importeStock = balance->importeStock + cuantia;
	escribir_ficBin(*(balance));

}

void Contabilizar_Ventacomplemento(Complemento complemento, int cantidad,
		Balance * balance) {

	float precio = complemento.articulo.precio;
	float cuantia = cantidad * precio;
	(balance->importeDisponible) = (balance->importeDisponible) + cuantia;
	(balance->importeStock) = (balance->importeStock) - cuantia;
	escribir_ficBin(*(balance));

}

void Contabilizar_Ventatextil(Textil textil, int cantidad, Balance * balance) {
	float precio = textil.articulo.precio;
	float cuantia = cantidad * precio;
	(balance->importeDisponible) = (balance->importeDisponible) + cuantia;
	(balance->importeStock) = (balance->importeStock) - cuantia;
	escribir_ficBin(*(balance));

}

void Imprimir_complemento(Complemento complemento) {
	printf("Nombre: %s, Codigo: %s, Precio: %f, Stock: %i \n",
			complemento.articulo.nombre, complemento.articulo.codigo,
			complemento.articulo.precio, complemento.stock);
}

void Imprimir_textil(Textil textil) {
	printf(
			"Nombre: %s, Codigo: %s, Precio: %f, Color: %s, StockXS: %i, StockS: %i, StockM: %i, StockL: %i \n",
			textil.articulo.nombre, textil.articulo.codigo,
			textil.articulo.precio, textil.color, textil.stockXS, textil.stockS,
			textil.stockM, textil.stockL);
}

void VentaComplemento(Complemento *complementos, int tamanyo, Balance *balance,
		Cliente * cliente) {

	char *codigo = malloc(10 * sizeof(char));
	int cantidad;
	bool disponible = false;
	do {
		printf("Introduce el codigo del complemento:\n");

		fflush(stdin);
		scanf("%s", codigo);

		if (comprobar_complemento(complementos, tamanyo, codigo)) {

			printf("No existe ningun complemento con ese codigo.\n");

		} else {

			for (int i = 0; i < tamanyo; i++) {

				if (strcmp((complementos + i)->articulo.codigo, codigo) == 0) {

					printf("El articulo que ha vendido es el siguiente: \n");

					Imprimir_complemento(*(complementos + i));

					do {
						printf("Cuantos articulos ha vendido?\n");

						fflush(stdin);

						scanf("%d", &cantidad);

						if ((complementos->stock) < cantidad) {
							printf(
									"No tiene suficiente stock para realizar esa venta.\n");
							disponible = false;
						} else {
							(complementos + i)->stock =
									((complementos + i)->stock) - cantidad;
							escribir_fic_bin_complementos(complementos, i + 1);
							Contabilizar_Ventacomplemento(*(complementos + i),
									cantidad, balance);
							disponible = true;
						}
						enviarImporte((complementos + i)->articulo.precio,
								cantidad, cliente);
					} while (disponible == false);

				}

			}
			printf("La venta se ha guardado correctamente\n\n\n");
		}

	} while (comprobar_complemento(complementos, tamanyo, codigo));

}
void enviarImporte(float precio, int cantidad, Cliente * cliente) {
	float acumulado;
	acumulado = precio * cantidad;
	cliente->acumulado = cliente->acumulado + acumulado;
}
void VentaTextil(Textil *textiles, int tamanyo, Balance *balance,
		Cliente * cliente) {
	char *codigo = malloc(10 * sizeof(char));
	int cantidadXS;
	int cantidadS;
	int cantidadM;
	int cantidadL;
	bool disponible = false;
	int TOTAL;
	do {
		printf("Introduce el codigo del articulo:\n");

		fflush(stdin);
		scanf("%s", codigo);

		if (comprobar_textil(textiles, tamanyo, codigo)) {

			printf("No existe ningun complemento con ese codigo.\n");

		} else {

			for (int i = 0; i < tamanyo; i++) {

				if (strcmp((textiles + i)->articulo.codigo, codigo) == 0) {

					printf("El articulo que ha vendido es el siguiente: \n");

					Imprimir_textil(*(textiles + i));

					do {
						printf("Cuantos articulos de talla XS ha vendido?\n");
						fflush(stdin);
						scanf("%i", &cantidadXS);

						if ((textiles->stockXS) < cantidadXS) {
							printf(
									"No tiene suficiente stock para realizar esa venta.\n");
							disponible = false;
						} else {
							(textiles + i)->stockXS = ((textiles + i)->stockXS)
									- cantidadXS;
							disponible = true;

						}
					} while (disponible == false);
					do {
						printf("Cuantos articulos de talla S ha vendido?\n");
						fflush(stdin);
						scanf("%i", &cantidadS);

						if ((textiles->stockS) < cantidadS) {
							printf(
									"No tiene suficiente stock para realizar esa venta.\n");
							disponible = false;
						} else {
							((textiles + i)->stockS = ((textiles + i)->stockS)
									- cantidadS);
							disponible = true;
						}
					} while (disponible == false);
					do {
						printf("Cuantos articulos de talla M ha vendido?\n");
						fflush(stdin);
						scanf("%i", &cantidadM);

						if ((textiles->stockM) < cantidadM) {
							printf(
									"No tiene suficiente stock para realizar esa venta.\n");
							disponible = false;
						} else {
							(textiles + i)->stockM = ((textiles + i)->stockM
									- cantidadM);
							disponible = true;

						}
					} while (disponible == false);
					do {
						printf("Cuantos articulos de talla L ha vendido?\n");
						fflush(stdin);
						scanf("%i", &cantidadL);

						if ((textiles->stockL) < cantidadL) {
							printf(
									"No tiene suficiente stock para realizar esa venta.\n");
							disponible = false;
						} else {
							(textiles + i)->stockL = ((textiles + i)->stockL
									- cantidadL);
							disponible = true;

						}
					} while (disponible == false);

					TOTAL = cantidadXS + cantidadS + cantidadM + cantidadL;
					escribir_fic_bin_textil(textiles, i + 1);

					enviarImporte((textiles + i)->articulo.precio, TOTAL,
							cliente);
					Contabilizar_Ventatextil(*(textiles + i), TOTAL, balance);

				}

			}
			printf("La venta se ha guardado correctamente\n\n\n");
		}

	} while (comprobar_textil(textiles, tamanyo, codigo));
}

void escribir_fic_bin_complementos(Complemento* c, int num_complementos) {
	FILE *f;
	f = fopen("Complementos.dat", "wb");
	fputc(num_complementos, f);
	int len = 0;
	for (int i = 0; i < num_complementos; i++) {
		fputc((c + i)->stock, f);
		len = strlen((c + i)->articulo.codigo) + 1;
		fputc(len, f);
		fwrite((c + i)->articulo.codigo, sizeof(char), len, f);
		len = strlen((c + i)->articulo.nombre) + 1;
		fputc(len, f);
		fwrite((c + i)->articulo.nombre, sizeof(char), len, f);
		fwrite(&((c + i)->articulo.precio), sizeof(float), 1, f);
	}
	fclose(f);

}

void LeerFic_bin_complementos(Complemento* c) {

	FILE *f;
	f = fopen("Complementos.dat", "rb");

	num_complementos = fgetc(f);
	int len = 0;
	for (int i = 0; i < num_complementos; i++) {

		(c + i)->stock = fgetc(f);

		len = fgetc(f);
		(c + i)->articulo.codigo = malloc(len * sizeof(char));
		fread((c + i)->articulo.codigo, sizeof(char), len, f);

		len = fgetc(f);
		(c + i)->articulo.nombre = malloc(len * sizeof(char));
		fread((c + i)->articulo.nombre, sizeof(char), len, f);

		fread(&((c + i)->articulo.precio), sizeof(float), 1, f);

	}

	fclose(f);

}

void escribir_fic_bin_textil(Textil* t, int num_complementos) {
	FILE *f;
	f = fopen("Textil.dat", "wb");
	fputc(num_complementos, f);
	int len = 0;
	for (int i = 0; i < num_complementos; i++) {
		fputc((t + i)->stockXS, f);
		fputc((t + i)->stockS, f);
		fputc((t + i)->stockM, f);
		fputc((t + i)->stockL, f);
		len = strlen((t + i)->articulo.codigo) + 1;
		fputc(len, f);
		fwrite((t + i)->articulo.codigo, sizeof(char), len, f);
		len = strlen((t + i)->color) + 1;
		fputc(len, f);
		fwrite((t + i)->color, sizeof(char), len, f);
		len = strlen((t + i)->articulo.nombre) + 1;
		fputc(len, f);
		fwrite((t + i)->articulo.nombre, sizeof(char), len, f);
		fwrite(&((t + i)->articulo.precio), sizeof(float), 1, f);

	}
	fclose(f);

}

void LeerFic_bin_textil(Textil* t) {

	FILE *f;
	f = fopen("Textil.dat", "rb");

	num_complementos = fgetc(f);
	int len = 0;
	for (int i = 0; i < num_complementos; i++) {

		(t + i)->stockXS = fgetc(f);
		(t + i)->stockS = fgetc(f);
		(t + i)->stockM = fgetc(f);
		(t + i)->stockL = fgetc(f);

		len = fgetc(f);
		(t + i)->articulo.codigo = malloc(len * sizeof(char));
		fread((t + i)->articulo.codigo, sizeof(char), len, f);

		len = fgetc(f);
		(t + i)->color = malloc(len * sizeof(char));
		fread((t + i)->color, sizeof(char), len, f);

		len = fgetc(f);
		(t + i)->articulo.nombre = malloc(len * sizeof(char));
		fread((t + i)->articulo.nombre, sizeof(char), len, f);

		fread(&((t + i)->articulo.precio), sizeof(float), 1, f);
	}

	fclose(f);

}
