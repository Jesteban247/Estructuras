#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

template <typename T>
class Grafo {
public:
    void agregarNodo(const T& nodo);
    void agregarArista(const T& origen, const T& destino, int peso);
    void imprimirVecinosEntrantes(const T& nodo);

private:
    map<T, int> nodosMap;
    vector<T> nodos;
    vector<vector<int>> matrizAdyacencia;
};

#include "Grafo.hxx"

#endif // GRAFO_H
