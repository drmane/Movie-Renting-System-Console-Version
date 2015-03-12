#ifndef CLIENTE_H
#define CLIENTE_H
using namespace std;
#include "listaPeliculas.h"
const int MAX_VISIONADAS=40;

typedef struct
{
	int codigo;
	bool gustar;
}tPeliculaSimple;

typedef tPeliculaSimple tPeliculasVistas[MAX_VISIONADAS];

typedef struct
{
	tPeliculasVistas PeliculasVistas; 
	int cont;

}tlistaPeliculasVisionadas;

typedef struct 
{
	tPalabra NIF;
	tPalabra nombre;
	tPalabra apellidos;
	tGenero genero;
	tlistaPeliculasVisionadas peliculasVisionadas;

}tCliente;

tCliente leerCliente(); /*lee un cliente desde el teclado y lo guarda en una variable cliente
						entrada:
						salida: Una estructura tCliente inicializada por el usario
*/
void mostrarCliente(tCliente cliente, bool mostrarDetalles,tListaPeliculas listaPeliculas);/*muestra los datos de un cliente por pantalla
						entrada: el cliente que se va a mostrar, un bool para especificar si se desea mostrar informacion detalla de 
						las peliculas vistas, la lista de peliculas completa
						salida:
*/
void editarCliente(tCliente &cliente);/*edita los campos de nombre, apellido y genero favorito de un cliente
						entrada: una estructura tCliente 
						salida: una estructura tCliente editada por el usario
*/
void altaVisionado(tCliente &cliente, tPeliculaSimple PeliculaVisionada);/*da de alta una pelicula vista por un cliente
						entrada: Una estrucutra tCliente y una estructura tPeliculaSimple que contiene el codigo de la pelicula vista
						y si le ha gustado al usario
						salida:La estrucutra tCliente actualizada con la nueva pelicula vista
*/
void datosVisionado(tCliente cliente,int codigo, int &vecesVistas, int &vecesGustada);/*Devuelve los datos detallados de una pelicula vista por un usario en especifico
						entrada:una estructura tCliente y el codigo de una pelicula
						salida: las veces que el cliente ha visto una pelicula, y las cantidad de veces que le ha gustado
*/

#endif


