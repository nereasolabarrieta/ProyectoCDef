/*
 * clsCliente.h
 *
 *  Created on: 9 abr. 2019
 *      Author: nereasolabarrieta
 */

#ifndef CLSCLIENTE_H_
#define CLSCLIENTE_H_

typedef struct {
	char* dni;
	char *nom;
	char *ape;
	float acumulado;
} Cliente;

void introducirCliente(Cliente *);
void imprimirCliente(Cliente);
void escribirFic_bin_clientes(Cliente* c, int num_clientes);
void LeerFic_bin_clientes(Cliente *c);

#endif /* CLSCLIENTE_H_ */
