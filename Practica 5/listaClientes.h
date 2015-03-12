#ifndef LISTA_CLIENTES_H
#define LISTA_CLIENTES_H
using namespace std;
#include "cliente.h"

typedef tCliente *tClientePtr; //puntero que apunta a clientes

typedef struct
{
	tClientePtr conjuntoClientes;
	int cont;
	int capacidad;
}tListaClientes;

bool listaClientesLlena(tListaClientes listaClientes); /*devuelve true si la lista no esta llena, es decir, es modificable
												entrada: Una estructura tListaClientes que contiene todos los clientes
												salida: Un bool que indica si esta llena o no la lista
*/

void buscarCliente(tListaClientes listaClientes, tPalabra NIF, bool &encontrado, int &posicion); /*se supone la lista ordenada, busqueda binaria, devuelve true y posicion si lo ha encontrado
												entrada: Una estructura tListaClientes que contiene todos los cliente y el NIF de un cliente en especifico
												salida: Un bool que indica si el cliente esta en la lista, y un inter que nos indica la posicion del cliente buscado dentro de la lista
*/

void insertarCliente(tCliente cliente, tListaClientes &listaClientes);/*insertar el cliente(no evalua si esta llena la lista)
												entrada: Una estructura tCliente y una estructura tListaClientes
												salida: Una estructura tListaClientes actualizada, con el nuevo cliente
*/

void bajaCliente(tListaClientes &listaClientes, tPalabra NIF);/*elimina un cliente por completo de la lista
															entrada: Una estructura tListaClientes que contiene la lista de cliente y el NIF del cliente que se quiere eliminar
															salida: Una estructura tListaClientes actualizada, sin el cliente especificado
*/

#endif