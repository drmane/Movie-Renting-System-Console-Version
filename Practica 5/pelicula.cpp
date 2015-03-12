#include<iostream>
#include<iomanip>
using namespace std;
#include "pelicula.h"

tPelicula leerPelicula() //lee una pelicula desde el teclado y lo guarda en una variable pelicula
{
	tPelicula pelicula;

	cin.sync();
	cout << "Introduzca el titulo de la Pelicula: ";
	cin.getline(pelicula.titulo,80);
	
	pelicula.genero = leerGenero(); //lee el genero y lo guarda en la pelicula

	cout << "Introduzca la duracion de la Pelicula(en minutos): ";
	cin >> pelicula.duracion;
	
	cout << "Introduzca el precio de la Pelicula: ";
	cin >> pelicula.precio;
	
	pelicula.disponible = 'S'; //Al crearse una nueva pelicula, automaticamente esta disponible

	return pelicula;
}
void mostrarPelicula(tPelicula pelicula) //muestra la pelicula
{

	cout << " "<< setw(7) << left << pelicula.codigo;
	cout << setw(28) << left << pelicula.titulo;

	cout << setw(18) << left;
	escribirGenero(pelicula.genero);

	cout << setw(9) << left << fixed << setprecision(2) << pelicula.duracion;
	cout << setw(8) << left << fixed << setprecision(2) << pelicula.precio;
	cout << setw(5) << left << pelicula.disponible << endl;
}
void editarPelicula(tPelicula &pelicula) //editar una pelicula
{
		cin.sync();

		cout << "Introduzca el nuevo titulo(titulo actual " << pelicula.titulo << "): ";
		cin.getline(pelicula.titulo,80);
		
		pelicula.genero = leerGenero();

		cout << "Introduzca la nueva duracion(duracion actual " << pelicula.duracion << " minutos): ";
		cin >> pelicula.duracion;
		
		cout << "Introduzca el nuevo precio(precio actual " << pelicula.precio << "): ";
		cin >> pelicula.precio;
		
}
