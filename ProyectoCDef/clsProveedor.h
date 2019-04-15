/*
 * clsProveedor.h
 *
 *  Created on: 9 abr. 2019
 *      Author: nereasolabarrieta
 */

#ifndef CLSPROVEEDOR_H_
#define CLSPROVEEDOR_H_

typedef struct
{
	char *NIF;
	char *nom;
}Proveedor;

void introducirProveedor(Proveedor *nuevoProveedor);
void ImprimirProv(Proveedor prov);
void LeerFic_bin_proveedores(Proveedor *p);
void escribirFic_bin_proveedores(Proveedor* p,int num_proveedores);

#endif /* CLSPROVEEDOR_H_ */
