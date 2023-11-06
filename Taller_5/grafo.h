#ifndef grafo_H
#define grafo_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <vector>
#include <set>
#include <climits>


using namespace std;

template <class T>
class GrafoNoDirigido 
{
    private:
        map<T, int> nodosMap; // Mapeo de nodos a índices
        vector<T> nodos;
        vector<vector<double>> matrizAdyacencia;

    public:

        //Funciones de Insercion
        void agregarNodo(const T& nodo);
        void agregarArista(const T& origen, const T& destino, double peso);

        //Funcion de Recorrido
        vector<T> Recorrido(const T& nodoInicio);

};


#include "grafo.hxx"

#endif
