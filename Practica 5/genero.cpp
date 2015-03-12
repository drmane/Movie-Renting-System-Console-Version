#include<iostream>
#include<string>
using namespace std;
#include "genero.h"

tGenero leerGenero()
{
	tGenero generoLeido;//genereo leido default
	string generoUsuario;
	bool ok;

	cout << "Introduzca el genero de la Pelicula(primera letra de cada palabra en mayuscula): ";
	do
	{
		getline(cin,generoUsuario);
		ok=true;

		if (generoUsuario == "Ciencia Ficcion")
			generoLeido = ciencia_ficcion;
		else if (generoUsuario == "Fantasia")
			generoLeido = fantasia;
		else if (generoUsuario == "Comedia")
			generoLeido = comedia;
		else if (generoUsuario == "Terror")
			generoLeido = terror;
		else if (generoUsuario == "Drama")
			generoLeido = drama;
		else if (generoUsuario == "Comedia Romantica")
			generoLeido = comedia_romantica;
		else
		{
			cout<<"Genero no valido"<<endl;
			ok=false;
		}
	}while(!ok);
	return generoLeido;
}
void escribirGenero(tGenero genero)
{
	switch(genero)
	{
	case 0: cout << "Ciencia Ficcion"; break;
	case 1: cout << "Fantasia"; break;
	case 2: cout << "Comedia"; break;
	case 3: cout << "Terror"; break;
	case 4: cout << "Drama"; break;
	case 5: cout << "Comedia Romantica"; break;
	
	}
}