#include<iostream>
using namespace std;
#include "ListaClientes.h"



bool listaClientesLlena(tListaClientes listaClientes)
{
	bool ok;

	if(listaClientes.cont==listaClientes.capacidad)//mira haber si la lista esta llena
		ok = false;
	else
		ok = true;

	return ok; //devuelve true si la lista no esta llena, es decir, es modificable
}
void buscarCliente(tListaClientes listaClientes, tPalabra NIF, bool &encontrado, int &posicion)
	//se supone la lista ordenada, busqueda binaria, devuelve true si lo ha encontrado
{

	int ini = 0, fin = listaClientes.cont, mitad;
	
	
	while((ini <= fin)&&(!encontrado))
	{
		mitad = (ini + fin) / 2; //division entera
		if(strcmp(NIF,listaClientes.conjuntoClientes[mitad].NIF) == 0)//si el NIF a buscar es igual que el NIF indicado por la variable mitad(cadenas de caracteres de tipo C)
		{
			encontrado = true;
			posicion = mitad; //la posicion es correcta si lo ha encontrado
		}
		else if (strcmp(NIF,listaClientes.conjuntoClientes[mitad].NIF) < 0) //si el NIF a buscar es mas grande que el NIF indicado por la variable mitad (cadenas de caracteres de tipo C)
			fin = mitad - 1;
		else ini = mitad + 1;//sino el comienzo es la siguiente posicion a la de la mitad
	}
}
void insertarCliente(tCliente cliente, tListaClientes &listaClientes)
{
	int posicion = 0;

	while((posicion < listaClientes.cont)&&(strcmp(listaClientes.conjuntoClientes[posicion].NIF,cliente.NIF)< 0)) posicion++; //busca la posicion para insertarla en la lista ordenada

	for(int i = listaClientes.cont; i > posicion; i--) //abre hueco en la posicion encontrada anteriormente
		listaClientes.conjuntoClientes[i] = listaClientes.conjuntoClientes[i - 1]; 
		listaClientes.conjuntoClientes[posicion] = cliente ; //mete el cliente en la lista
		listaClientes.cont++; //aumenta el contador
		
}
void bajaCliente(tListaClientes &listaClientes, tPalabra NIF)
{
	bool encontrado = false, ok=false; //da igual a que se inicialice porque al ejecutar buscarPelicula cambia
	int posicion = 0; //da igual a que se inicialice porque al ejecutar buscarPelicula cambia

	buscarCliente(listaClientes, NIF, encontrado,posicion); //busca la pelicula, le devuelve su posicion y si la ha encontrado

		for(int i = posicion; i < listaClientes.cont;i++)
			listaClientes.conjuntoClientes[i] = listaClientes.conjuntoClientes[i + 1]; //la eliminacion se hace asi

		listaClientes.cont--;
		
}
