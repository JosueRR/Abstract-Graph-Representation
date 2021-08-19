#include <iostream>
using namespace std;

#include "GrafoAbst.h"
#include "Entero.h"

int main()
{
	vector< vector< int >> caminosMinimos;
	vector< int > recorrido;

	// construcción aleatoria:
	Entero n;
	GrafoAbst g_int(10, 0.5, &n);

	// se llenan los vértices con valores válidos:
	for (int i = 0; i < 10; i++) 
	{
		Entero ni(i);
		g_int[i] = ni;
	}

	cout << "GRAFO ALEATORIO" << endl;
	cout << g_int << endl;
	for (int i = 0; i < 10; i++) {
		cout << g_int[i].toString() << ',';
	}

	cout << endl << "------------------------------" << endl;

	/*
	g_int.obtCaminosMinimos(0, caminosMinimos);
	g_int.obtRecorridoXanchura(0, recorrido);
	*/

	// construcción basada en archivo csv:
	ifstream d("grafo_p.txt", ios::in);
	if (!d)
		cout << "problemas para abrir el archivo grafo_p.txt" << endl;
	GrafoAbst g_int1(d, &n);

	// se llenan los vértices con valores válidos:
	int contador = 0;
	for (int i = 9; i >= 0; i--) {
		Entero ni(i);
		g_int1[contador] = ni;
		contador++;
	}

	cout << "GRAFO ARCHIVO _P" << endl;
	cout << g_int1 << endl;
	for (int i = 0; i < 10; i++) {
		cout << g_int1[i].toString() << ',';
	}


	
	g_int1.obtCaminosMinimos(0, caminosMinimos);
	g_int1.obtRecorridoXanchura(0, recorrido);
	
	
	cout << endl;

	return 0;
}