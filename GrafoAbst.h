#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
using namespace std;

#include "Objeto.h"

class GrafoAbst
{
    // Representa un grafo con vértices de tipo derivado de Objeto.
    // Ver Objeto para los requerimientos sobre las clases derivadas.

public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de vértices o nodos.

    // REQ: 0 < p < 1.
    // Construye un GrafoAbst con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    // NOTA: todos los vértices son inicializados con copias del objeto apuntado por "po".
    GrafoAbst(int N, double p, Objeto* po);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // Inicializa los vértices con copias del objeto apuntado por "po".
    // NOTA: todos los vértices son inicializados con copias del objeto apuntado por "po".
    GrafoAbst(ifstream& archivo, Objeto* po);

    // Construye una copia idéntica a orig.
    GrafoAbst(const GrafoAbst& orig);

    // Destructor
    ~GrafoAbst();

    /* MÉTODOS OBSERVADORES */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el GrafoAbst.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el GrafoAbst.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna una copia del vértice para que NO pueda ser modificado.
    Objeto& operator[](int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el GrafoAbst.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el GrafoAbst.
    int obtTotVrt() const;

    // REQ: 0 <= idVrt < N.
    // EFE: Retorna por "caminosMinimos" los caminos más cortos entre idVrtO y todos los demás vértices.
    // REF1: https://es.wikipedia.org/wiki/Algoritmo_de_Dijkstra
    // REF2: https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
    // SUPUESTO#1: El grafo es conectado, por lo que caminosMinimos.size() == N - 1.
    // SUPUESTO#2: La distancia entre dos vértices directamente conectados es siempre uno.
    void obtCaminosMinimos(int idVrtO, vector< vector< int >>& caminosMinimos) const;

    // REQ: 0 <= idVrt < N.
    // EFE: Retorna por recorrido la secuencia de idVrt por anchura primero.
    // REF: https://es.wikipedia.org/wiki/B%C3%BAsqueda_en_anchura
    // SUPUESTO: que grafo es conectado, por lo que recorrido.size() == N.
    void obtRecorridoXanchura(int idVrtO, vector< int >& recorrido) const;

    // EFE: permite que el digrafo sea consumido por un flujo mediante el operator<<.
    // NOTA: es una función externa a la clase que por hacer acceso a los atributos privados
    //       del conjunto se debe declarar como friend. Sustituye a toString().
    friend ostream& operator<<(ostream& o, const GrafoAbst& g);

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna el vértice para que pueda ser modificado.
    Objeto& operator[](int idVrt);

private:

    struct Nodo 
    {
        Objeto* t;
        list< int > listaAdy;

        // constructor estándar de Nodo
        Nodo() : t(0), listaAdy() {}; 
        // constructor con dato de vértice
        Nodo(const Objeto* obj_p) : t(&(obj_p->clonar())), listaAdy() {}; 
        // constructor de copias de Nodo
        Nodo(const Nodo& vrt) : t(&(vrt.t->clonar())), listaAdy(vrt.listaAdy) {};
        ~Nodo() { delete t; }
    };

    vector< Nodo > nodos; // vector de vértices
};

GrafoAbst::GrafoAbst(int N, double p, Objeto* po) : nodos(N) // reserva espacio para N nodos
{
    // Se genera una semilla para la secuencia de números al azar:
    srand(time(NULL));

    // Variable donde se almacena el número aleatorio
    double p_ady;

    // Se generan las adyacencias en cada vértice
    for (int i = 0; i < N; i++)
    {
        nodos[i].t = &(po->clonar()); // Inicializa nodos[i] con copias del objeto apuntado por "po"
        for (int f = i + 1; f < N; f++)
        {
            p_ady = (rand() / (1.0 * RAND_MAX));
            // Req: p sea mayor que el número aleatorio
            if (p_ady < p)
            {
                nodos[i].listaAdy.push_back(f);
                nodos[f].listaAdy.push_back(i);
            }
        }
    }
}

GrafoAbst::GrafoAbst(ifstream& archivo, Objeto* po) 
{
    string linea;
    string entero;
    int indice = 0;

    // Se lee el tamaño del grafo y se crea basado en nodos estandar
    (archivo >> linea);
    int cantidadNodos = stoi(linea);
    nodos.resize(cantidadNodos);

    // Se crean las listas de adyacencias
    while (archivo >> linea)
    {
        nodos[indice].t = &(po->clonar()); // Inicializa nodos[i] con copias del objeto apuntado por "po"
        stringstream s(linea);
        while (getline(s, entero, ','))
        {
            int d = stoi(entero);
            nodos[indice].listaAdy.push_back(d);
        }
        indice++;
    }
}

GrafoAbst::GrafoAbst(const GrafoAbst& orig) 
{
    this->nodos = orig.nodos;
}

GrafoAbst::~GrafoAbst() 
{}

bool GrafoAbst::xstVrt(int idVrt) const 
{
    int tamnioGrafo = nodos.size();
    if (0 <= idVrt && idVrt < tamnioGrafo)
    {
        return true;
    }
    return false;
}

bool GrafoAbst::xstAdy(int idVrtO, int idVrtD) const 
{
    // Se busca que el elemento idVrtD esté en la lista adys de idVrtO
    list< int >::const_iterator itr;
    itr = find(nodos[idVrtO].listaAdy.begin(), nodos[idVrtO].listaAdy.end(), idVrtD);

    if (itr != nodos[idVrtO].listaAdy.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GrafoAbst::obtIdVrtAdys(int idVrt, vector< int >& rsp) const 
{
    int vertice;
    for (list< int >::const_iterator itr = nodos[idVrt].listaAdy.begin(); itr != nodos[idVrt].listaAdy.end(); itr++)
    {
        vertice = *itr;
        rsp.push_back(vertice);
    }
}

int GrafoAbst::obtCntVrtAdys(int idVrt) const 
{
    return nodos[idVrt].listaAdy.size();
}

Objeto& GrafoAbst::operator[](int idVrt) const 
{
    Objeto* po;
    po = nodos[idVrt].t;
    return *po;
}

int GrafoAbst::obtTotArc() const 
{
    int cantidadAdys = 0;
    for (int i = 0; i < nodos.size(); i++)
    {
        cantidadAdys = nodos[i].listaAdy.size() + cantidadAdys;
    }
    cantidadAdys = cantidadAdys / 2;
    return cantidadAdys;
}

int GrafoAbst::obtTotVrt() const 
{
    return nodos.size();
}

Objeto& GrafoAbst::operator[](int idVrt) 
{
    Objeto* po;
    po = nodos[idVrt].t;
    return *po;
}

void GrafoAbst::obtCaminosMinimos(int idVrtO, vector< vector< int >>& caminosMinimos) const 
{
    // Se reserva espacio para caminosMinimos
    caminosMinimos.resize(nodos.size() - 1);
    // Mapa que funciona como padre, para obtener los caminos minimos
    map<int, int> mapaPadre;
    // Vector para guardar las distancias del nodo origen al resto de vertices 
    vector< int> distancia;
    distancia.resize(nodos.size());
    // Vector bool para controlar los vértices que ya han sido visitados
    vector< bool> visto;
    visto.resize(nodos.size());

    // Se asignan valores de distancia por defecto
    for (int i = 0; i < nodos.size(); i++)
    {
        // NO existe una adyacencia entre idVrtO y "i"
        list< int>::const_iterator itrDistancia = find(nodos[idVrtO].listaAdy.begin(), nodos[idVrtO].listaAdy.end(), i);
        if (itrDistancia == nodos[idVrtO].listaAdy.end())
        {
            distancia[i] = 99;  // 99 ~ Infinito
        }
        // Existe una adyacencia entre idVrtO y i
        else
        {
            distancia[i] = 1;
        }
    }
    // Se asigna el valor de idVrtO por defecto
    distancia[idVrtO] = 0;

    // Se generan las distancias mientras existan nodos/vertices sin revisar
    bool todosVistos = true;
    while (todosVistos == true)
    {
        // Se toma el vertice con la distancia mínima y que aún no haya sido visitado
        int minimo = *max_element(distancia.begin(), distancia.end());
        int vertice;
        for (int i = 0; i < distancia.size(); i++)
        {
            if (visto[i] == false && distancia[i] <= minimo)
            {
                minimo = distancia[i];
                vertice = i;
            }
        }

        // Se asigna visto = true de visto[vertice]
        visto[vertice] = true;

        // Se calculan las nuevas distancias y se asigna valor para el padre
        for (list<int>::const_iterator itrAdy = nodos[vertice].listaAdy.begin(); itrAdy != nodos[vertice].listaAdy.end(); itrAdy++)
        {
            if (distancia[vertice] < distancia[*itrAdy])
            {
                mapaPadre[*itrAdy] = vertice;
                distancia[*itrAdy] = distancia[vertice] + 1;
            }
        }

        // Se verifica que aún existan nodos/vertices sin revisar
        vector< bool>::const_iterator itrVisto = find(visto.begin(), visto.end(), false);
        if (itrVisto == visto.end())
        {
            todosVistos = false;
        }
    }

    // Se agregan los caminosMinimos, utilizando el mapaPadre
    int indice = 0;
    for (int i = 0; i < nodos.size(); i++)
    {
        if (i != idVrtO)
        {
            int nodoDest = i;
            while (mapaPadre[nodoDest] != idVrtO)
            {
                caminosMinimos[indice].push_back(nodoDest);
                nodoDest = mapaPadre[nodoDest];
            }
            caminosMinimos[indice].push_back(nodoDest);
            reverse(caminosMinimos[indice].begin(), caminosMinimos[indice].end());
            indice++;
        }
    }
}

void GrafoAbst::obtRecorridoXanchura(int idVrtO, vector< int >& recorrido) const 
{
    // Vector de booleanos, indica si los nodos han sido visitados
    vector<bool> visto;
    visto.resize(nodos.size());
    // Lista de prioridad, almacena temporalmente los nodos por nivel
    list<int> listaPrioridad;
    // Para iterar en la lista de ady
    list<int>::const_iterator itr;

    // Se agrega idVrtO por defecto
    visto[idVrtO] = true;
    listaPrioridad.push_back(idVrtO);

    // Se recorre la lista de prioridad y se agregan a "recorrido"
    int nodoActual = idVrtO;
    while (!listaPrioridad.empty())
    {
        nodoActual = listaPrioridad.front();
        recorrido.push_back(nodoActual);
        listaPrioridad.pop_front();

        for (itr = nodos[nodoActual].listaAdy.begin(); itr != nodos[nodoActual].listaAdy.end(); ++itr)
        {
            if (!visto[*itr])
            {
                visto[*itr] = true;
                listaPrioridad.push_back(*itr);
            }
        }
    }
}

ostream& operator<<(ostream& o, const GrafoAbst& g) 
{
    ostringstream fs;

    for (auto p : g.nodos) {
        int cnt = p.listaAdy.size();
        int i = 0;
        for (auto ady : p.listaAdy) {
            fs << ady;
            if (i < cnt - 1)
                fs << ',';
            i++;
        }
        fs << endl;
    }
    o << fs.str();
    return o;
}