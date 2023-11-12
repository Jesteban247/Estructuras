#ifndef GRAFO_HXX
#define GRAFO_HXX

#include "Grafo.h"

template <typename T>
void Grafo<T>::agregarNodo(const T& nodo) 
{
    if (nodosMap.find(nodo) == nodosMap.end()) 
    {
        nodosMap[nodo] = nodos.size();
        nodos.push_back(nodo);
        
        // Añadir una nueva fila a la matriz de adyacencia con ceros
        matrizAdyacencia.push_back(vector<int>(nodos.size(), 0));

        // Actualizar todas las filas existentes añadiendo un nuevo elemento inicializado en 0
        for (int i = 0; i < matrizAdyacencia.size() - 1; i++) {
            matrizAdyacencia[i].push_back(0);
        }
    }
}

template <typename T>
void Grafo<T>::agregarArista(const T& origen, const T& destino, int peso) 
{
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end())
    {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        matrizAdyacencia[indiceOrigen][indiceDestino] = peso;
    }
    
}

template <typename T>
void Grafo<T>::imprimirVecinosEntrantes(const T& nodo) {
    if (nodosMap.find(nodo) != nodosMap.end()) {
        int indiceDestino = nodosMap[nodo];
        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[i][indiceDestino] != 0) {
                cout << nodos[i] << " --- " << matrizAdyacencia[i][indiceDestino] << " ---> " << nodo << endl;
            }
        }
    }
}

#endif // GRAFO_HXX