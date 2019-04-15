#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "clsBalance.h"
#include "clsProveedor.h"
#include "clsCliente.h"
#include "clsMenuPrincipal.h"
#include "clsArticulo.h"

#define NUM_PROV 20
#define NUM_CLIENTES 100
#define NUM_ARTIC 30

Balance *nuestro_balance;
Cliente *clientes;
Proveedor *proveedores;
Textil * textiles;
Complemento * complementos;

int main(void) {

	clientes = (Cliente *) malloc(NUM_CLIENTES * sizeof(Cliente));
	proveedores = (Proveedor *) malloc(NUM_PROV * sizeof(Proveedor));
	nuestro_balance = (Balance *) malloc(sizeof(Balance));
	textiles= (Textil*)malloc(NUM_ARTIC*sizeof(Textil));
	complementos= (Complemento*)malloc(NUM_ARTIC*sizeof(Complemento));
	menuPrincipal();
	return 0;

}
void menuPrincipal() {
	char dni_vacio[] = "0000000000";

	for (int i = 0; i < NUM_CLIENTES; i++) {
	(clientes + i)->dni = dni_vacio;

	}

	for (int i = 0; i < NUM_PROV; i++) {
		(proveedores + i)->NIF = dni_vacio;
	}

	for (int i = 0; i < NUM_ARTIC; i++) {
			((textiles + i)->articulo).codigo= dni_vacio;
			((complementos + i)->articulo).codigo= dni_vacio;
		}



// si existe clientes.txt meterlos en el array
// si existe provedorees.txt meterlos en el array

	if (!existsFile("Balance.dat"))
	{
		introducirBalance();
		menu();
	}
	else
	{
		if (existsFile("Clientes.dat"))
		{
			LeerFic_bin_clientes(clientes);
		}
		if (existsFile("Proveedores.dat"))
		{
			LeerFic_bin_proveedores(proveedores);
		}
		if (existsFile("Complementos.dat"))
		{
			LeerFic_bin_complementos(complementos);
		}
		if (existsFile("Textil.dat"))
		{
			LeerFic_bin_textil(textiles);
		}
			leerFichero(nuestro_balance);

		menu();
	}

}

void menu() {
	char opcion;

	do {

		printf("\n 1. Introducir cliente");
		printf("\n 2. Introducir proveedor");
		printf("\n 3. Contabilizar venta"); // identificar cliente--> dni (sacarle por pantalla),identificar articulo (textil o complemento) introducir codigo, (talla) stock-1.,
		printf("\n 4. Contabilizar compra");
		printf("\n 5. Visualizar estado contable"); //imprimier balance
		printf("\n 6. Visualizar todos los clientes");
		printf("\n 7. Visualizar todos los proveedores");
		printf("\n 8. Visualizar todos los complementos");
		printf("\n 9. Visualizar todos los textiles");
		printf("\n *. Editar balance");
		printf("\n 0. Salir");

		printf(" \n\n Introduzca una opcion del 0-*:");

		fflush(stdin);
		scanf("%s", &opcion);
		switch (opcion) {
		case '1':
			introducirC();
			break;
		case '2':
			introducirP();
			break;
		case '3':ContabilizarVenta();
			break;
		case '4': compra();
			break;
		case '5':imprimirBalance();
			break;
		case '6': imprimirClientes();
			break;
		case '7': imprimirProv();
			break;
		case '8': imprimirComplementos();
			break;
		case '9': imprimirTextil();
			break;
		case '*': introducirBalance();
					break;
		case '0':
			free(clientes);
			clientes = NULL;
			free(nuestro_balance);
			nuestro_balance =NULL;
			free(textiles);
			textiles =NULL;
			free(complementos);
			complementos =NULL;
			free(proveedores);
			proveedores =NULL;
			printf("Agur");
			break;
		default:
			printf("Esa opcion no esta disponible\n");
		}
	} while (opcion != '0');
}
void introducirBalance() {
	printf("A continuacion introduzca su balance en masas patrimoniales:\n");
	introducir(nuestro_balance);
}

void introducirC() {
	char dni_vacio[] = "0000000000";
	for (int i = 0; i < NUM_CLIENTES; i++) {
		if (strcmp((clientes + i)->dni, dni_vacio) == 0) {
			printf("entra %i \n", i + 1);
			introducirCliente(clientes + i);
			escribirFic_bin_clientes(clientes,i+1);

			break;
		}
	}
}

void introducirP() {
	char dni_vacio[] = "0000000000";
	for (int i = 0; i < NUM_PROV; i++) {
		if (strcmp((proveedores + i)->NIF, dni_vacio) == 0) {
			introducirProveedor(proveedores + i);
			escribirFic_bin_proveedores(proveedores,i+1);
			break;
		}
	}

}



void compra() {
	char opcion;
	do {

		printf("\nQue tipo de articulo desea introducir?\n");
		printf("1-Complemento\n");
		printf("2-Textil\n");
		printf("0-Salir\n");
		fflush(stdin);
		scanf("%s", &opcion);
		switch (opcion) {
		case '1':
			anyadirComplemento(complementos,NUM_ARTIC,nuestro_balance);
			break;
		case '2':
			anyadirTextil(textiles,NUM_ARTIC,nuestro_balance);
			break;
		case '0':
			printf("Agur");
			break;
		default:
			printf("Esa opcion no existe.");
		}
	} while (!(opcion == '1' || opcion == '2' || opcion=='0') );

}

void imprimirClientes() {
	char dni_vacio[] = "0000000000";
	for (int i = 0; i < NUM_CLIENTES; i++) {
		if (strcmp((clientes + i)->dni, dni_vacio) != 0)
		{
			imprimirCliente(*(clientes + i));
		}
	}
}

void imprimirProv() {
	char dni_vacio[] = "0000000000";
	for (int i = 0; i < NUM_PROV; i++) {
		if (strcmp((proveedores + i)->NIF, dni_vacio) != 0) {

			ImprimirProv(*(proveedores + i));
		}
	}
}

void imprimirBalance ()
{
	float totalA= nuestro_balance->importeANC+nuestro_balance->importeDisponible+nuestro_balance->importeStock+nuestro_balance->importeRealizable;
	float totalP= nuestro_balance->importePC+nuestro_balance->importePN+nuestro_balance->importePNC;
	printf( "TOTAL ACTIVO: %f eu\n",totalA);
		printf( "Activo no corriente: %f\n",nuestro_balance->importeANC);
		printf( "Activo corriente: %f\n",nuestro_balance->importeDisponible+nuestro_balance->importeStock+nuestro_balance->importeRealizable);
		printf( "1. Stock: %f\n",nuestro_balance->importeStock);
		printf( "2. Realizable: %f\n",nuestro_balance->importeRealizable);
		printf( "3. Disponible: %f\n",nuestro_balance->importeDisponible);

		printf( "--------------------------\n");


		printf( "TOTAL PASIVO Y PATRIMONIO NETO: %f\n",totalP);
		printf( "PAtrimonio neto: %f\n",nuestro_balance->importePN);
		printf("Pasivo no corriente: %f\n",nuestro_balance->importePNC);
		printf( "Pasivo corriente: %f\n",nuestro_balance->importePC);
}

void ContabilizarVenta(){
	bool existe=false;
	char *dni = malloc(10 * sizeof(char));
	do
	{
	printf("Introduce el DNI del cliente que ha realizado la compra:\n");

	fflush(stdin);
	scanf("%s", dni);


	for (int i = 0; i < NUM_CLIENTES; i++) {
		if (strcmp((clientes + i)->dni, dni) == 0) {
			printf("El cliente correspondiente a este DNI es el siguiente: \n");
			imprimirCliente(*(clientes + i));
			existe=true;
			char opcion;
				do {

				printf("Que tipo de venta desea contabilizar?\n");
				printf("1-Complemento\n");
				printf("2-Textil\n");
				printf("0-Salir\n");
				fflush(stdin);
				scanf("%s", &opcion);
				switch (opcion) {
				case '1':
					VentaComplemento(complementos,NUM_ARTIC, nuestro_balance,(clientes + i));
					escribirFic_bin_clientes(clientes,i+1);
					break;
				case '2':
					VentaTextil(textiles,NUM_ARTIC, nuestro_balance,(clientes + i));
					escribirFic_bin_clientes(clientes,i+1);
					break;
				case '0':
					printf("Salir");
					break;
				default:
					printf("Esa opcion no existe.");
				}
			} while  (!(opcion == '1' || opcion == '2' || opcion == '0') );
			break;
		}
	}
	if(existe==false)
	{
		printf("No existe ningun cliente con ese DNI\n");
	}

	}while(existe==false);


}
void imprimirComplementos()
{
	char dni_vacio[] = "0000000000";
			for (int i = 0; i < NUM_ARTIC; i++) {

				if (strcmp((complementos + i)->articulo.codigo, dni_vacio) != 0) {

					Imprimir_complemento(*(complementos + i));
				}
			}
}
void imprimirTextil()
{
	char dni_vacio[] = "0000000000";
				for (int i = 0; i < NUM_ARTIC; i++) {
					;
					if (strcmp((textiles + i)->articulo.codigo, dni_vacio) != 0) {
						Imprimir_textil(*(textiles + i));
					}
				}
}

