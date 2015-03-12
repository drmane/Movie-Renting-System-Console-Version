//Ricardo de la Rosa Vivas
//Daniel Ruiz Manero

#include<iostream>
#include<string>
#include<fstream>
#include <iomanip>
using namespace std;
#include "listaClientes.h"

const int SIZE_PELICULA = sizeof(tPelicula); //poner bool en carga de clientes y peliculas?
const int SIZE_CLIENTE = sizeof(tCliente);

char menuPrincipal(); //menu principal
void gestionPeliculas(tListaPeliculas &listaPeliculas); //gestion de las peliculas
char menuPeliculas();//menu de la gestion de las peliculas
void gestionClientes(tListaClientes &listaClientes,tListaPeliculas listaPeliculas);//gestion de los clientes (faltan parametros!!! y en el main poner)
char menuClientes();//menu de la gestion de clientes
void gestionGeneral(tListaPeliculas listaPeliculas, tListaClientes &listaClientes);// gestion general (faltan parametros!!! y en el main poner)
char menuGestionGeneral(); //menu de la gestion general
void cargaPeliculas(tListaPeliculas &listaPeliculas);//carga inicial de las peliculas desde archivo binario
void cargaClientes(tListaClientes &listaClientes);//carga inicial de los clientes desde archivo binario
void guardarPeliculas(tListaPeliculas listaPeliculas);//guardado final de las peliculas al archivo de texto(guarda al salir del menu principal y del menu de pelicula)
void guardarCliente(tListaClientes listaClientes);//guardado final de los clientes al archivo de texto(guarda al salir del menu principal y del menu de pelicula)
void nuevaPelicula(tListaPeliculas &listaPeliculas);//inserta una nueva pelicula en la lista
void datosPelicula(tListaPeliculas listaPeliculas); //pide el codigo de la pelicula y la muestra por pantalla si existe
void mostrarPeliculas(tListaPeliculas listaPeliculas); //muestra todas las peliculas puede mostrar las disponibles o todas
void editarPelicula(tListaPeliculas &listaPeliculas); //busca una pelicula y si la encuentra la edita
void bajaPelicula(tListaPeliculas &listaPeliculas);//da de baja una pelicula indicada por un codigo
void obtenerNIF(tPalabra &NIF);//pide al usuario y comprueba si el NIF es correcto
bool obtenerRespuesta();//interactua con el usario para obtener una respuesta, si la respuesta en si, devuelve true;
void nuevoCliente(tListaClientes &listaClientes);//da de alta un nuevo cliente
void datosCliente(tListaClientes listaClientes, tListaPeliculas listaPeliculas);//pide el NIF de un cliente y lo muestra por pantalla si existe
void mostrarClientes(tListaClientes listaClientes, tListaPeliculas listaPeliculas);//muestra todos los clientes dados de alta
void modificarCliente(tListaClientes &listaClientes);//busca un cliente y si lo encuentra lo edita
void eliminarCliente(tListaClientes &listaClientes,tListaPeliculas listaPeliculas);//elimina por completo un cliente de la lista
void nuevoVisionado(tListaPeliculas listaPeliculas, tListaClientes &listaClientes); //pide un DNI, codigo de pelicula y si le gusto o no y lo guarda en peliculas visionadas
void exportarListaClientes(tListaClientes listaClientes); //exportar los datos de un usuario a un archivo de texto
void estadisticasPeliculas(tListaClientes listaClientes, tListaPeliculas listaPeliculas);//mostrar por pantalla una peliculas, el numero de veces visionada y el numero de veces que gusto
void ordenarListaApellido(tListaClientes &listaClientesOrdenada); //ordenacion por seleccion directa
void importarDatos(tListaPeliculas &listaPeliculas, tListaClientes &listaClientes); //gestiona la importacion de la lista de peliculas y clientes desde archivo de texto
bool importarDatosPeliculas(tListaPeliculas &listaPeliculas); //importacion de peliculas desde archivo de texto
bool importarDatosClientes(tListaClientes &listaClientes); //importacion de clientes desde archivo de texto
void importarPeliculasVisionadas(tCliente &cliente, ifstream &input); //importa las peliculas visionadas por cliente desde archivo de texto
void nuevaListaPeliculas(tListaPeliculas &listaPeliculas); //crea un nuevo array de diez peliculas(necesario en la transferencia de texto a binario) y borra el anterior
void nuevaListaClientes(tListaClientes &listaClientes); //crea un nuevo array de diez clientes (necesario en la transferencia de texto a binario) y borra el anterior
void aumentarCapacidadPeliculas(tListaPeliculas &listaPeliculas); //aumenta la capacidad de las peliculas si es necesario
void aumentarCapacidadClientes(tListaClientes &listaClientes); //aumenta la capacidad de los clientes si es necesario

int main()
{
	tListaPeliculas listaPeliculas;
	tListaClientes listaClientes;

	listaPeliculas.conjuntoPeliculas = new tPelicula[10]; //creacion de una array dinamico de diez peliculas
	listaPeliculas.contador = 0;
	listaPeliculas.capacidad = 10;

	listaClientes.conjuntoClientes = new tCliente[10]; //creacion de una array dinamico de diez clientes
	listaClientes.cont = 0;
	listaClientes.capacidad = 10;

	bool salir = false;

	cargaPeliculas(listaPeliculas);
	cargaClientes(listaClientes);
	
	do
	{
		switch(menuPrincipal())
		{
		case '0': salir = true; break;
		case '1': gestionPeliculas(listaPeliculas); break;
		case '2': gestionClientes(listaClientes,listaPeliculas); break;
		case '3': gestionGeneral(listaPeliculas, listaClientes);break;
		case '4': importarDatos(listaPeliculas, listaClientes); break;
		}

	}while(!salir);

	guardarPeliculas(listaPeliculas);
	guardarCliente(listaClientes);

	delete [] listaPeliculas.conjuntoPeliculas;
	delete [] listaClientes.conjuntoClientes;

	return 0;
}
char menuPrincipal() //menu principal
{
	char opcion;

	cout << endl << "RedPelis" << endl;
	cout << "--------" << endl << endl;

	cout << "1.- Gestionar Peliculas" << endl;
	cout << "2.- Gestionar Clientes" << endl;
	cout << "3.- Gestion General" << endl;
	cout << "4.- Importar datos de archivos de texto" << endl;
	cout << "0.- Salir" << endl;

	do
	{
		cout << endl << "Introduzca la Opcion: ";
		cin >> opcion;
		cin.sync();
	}while((opcion < '0')||(opcion > '4'));

	return opcion;
}
void gestionPeliculas(tListaPeliculas &listaPeliculas) //gestion de las peliculas
{
	bool salir = false; //permite volver al menu anterior
	do
	{
		switch(menuPeliculas())
		{
		case '0': salir = true; break;
		case '1': nuevaPelicula(listaPeliculas); break;
		case '2': datosPelicula(listaPeliculas); break;
		case '3': mostrarPeliculas(listaPeliculas); break;
		case '4': editarPelicula(listaPeliculas); break;
		case '5': bajaPelicula(listaPeliculas); break;
		}

	}while(!salir);

	guardarPeliculas(listaPeliculas);
}
char menuPeliculas()//menu de la gestion de las peliculas
{
	char opcion;

	cout << endl << "RedPelis" << endl;
	cout << "--------" << endl << endl;

	cout << "1.- Alta de Peliculas" << endl;
	cout << "2.- Datos de Pelicula" << endl;
	cout << "3.- Datos de Todas las Peliculas" << endl;
	cout << "4.- Edicion de la Pelicula" << endl;
	cout << "5.- Baja de Pelicula" << endl;
	cout << "0.- Volver al Menu Anterior" << endl;

	do
	{
		cout << endl << "Introduzca la Opcion: ";
		cin >> opcion;
		cin.sync();
	}while((opcion < '0')||(opcion > '5'));

	return opcion;
}
void gestionClientes(tListaClientes &listaClientes,tListaPeliculas listaPeliculas) //menu de la gestion de clientes
{
	bool salir = false; //permite volver al menu anterior

	do
	{
		switch(menuClientes())
		{
		case '0': salir = true; break;
		case '1': nuevoCliente(listaClientes);break;
		case '2': datosCliente(listaClientes,listaPeliculas);break;
		case '3': mostrarClientes(listaClientes,listaPeliculas);break;
		case '4': modificarCliente(listaClientes);break;
		case '5': eliminarCliente(listaClientes,listaPeliculas);break;
		}

	}while(!salir);

	guardarCliente(listaClientes);
}
char menuClientes() //menu de la gestion de clientes
{
	char opcion;

	cout << endl << "RedPelis" << endl;
	cout << "--------" << endl << endl;

	cout << "1.- Nuevo Cliente" << endl;
	cout << "2.- Datos de Cliente" << endl;
	cout << "3.- Datos de Todos los Clientes" << endl;
	cout << "4.- Editar Cliente" << endl;
	cout << "5.- Baja del Cliente" << endl;
	cout << "0.- Volver al Menu Anterior" << endl;

	
	do
	{
		cout << endl << "Introduzca la Opcion: ";
		cin >> opcion;
		cin.sync();
	}while((opcion < '0')||(opcion > '5'));

	return opcion;
}
void gestionGeneral(tListaPeliculas listaPeliculas, tListaClientes &listaClientes)// gestion general (faltan parametros!!! y en el main poner)
{
	bool salir = false; //permite volver al menu anterior

	do
	{
		switch(menuGestionGeneral())
		{
		case '0': salir = true; break;
		case '1': nuevoVisionado(listaPeliculas, listaClientes); break;
		case '2': exportarListaClientes(listaClientes); break;
		case '3': estadisticasPeliculas(listaClientes, listaPeliculas); break;
		}

	}while(!salir);

	guardarCliente(listaClientes);
}
char menuGestionGeneral() //menu de la gestion general
{
	char opcion;

	cout << endl << "RedPelis" << endl;
	cout << "--------" << endl << endl;

	cout << "1.- Nuevo Visionado" << endl;
	cout << "2.- Exportar Lista de Clientes" << endl;
	cout << "3.- Estadisticas de la Pelicula" << endl;
	cout << "0.- Volver al Menu Anterior" << endl;


	do
	{
		cout << endl << "Introduzca la Opcion: ";
		cin >> opcion;
		cin.sync();
	}while((opcion < '0')||(opcion > '3'));

	return opcion;
}
void cargaPeliculas(tListaPeliculas &listaPeliculas)//carga inicial de las peliculas desde archivo de texto
{
	tPelicula pelicula;
	fstream input;
	int cuantos;

	input.open("pelis.dat", ios::in | ios::binary);
	input.read( (char *) &pelicula, SIZE_PELICULA );

	cuantos = input.gcount();
	while( cuantos == SIZE_PELICULA)
	{
		listaPeliculas.conjuntoPeliculas[listaPeliculas.contador] = pelicula;
		input.read( (char *) &pelicula, SIZE_PELICULA );
		cuantos = input.gcount();
		listaPeliculas.contador++;
	}
	input.close();
}
void cargaClientes(tListaClientes &listaClientes)
{
	tCliente cliente;
	fstream input;
	int cuantos;

	input.open("clientes.dat", ios::in | ios::binary);
	input.read( (char *) &cliente, SIZE_CLIENTE );

	cuantos = input.gcount();
	while( cuantos == SIZE_CLIENTE)
	{
		listaClientes.conjuntoClientes[listaClientes.cont] = cliente;
		input.read( (char *) &cliente, SIZE_CLIENTE );
		cuantos = input.gcount();
		listaClientes.cont++;
	}

	input.close();	
}
void guardarPeliculas(tListaPeliculas listaPeliculas)//guardado final de las peliculas desde archivo de texto
{
	fstream output;

	output.open("pelis.dat", ios::out | ios::binary | ios::trunc);

	for(int i = 0; i < listaPeliculas.contador; i++) 
		output.write( (char *) &listaPeliculas.conjuntoPeliculas[i], SIZE_PELICULA); //escribe cada pelicula en el archivo binario
	
	output.close();
}
void guardarCliente(tListaClientes listaClientes)
{
	fstream output;

	output.open("clientes.dat", ios::out | ios::binary | ios::trunc);

	for(int i = 0; i < listaClientes.cont; i++) 
		output.write( (char *) &listaClientes.conjuntoClientes[i], SIZE_CLIENTE); //escribe cada pelicula en el archivo binario
	
	output.close();
}
void nuevaPelicula(tListaPeliculas &listaPeliculas)//inserta una nueva pelicula en la lista
{
	int codigo = 0, posicion = 0, codigoBuscar;
	bool encontrado = false;
	tPelicula peliculaAux;

	if(!listaPeliculasLlena(listaPeliculas)) //evalua si la lista esta llena(devuelve true si no esta llena)
		aumentarCapacidadPeliculas(listaPeliculas);

	cout << "Introduzca el codigo de la Pelicula: ";
	cin >> codigoBuscar;

	buscarPelicula(listaPeliculas,codigoBuscar,encontrado,posicion);

	if(encontrado)
		cout << "ERROR!! es codigo esta en uso" << endl;
	else
	{
		peliculaAux = leerPelicula();
		peliculaAux.codigo = codigoBuscar;
		insertarPelicula(listaPeliculas, peliculaAux);
	
	}
	
}
void datosPelicula(tListaPeliculas listaPeliculas) //pide el codigo de la pelicula y la muestra por pantalla si existe
{
	int codigo = 0, posicion = 0;
	bool encontrado = false;

	cout << "Introduce el codigo a buscar: ";

	cin >> codigo;
	cout << endl;

	buscarPelicula(listaPeliculas,codigo,encontrado,posicion);

	if (encontrado)
	{
		cout << "Codigo  Titulo                     Genero            Duracion Precio  Disponible";
		cout << "-------------------------------------------------------------------------------" << endl;
		mostrarPelicula(listaPeliculas.conjuntoPeliculas[posicion]);
	}
	else
		cout << "ERROR!! Pelicula NO encontrada";
}
void mostrarPeliculas(tListaPeliculas listaPeliculas) //muestra todas las peliculas puede mostrar las disponibles o todas
{	
	if(listaPeliculas.contador != 0) //evalua si la lista esta vacia
	{

		cout << "Desea mostrar solo las Disponibles?(respuesta: S/N): ";
		if(obtenerRespuesta())
		{
			cout << " Codigo  Titulo                     Genero            Duracion Precio  Disponible";
			cout << "-------------------------------------------------------------------------------" << endl;
			for(int i = 0; i < listaPeliculas.contador;i++)
						if(listaPeliculas.conjuntoPeliculas[i].disponible == 'S')
							mostrarPelicula(listaPeliculas.conjuntoPeliculas[i]);
		}
		else
		{
			cout << "Codigo  Titulo                     Genero            Duracion Precio  Disponible";
			cout << "-------------------------------------------------------------------------------" << endl;
			for(int i = 0; i < listaPeliculas.contador; i++)
						mostrarPelicula(listaPeliculas.conjuntoPeliculas[i]);
		}

	}
	else
		cout << "ERROR!! lista vacia" << endl;
}
void editarPelicula(tListaPeliculas &listaPeliculas)//busca una pelicula y si la encuentra la edita
{
	
	int codigo = 0, posicion = 0;
	bool encontrado = false;

	cout << "Introduce el codigo a buscar: ";

	cin >> codigo;
	cout << endl;

	buscarPelicula(listaPeliculas,codigo,encontrado,posicion);

	if(codigo == listaPeliculas.conjuntoPeliculas[posicion].codigo)
	{
		editarPelicula(listaPeliculas.conjuntoPeliculas[posicion]);
	}
	else
		cout << "ERROR!! Pelicula NO encontrada";
}
void bajaPelicula(tListaPeliculas &listaPeliculas)//da de baja una pelicula indicada por un codigo
{
	int codigo = 0, posicion = 0;
	bool encontrado = false;

	cout << "Introduce el codigo a buscar: ";

	cin >> codigo;
	cout << endl;

	buscarPelicula(listaPeliculas,codigo,encontrado,posicion);

	if(codigo == listaPeliculas.conjuntoPeliculas[posicion].codigo)
	{
		listaPeliculas.conjuntoPeliculas[posicion].disponible = 'N';
		cout << "Se ha dado de baja satisfactoriamente la pelicula" << endl;
	}
	else
		cout << "ERROR!! Pelicula NO encontrada";
}
void obtenerNIF(tPalabra &NIF)
{
	int longitud, i;
	bool ok;
	
	cout << "Introduzca el NIF del cliente: ";

	do
	{ // la comprobacion del nif se tiene que hacer aqui, (no dentro de "leercliente")para que la funcion "leerCliente" no reciba ningun parametro como lo especifica la practica
		ok=true;
		i=0;

		cin.sync(); //sino se salta el getline
		cin.getline(NIF,80);

		longitud = strlen(NIF);
			
		if(longitud==9)//se comprueba la longitud
		{ 

			if(isalpha(NIF[8])) //se comprueba que el ultimo digito es una letra
			{
				if (islower(NIF[8]))
					NIF[8] = toupper(NIF[8]);
			}
			else ok=false;

			while (ok && i < 8) //se comprueba que los 8 primeros caracteres son digitos
			{
				if(!isdigit(NIF[i]))
					ok=false;
				i++;
			} 
		}
			else ok=false;
			if(!ok)
				cout << "introduzca un NIF valido"<<endl;
	}while (!ok);
}
bool obtenerRespuesta()
{
	bool ok=false, respuesta;
	char respuestaDelUsario;
	
	do{
		respuestaDelUsario = cin.get();
		cin.sync();
		if((respuestaDelUsario == 'S')||(respuestaDelUsario == 's'))
			{	
			respuesta=true;
			ok=true;
			}
		else if ((respuestaDelUsario == 'N')||(respuestaDelUsario == 'n')||(respuestaDelUsario == '\n'))
			{
			respuesta=false;
			ok=true;
			}
		else 
			{
				cout <<"Introduzca una opcion valida"<<endl;
				ok=false;
			}
		}while(!ok);
	return respuesta;
}
void nuevoCliente(tListaClientes &listaClientes)
{
	tPalabra NIFbuscar;
	tCliente clienteAux;
	int posicion = 0;
	bool encontrado = false;
	bool ok=false;

	if(!listaClientesLlena(listaClientes)) //evalua si la lista esta llena(devuelve true si no esta llena)
		aumentarCapacidadClientes(listaClientes);

	obtenerNIF(NIFbuscar);
	buscarCliente(listaClientes,NIFbuscar,encontrado,posicion);
	if(encontrado)
		cout << "ERROR!! el NIF ya esta en uso" << endl;
	else
		{
		clienteAux = leerCliente();

		strcpy_s(clienteAux.NIF,NIFbuscar);  // la asignacion en cadenas de C se debe hacer asi

		insertarCliente(clienteAux,listaClientes);
		}
	
}
void datosCliente(tListaClientes listaClientes,tListaPeliculas listaPeliculas)
{

	int posicion = 0;
	bool encontrado = false,ok=false;
	bool mostrarDetalles=true;
	tPalabra NIF;
	
	obtenerNIF(NIF);

	buscarCliente(listaClientes,NIF,encontrado,posicion);

	if (encontrado)
	{
		cout << " NIF         Nombre      Apellidos           Genero            Peliculas Vistas" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		mostrarCliente(listaClientes.conjuntoClientes[posicion],mostrarDetalles,listaPeliculas);
	}
	else
		cout << "ERROR!! Cliente NO encontrado";

}
void mostrarClientes(tListaClientes listaClientes, tListaPeliculas listaPeliculas)
{
	bool mostrarDetalles=false;

	if(listaClientes.cont != 0) //evalua si la lista esta vacia
	{
		cout << " NIF         Nombre      Apellidos           Genero            Peliculas Vistas" << endl;
		cout << "------------------------------------------------------------------------------" << endl;

		for(int i = 0; i < listaClientes.cont;i++)
			mostrarCliente(listaClientes.conjuntoClientes[i],mostrarDetalles,listaPeliculas);
	}
	else
		cout << "ERROR!! lista vacia" << endl;

}
void modificarCliente(tListaClientes &listaClientes)
{
	tPalabra NIF;
	int posicion = 0;
	bool encontrado = false,ok=false;

	obtenerNIF(NIF);
	buscarCliente(listaClientes,NIF,encontrado,posicion);
	
	if(strcmp(NIF,listaClientes.conjuntoClientes[posicion].NIF) == 0)
	{
		editarCliente(listaClientes.conjuntoClientes[posicion]);
	}
	else
		cout << "ERROR!! Cliente NO encontrado";
}
void eliminarCliente(tListaClientes &listaClientes,tListaPeliculas listaPeliculas)
{
	tPalabra NIF;
	bool encontrado=false,mostrardetalles=false;
	int posicion=0;
	
	obtenerNIF(NIF);
	buscarCliente(listaClientes,NIF,encontrado,posicion);
	if(encontrado)
		{
			cout<<"Estas seguro que desea eliminar este cliente:(S/N)"<<endl;
			cout << " NIF         Nombre      Apellidos           Genero            Peliculas Vistas" << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			mostrarCliente(listaClientes.conjuntoClientes[posicion],mostrardetalles,listaPeliculas);

			if(obtenerRespuesta())
			{
				bajaCliente(listaClientes,NIF);
				cout << "Se ha eliminado el cliente"<<endl;
			}
			else
				cout << "No se ha eliminado el cliente"<< endl;
		}
			
	else
		cout<<"No existe este cliente"<<endl;

}
void nuevoVisionado(tListaPeliculas listaPeliculas, tListaClientes &listaClientes) //pide un DNI, codigo de pelicula y si le gusto o no y lo guarda en peliculas visionadas
{
	int codigo, posicionPelicula = 0, posicionCliente = 0;
	bool encontradoPelicula = false, encontradoCliente = false, ok = false;
	tPalabra NIF;
	tPeliculaSimple peliculavisionada;
	
	cout << "Introduzca el codigo de la pelicula: ";

	cin >> codigo;

	buscarPelicula(listaPeliculas, codigo, encontradoPelicula, posicionPelicula);
	
	if(!encontradoPelicula)
		cout << "ERROR!! Pelicula no encontrada" << endl;
	else if((listaPeliculas.conjuntoPeliculas[posicionPelicula].disponible=='N')||(listaPeliculas.conjuntoPeliculas[posicionPelicula].disponible=='n'))
		cout << "Pelicula no disponible"<<endl;
		
	else
	{
		peliculavisionada.codigo=codigo;

		obtenerNIF(NIF);

		buscarCliente(listaClientes, NIF,encontradoCliente,posicionCliente);

		if(!encontradoCliente)
			cout << "ERROR!! Cliente no encontrado" << endl;
		else{
			cout << "Le gusto la pelicula?(S/N): "; 

			if(obtenerRespuesta())
				peliculavisionada.gustar = true;
			else
				peliculavisionada.gustar= false;

			altaVisionado(listaClientes.conjuntoClientes[posicionCliente],peliculavisionada);
		}
	}
}
void exportarListaClientes(tListaClientes listaClientes) //exportar los datos de un usuario a un archivo de texto
{
	string nombreArchivo;
	ofstream output;
	tListaClientes listaClientesOrdenada;
	listaClientesOrdenada = listaClientes;

	cout << "Introduce el nombre del archivo donde exportar los datos(ej: infoCliente.txt): ";
	getline(cin, nombreArchivo);

	output.open(nombreArchivo);

	ordenarListaApellido(listaClientesOrdenada); //ordenacion por seleccion directa

	for(int i=0;i<listaClientes.cont;i++)
	{
		output << listaClientesOrdenada.conjuntoClientes[i].apellidos << endl<<flush;
		output << listaClientesOrdenada.conjuntoClientes[i].nombre << endl<<flush;
		output << listaClientesOrdenada.conjuntoClientes[i].peliculasVisionadas.cont << endl << endl<<flush;
	}

	output.close();

	delete [] listaClientesOrdenada.conjuntoClientes;
}
void estadisticasPeliculas(tListaClientes listaClientes, tListaPeliculas listaPeliculas)
{
	int vecesVisionadaTemporal = 0, vecesGustarTemporal = 0, vecesVisionadaTotal = 0, vecesGustarTotal = 0;

	cout << " Titulo                      Veces Visionada   Numero Clientes que le gusta" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	for(int pos = 0; pos < listaPeliculas.contador; pos++)//recorre las peliculas
	{
		cout << " " << setw(28) << left << listaPeliculas.conjuntoPeliculas[pos].titulo;

		for(int contadorClientes = 0; contadorClientes < listaClientes.cont; contadorClientes++) //recorre todos los clientes
		{
			datosVisionado(listaClientes.conjuntoClientes[contadorClientes], listaPeliculas.conjuntoPeliculas[pos].codigo ,vecesVisionadaTemporal, vecesGustarTemporal);
			vecesVisionadaTotal = vecesVisionadaTemporal;
			vecesGustarTotal = vecesGustarTemporal;
		}

		cout << setw(18) << left << vecesVisionadaTotal;
		cout << setw(18) << left << vecesGustarTotal << endl;

		vecesVisionadaTemporal = 0; //ajusta las variables temporales
		vecesGustarTemporal = 0; //ajusta las variables temporales
		vecesVisionadaTotal = 0;//ajusta las variables totales
		vecesGustarTotal = 0; //ajusta las variables totales
	}
}
void ordenarListaApellido(tListaClientes &listaClientesOrdenada) //ordenacion por seleccion directa
{
	tCliente tmp;
	int menor;

	for(int i=0;i<listaClientesOrdenada.cont-1;i++)//ordenacion por seleccion directa
	{
		menor=i;
		for(int j = i+1; j < listaClientesOrdenada.cont;j++)
			if(strcmp(listaClientesOrdenada.conjuntoClientes[j].apellidos,listaClientesOrdenada.conjuntoClientes[menor].apellidos) < 0)
				menor = j;
		if(menor > i)
		{	
			tmp = listaClientesOrdenada.conjuntoClientes[i];
			listaClientesOrdenada.conjuntoClientes[i] = listaClientesOrdenada.conjuntoClientes[menor];
			listaClientesOrdenada.conjuntoClientes[menor] = tmp;
		}
	}
}
void importarDatos(tListaPeliculas &listaPeliculas, tListaClientes &listaClientes)
{
	if(importarDatosPeliculas(listaPeliculas))
	{
		cout << "Se ha importado la Lista de Peliculas SATISFACTORIAMENTE " << endl;
		if(importarDatosClientes(listaClientes))
			cout << "Se ha importado la Lista de Clientes SATISFACTORIAMENTE " << endl;
		else
			cout << "NO se ha podido importar la Lista de Clientes " << endl;
	}
	else
		cout << "NO se ha podido importar la Lista de Peliculas " << endl;
}
bool importarDatosPeliculas(tListaPeliculas &listaPeliculas)//importacion de peliculas desde archivo de texto
{
	ifstream input("pelis.txt");
	tPalabra aux;
	int auxGenero;
	bool ok = false;

	nuevaListaPeliculas(listaPeliculas);

	if(input.is_open())	
	{

		input >> listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].codigo;
		while(listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].codigo != -1)
		{
			if(listaPeliculas.contador == listaPeliculas.capacidad)
				aumentarCapacidadPeliculas(listaPeliculas);
			else
			{
				input.getline(aux,80);
				input.getline(listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].titulo,80); //como cadena de caracteres

				input >> auxGenero;
				listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].genero = tGenero(auxGenero); //debe hacer casting para convertirlo al tipo enumerado

				input >> listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].duracion;
				input >> listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].precio;
				input >> listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].disponible;

				listaPeliculas.contador++;

				input >> listaPeliculas.conjuntoPeliculas[listaPeliculas.contador].codigo;
			}
		}
		input.close();
		ok = true; //se ha importado de manera satisfactoria
	}

	return ok;
}
bool importarDatosClientes(tListaClientes &listaClientes) //importacion de clientes desde archivo de texto
{
	int auxGenero;
	tPalabra aux;
	bool ok = false;
	ifstream input("clientes.txt");

	nuevaListaClientes(listaClientes);// el array debe en memoria debe destruirse aqui y crearse uno nuevo sin nada

	if(input.is_open())
	{
		input >> listaClientes.conjuntoClientes[listaClientes.cont].NIF;	

		while(strcmp(listaClientes.conjuntoClientes[listaClientes.cont].NIF,"x") != 0)		
		{
			if(listaClientes.cont == listaClientes.capacidad) //si la lista esta llena, aumenta la capacidad
				aumentarCapacidadClientes(listaClientes);
			else
			{
				input.getline(aux,80);
				input >> listaClientes.conjuntoClientes[listaClientes.cont].nombre;
				input.getline(aux,80);
				input.getline(listaClientes.conjuntoClientes[listaClientes.cont].apellidos,80);	
				
				input >> auxGenero;
				input,listaClientes.conjuntoClientes[listaClientes.cont].genero = tGenero(auxGenero); //debe hacer casting para convertirlo al tipo enumerado

				listaClientes.conjuntoClientes[listaClientes.cont].peliculasVisionadas.cont = 0; // el contador de las peliculas visionadas de ese usuario se inicia a 0

				importarPeliculasVisionadas(listaClientes.conjuntoClientes[listaClientes.cont],input);
				
				listaClientes.cont++;
				input >> listaClientes.conjuntoClientes[listaClientes.cont].NIF;
			}	
		}
		input.close();
		ok = true; //se ha importado de manera satisfactoria
	}

	return ok;
}
void importarPeliculasVisionadas(tCliente &cliente, ifstream &input) //importa las peliculas visionadas por cliente desde archivo de texto
{
		char gustar;

		input >> cliente.peliculasVisionadas.PeliculasVistas[cliente.peliculasVisionadas.cont].codigo;

		while ((cliente.peliculasVisionadas.PeliculasVistas[cliente.peliculasVisionadas.cont].codigo != -1) &&(cliente.peliculasVisionadas.cont < MAX_VISIONADAS))
		{
			input >> gustar;
			if (gustar=='S')
				cliente.peliculasVisionadas.PeliculasVistas[cliente.peliculasVisionadas.cont].gustar = true;
			else
				cliente.peliculasVisionadas.PeliculasVistas[cliente.peliculasVisionadas.cont].gustar = false;
				
			cliente.peliculasVisionadas.cont++;

			input >> cliente.peliculasVisionadas.PeliculasVistas[cliente.peliculasVisionadas.cont].codigo;	
		}
}
void nuevaListaPeliculas(tListaPeliculas &listaPeliculas) //crea un nuevo array de diez peliculas(necesario en la transferencia de texto a binario) y borra el anterior
{
	delete [] listaPeliculas.conjuntoPeliculas; //borra el antiguo array

	listaPeliculas.conjuntoPeliculas = new tPelicula[10]; //el puntero apuntara a 10 peliculas
	listaPeliculas.capacidad = 10; //se cambia la capacidad del nuevo array(el contador sigue igual)
	listaPeliculas.contador = 0; //el contador se pone a 0
}
void nuevaListaClientes(tListaClientes &listaClientes) //crea un nuevo array de diez clientes (necesario en la transferencia de texto a binario) y borra el anterior
{
	delete [] listaClientes.conjuntoClientes; //borra el antiguo array

	listaClientes.conjuntoClientes = new tCliente[10]; //el puntero apuntara a 10 peliculas
	listaClientes.capacidad = 10; //se cambia la capacidad del nuevo array(el contador sigue igual)
	listaClientes.cont = 0; //el contador se pone a 0
}
void aumentarCapacidadPeliculas(tListaPeliculas &listaPeliculas) //aumenta la capacidad de las peliculas si es necesario
{
	tPeliculaPtr aux;

	aux = new tPelicula[(listaPeliculas.capacidad * 3) / 2 + 1]; //nuevo puntero con la nueva capacidad

	for(int i = 0; i << listaPeliculas.contador; i++)
		aux[i] = listaPeliculas.conjuntoPeliculas[i]; //copia los componentes del viejo array al nuevo

	delete [] listaPeliculas.conjuntoPeliculas; //borra el antiguo array

	listaPeliculas.conjuntoPeliculas = aux; //el puntero del nuevo array(auxiliar) se convierte en el puntero de la lista de peliculas 
	listaPeliculas.capacidad = (listaPeliculas.capacidad * 3) / 2 + 1; //se cambia la capacidad del nuevo array(el contador sigue igual)
}
void aumentarCapacidadClientes(tListaClientes &listaClientes) //aumenta la capacidad de los clientes si es necesario
{
	tClientePtr aux;

	aux = new tCliente[(listaClientes.capacidad * 3) / 2 + 1]; //nuevo puntero con la nueva capacidad

	for(int i = 0; i << listaClientes.cont; i++)
		aux[i] = listaClientes.conjuntoClientes[i]; //copia los componentes del viejo array al nuevo

	delete [] listaClientes.conjuntoClientes; //borra el antiguo array

	listaClientes.conjuntoClientes = aux; //el puntero del nuevo array(auxiliar) se convierte en el puntero de la lista de clientes 
	listaClientes.capacidad = (listaClientes.capacidad * 3) / 2 + 1; //se cambia la capacidad del nuevo array(el contador sigue igual)
}