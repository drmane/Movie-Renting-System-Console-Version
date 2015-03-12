#ifndef PELICULA_H
#define PELICULA_H
using namespace std;
#include "genero.h"

typedef char tPalabra[80]; //cadena de caracteres del tipo C

typedef struct
{
	int codigo;
	tPalabra titulo;
	tGenero genero;
	int duracion;
	double precio;
	char disponible; //he considerado la disponibilidad como char por si hubiese la posibilidad de proximamente o alguna otra, asi seria facilmente de añadir
}tPelicula;

tPelicula leerPelicula(); /*lee una pelicula desde el teclado y lo guarda en una variable pelicula
					    entrada:
						salida: Una estructura tPelicula inicializada por el usario
*/

void mostrarPelicula(tPelicula pelicula); /* muestra la pelicula por pontalla
						entrada: Una estrucutra tPelicula
						salida:
*/
void editarPelicula(tPelicula &pelicula); /*edita los campos de titulo, duracion, genero y precio de una pelicula
						entrada: una estructura tPelicula 
						salida: una estructura tPelicula editada por el usario

*/
#endif