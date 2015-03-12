#include<iostream>
using namespace std;
#include "listaPeliculas.h"

bool listaPeliculasLlena(tListaPeliculas listaPeliculas)
{
	bool ok;

	if(listaPeliculas.contador == listaPeliculas.capacidad)//mira haber si la lista esta llena
		ok = false;
	else
		ok = true;

	return ok; //devuelve true si la lista no esta llena, es decir, es modificable
}

void buscarPelicula(tListaPeliculas listaPeliculas, int codigo, bool &encontrado, int &posicion) //se supone la lista ordenada, busqueda binaria, devuelve true si lo ha encontrado
{
	int ini = 0, fin = listaPeliculas.contador, mitad;
	encontrado = false;
	
	while((ini <= fin)&&(!encontrado))
	{
		mitad = (ini + fin) / 2; //division entera
		if(codigo == listaPeliculas.conjuntoPeliculas[mitad].codigo)//si lo encuentra guarda su posicion
		{
			encontrado = true;
			posicion = mitad; //la posicion es correcta si lo ha encontrado
		}
		else if (codigo < listaPeliculas.conjuntoPeliculas[mitad].codigo) //si el codigo es menor que el codigo de la pelicula en la posicion mitad, el final se acorta
			fin = mitad - 1;
		else ini = mitad + 1;//sino el comienzo es la siguiente posicion a la de la mitad(porque el codigo es mayor que el de la pelicula de la mitad)
	}

}

void insertarPelicula(tListaPeliculas &listaPeliculas, tPelicula pelicula) //insertar la pelicula
{
	int posicion = 0;

	while((posicion < listaPeliculas.contador)&&( listaPeliculas.conjuntoPeliculas[posicion].codigo < pelicula.codigo )) posicion++; //busca la posicion para insertarla en la lista ordenasa

	for(int i = listaPeliculas.contador; i > posicion; i--) //abre hueco en la posicion encontrada anteriormente
		listaPeliculas.conjuntoPeliculas[i] = listaPeliculas.conjuntoPeliculas[i - 1]; 
		listaPeliculas.conjuntoPeliculas[posicion] = pelicula; //mete la pelicula en la lista
		listaPeliculas.contador++; //aumenta el contador
}

bool bajaPelicula(tListaPeliculas &listaPeliculas, int codigoPelicula) //devuelve true si se ha podido borrar
{
	bool encontrado = false, ok; //da igual a que se inicialice porque al ejecutar buscarPelicula cambia
	int posicion = 0; //da igual a que se inicialice porque al ejecutar buscarPelicula cambia

	void buscarPelicula(tListaPeliculas listaPeliculas, int codigo, bool &encontrado, int &posicion); //busca la pelicula, le devuelve su posicion y si la ha encontrado
		if(!encontrado) //si la encuentra procede a eliminarla en esa posicion
			ok = false;
		else
		{
			for(int i = posicion; i < listaPeliculas.contador;i++)
				listaPeliculas.conjuntoPeliculas[i] = listaPeliculas.conjuntoPeliculas[i - 1];

			listaPeliculas.contador--;
			ok = true;
		}
	return ok;
}