/*
 * clsBalance.h
 *
 *  Created on: 9 abr. 2019
 *      Author: nereasolabarrieta
 */
#include <stdbool.h>

#ifndef CLSBALANCE_H_
#define CLSBALANCE_H_

typedef struct
{
	float importeStock;
	float importeRealizable;
	float importeDisponible;
	float importeANC;
	float importePC;
	float importePNC;
	float importePN;
}Balance;

void introducir();
bool existsFile(char*);
void leerFichero(Balance*);
void escribir_ficBin(Balance);
bool cuadra(float importeStock, float importeRealizable,float importeDisponible, float importeANC,float importePC,float importePNC,float importePN);


#endif /* CLSBALANCE_H_ */
