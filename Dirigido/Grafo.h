#ifndef grafo_H
#define grafo_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

const int INFINITO = 1000000;

template <class T>
class Grafo 
{
    private:
        map<T, int> nodosMap; // Mapeo de nodos a índices
        vector<T> nodos;
        vector<vector<int>> matrizAdyacencia;

    public:
        void agregarNodo(const T& nodo);

        void agregarArista(const T& origen, const T& destino, int peso);

        void eliminarVertice(const T& nodo);

        void eliminarArista(const T& origen, const T& destino);

        void imprimirMatrizAdyacencia();

        bool Conectado();

        multimap<int, int> Prim(const T& nodoInicio);

        multimap<int, int> Dijkstra(const T& origen);

        vector<int> FloydWarshall(const T& origen, const T& destino);

        


};


#include "Grafo.hxx"

#endif
