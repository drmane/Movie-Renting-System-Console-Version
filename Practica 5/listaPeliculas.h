#ifndef LISTAPELICULAS_H
#define LISTAPELICULAS_H
using namespace std;
#include "pelicula.h"

typedef tPelicula *tPeliculaPtr;

typedef struct
{
	tPeliculaPtr conjuntoPeliculas; //puntero que apunta a un conjunto de peliculas
	int contador;
	int capacidad;
}tListaPeliculas;

bool listaPeliculasLlena(tListaPeliculas listaPeliculas); /*devuelve true si la lista no esta llena, es decir, es modificable
											entrada: Una estructura tListaPeliculas que contiene todas las peliculas
											salida: Un bool que indica si esta llena o no la lista
*/
void buscarPelicula(tListaPeliculas listaPeliculas, int codigo, bool &encontrado, int &posicion); /*se supone la lista ordenada, busqueda binaria, devuelve true y posicion si lo ha encontrado
											entrada: Una estructura tListaPeliculas que contiene todas las peliculas y el codigo de una pelicula en especifica
											salida: Un bool que indica si la pelicula esta en la lista, y un inter que nos indica la posicion de la pelicula buscada dentro de la lista
*/
void insertarPelicula(tListaPeliculas &listaPeliculas, tPelicula pelicula);/*insertar la pelicula en la lista de peliculas(no evalua si esta llena)
											entrada: Una estructura tListaPeliculas y una estructura tPelicula
											salida: Una estructura tListaPelicula actualizada, con la nueva pelicula
*/

bool bajaPelicula(tListaPeliculas &listaPeliculas, int codigoPelicula); /*elimina una pelicula por completo de la lista,devuelve true si se ha podido borrar
											entrada: Una estructura tListaPeliculas y el codigo de una pelicula en especifica
											salida: Una estructura tListaPeliculas actualizada, sin la pelicula especifcada
*/

#endif