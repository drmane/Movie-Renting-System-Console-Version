#include<iostream>
#include<iomanip>
#include<ctype.h>
using namespace std;
#include "cliente.h"




tCliente leerCliente()
{
	tCliente cliente;
	

	cout << "Introduzca el nombre del cliente: ";
	cin >> setw(80) >> cliente.nombre;
	cin.sync();

	cout << "Introduzca el apellido del cliente: ";
	cin.getline(cliente.apellidos,80);

	cliente.apellidos[0]=toupper(cliente.apellidos[0]); //transforma la primera letra del apellido en mayusculas para luego ordenar la lista

	cliente.genero = leerGenero();

	cliente.peliculasVisionadas.cont=0;

	return cliente;
}
void mostrarCliente(tCliente cliente, bool mostrarDetalles,tListaPeliculas listaPeliculas)
{
	bool encontrado;
	int posicion=0;

	cout << " " << setw(12) << left << cliente.NIF;
	cout << setw(12) << left << cliente.nombre; 
	cout << setw(20) << left << cliente.apellidos;
	cout << setw(18) << left;
	escribirGenero(cliente.genero);
	
	cout << setw(3) << left << cliente.peliculasVisionadas.cont;

	if (mostrarDetalles)
	{
		cout << endl << endl;
		if(cliente.peliculasVisionadas.cont == 0)
			cout <<"No hay peliculas visionadas" << endl;
		else
		{

			cout << "Titulo                      Genero            Gustar" << endl;
			cout << "****************************************************" << endl;

			for(int i=0; i < cliente.peliculasVisionadas.cont; i++)
			{
				buscarPelicula(listaPeliculas,cliente.peliculasVisionadas.PeliculasVistas[i].codigo,encontrado,posicion);
				if(encontrado)
				{
					cout << setw(28) << left << listaPeliculas.conjuntoPeliculas[posicion].titulo << setw(18) << left;
					escribirGenero(listaPeliculas.conjuntoPeliculas[posicion].genero);
					cout << setw(5) << left;
					if (cliente.peliculasVisionadas.PeliculasVistas[i].gustar)
						cout <<"Si"<< endl;
					else
						cout <<"No"<< endl;
				}
			}		
		}
	}
	cout << endl;
}
void editarCliente(tCliente &cliente)
{

		cout << "Nuevo nombre: ";
		cin >> setw(80) >> cliente.nombre;
		cin.sync();

		cout << "Nuevos Apellidos: ";
		cin.getline(cliente.apellidos,80);
		cliente.apellidos[0]=toupper(cliente.apellidos[0]); //transforma la primera letra del apellido en mayusculas para luego ordenar la lista
		

		cliente.genero = leerGenero();
	
}
void altaVisionado(tCliente &cliente, tPeliculaSimple PeliculaVisionada)
{
	int i=cliente.peliculasVisionadas.cont;

	cliente.peliculasVisionadas.PeliculasVistas[i]=PeliculaVisionada;

	cliente.peliculasVisionadas.cont++;
}
void datosVisionado(tCliente cliente,int codigo, int &vecesVistas, int &vecesGustada)
{
	int ini = 0, fin = cliente.peliculasVisionadas.cont, mitad;
	bool encontrado = false;
	
	while((ini <= fin)&&(!encontrado))
	{
		mitad = (ini + fin) / 2; //division entera
		if(codigo == cliente.peliculasVisionadas.PeliculasVistas[mitad].codigo)//si lo encuentra guarda su posicion
		{
			vecesVistas++; //si la encuentra, aumenta las veces vista
			encontrado = true;
			if(cliente.peliculasVisionadas.PeliculasVistas[mitad].gustar)
				vecesGustada++;//si ademas gustar esta a true, aumenta el numero de clientes que le gusta la pelicula
		}
		else if (codigo < cliente.peliculasVisionadas.PeliculasVistas[mitad].codigo) //si el codigo es menor que el codigo de la pelicula en la posicion mitad, el final se acorta
			fin = mitad - 1;
		else ini = mitad + 1;//sino el comienzo es la siguiente posicion a la de la mitad(porque el codigo es mayor que el de la pelicula de la mitad)
	}

}
