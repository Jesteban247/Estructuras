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
        vector<vector<int>> matrizAdyacencia;

    public:
        void agregarNodo(const T& nodo);

        void agregarArista(const T& origen, const T& destino, int peso);

        int cantidadVertices();

        int cantidadAristas();

        bool buscarVertice(const T& nodo);

        bool buscarArista(const T& origen, const T& destino);

        void eliminarVertice(const T& nodo);

        void eliminarArista(const T& origen, const T& destino);

        void imprimirMatrizAdyacencia();

        void imprimirGrafo();
    

        //Recorridos
    
            // Función auxiliar para el DFS
            void dfs(int nodoActual, vector<bool>& visitado);

            // Función para realizar el recorrido en profundidad (DFS) desde un nodo dado
            void recorridoEnProfundidad(const T& inicio);

            // Función para realizar el recorrido en anchura (BFS) desde un nodo dado
            void recorridoEnAnchura(const T& inicio);

            // Función para realizar el recorrido plano
            void recorridoPlano();

        // Caminos de Hamilton

            // Función auxiliar para el algoritmo de Hamilton
            bool encontrarCaminoHamiltonRecursivo(vector<int>& camino, vector<bool>& visitado, int nodoActual);

            // Función para encontrar un camino de Hamilton en el grafo
            bool encontrarCaminoHamilton();
    
        // Ciclos de Hamilton

            // Función auxiliar para el algoritmo de Hamilton
            bool encontrarCicloHamiltonRecursivo(vector<int>& ciclo, vector<bool>& visitado, int nodoActual, int nodoInicial);

            // Función para encontrar un ciclo de Hamilton en el grafo
            bool encontrarCicloHamilton();
            
        // Caminos de Euler

            int gradoVertice(int indiceNodo);

            // Función auxiliar para el algoritmo de Euler
            bool encontrarCaminoEulerRecursivo(vector<int>& camino, vector<vector<int>>& copiaMatrizAdyacencia, int nodoActual);

            // Función para encontrar un camino de Euler en el grafo
            bool encontrarCaminoEuler();

        // Ciclos de Euler

            // Función para encontrar un ciclo de Euler en el grafo
            bool encontrarCicloEuler();
   
        // Algoritmo de Prim

            void Prim(const T& nodoInicio);
    
        // Algoritmo de Dijkstra

            // Función para encontrar el vértice no visitado con la distancia mínima
            int encontrarVerticeMinimo(const vector<int>& distancias, const vector<bool>& visitado);

            void Dijkstra(const T& nodoInicio);

        // Algoritmo de Kruskal

            // Función auxiliar para encontrar el conjunto al que pertenece un nodo
            int encontrar(vector<int>& padres, int i);

            // Función auxiliar para unir dos conjuntos
            void unir(vector<int>& padres, int x, int y);

            void Kruskal();

        // Algoritmo de Floyd-Warshall

            // Crea una funcion para el algoritmo de Floyd-Warshall y muestra las 2 matrices
            void FloydWarshall();

};


#include "grafo.hxx"

#endif
