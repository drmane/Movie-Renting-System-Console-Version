#ifndef GENERO_H
#define GENERO_H
using namespace std;

typedef enum { ciencia_ficcion, fantasia, comedia, terror, drama, comedia_romantica} tGenero;

tGenero leerGenero();/*Devuelve un genero introducido por el usario
					 entrada:
					 salida: estructura tGenero
*/
void escribirGenero(tGenero genero);/*escribe el nombre del género en la consola
									entrada: estructura tGenero
									salida:
*/
#endif