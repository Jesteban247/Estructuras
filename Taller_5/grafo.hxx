#include "grafo.h"

//Funciones de Insercion
    template <class T>
    void GrafoNoDirigido<T>::agregarNodo(const T& nodo) {
        if (nodosMap.find(nodo) == nodosMap.end()) {
            nodosMap[nodo] = nodos.size();
            nodos.push_back(nodo);
            // Añadir una fila y columna a la matriz de adyacencia
            for (vector<double>& fila : matrizAdyacencia) {
                fila.push_back(0);
            }
            matrizAdyacencia.push_back(vector<double>(nodos.size(), 0));
        }
    }

    template <class T>
    void GrafoNoDirigido<T>::agregarArista(const T& origen, const T& destino, double peso) {
        if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
            int indiceOrigen = nodosMap[origen];
            int indiceDestino = nodosMap[destino];

            matrizAdyacencia[indiceOrigen][indiceDestino] = peso;
            matrizAdyacencia[indiceDestino][indiceOrigen] = peso; // El grafo es no dirigido, así que agregamos la arista en ambas direcciones
        }
    }


//Funcion de Recorrido
    template <class T>
    vector<T> GrafoNoDirigido<T>::Recorrido(const T& nodoInicio)
    {
        int inicio = nodosMap[nodoInicio];

        vector<int> visitados(matrizAdyacencia.size(), 0);
        vector<int> ruta;
        ruta.push_back(inicio);

        visitados[inicio] = 1;
        double distanciaTotal = 0.0; // Inicializamos la distancia total

        while (ruta.size() < nodos.size()) {
            int nodoActual = ruta.back();
            int nodoCercano = -1;
            double pesoMinimo = 1000000;

            for (int i = 0; i < matrizAdyacencia.size(); i++) {
                if (i != nodoActual && !visitados[i] && matrizAdyacencia[nodoActual][i] < pesoMinimo) {
                    pesoMinimo = matrizAdyacencia[nodoActual][i];
                    nodoCercano = i;
                }
            }

            if (nodoCercano != -1) {
                ruta.push_back(nodoCercano);
                visitados[nodoCercano] = 1;
                distanciaTotal += pesoMinimo; // Sumamos la distancia del nuevo tramo
            }
        }

        // Construir un vector con los datos de los nodos en la ruta
        vector<T> rutaDatos;
        for (int nodoIndex : ruta) {
            rutaDatos.push_back(nodos[nodoIndex]);
        }

        // Imprimir la ruta y la distancia total
        cout << "Ruta: ";
        for (int i = 0; i < rutaDatos.size(); i++) {
            cout << rutaDatos[i];
            if (i < rutaDatos.size() - 1) {
                cout << "-";
            }
        }
        cout << endl;
        cout << "Distancia total: " << distanciaTotal << endl;

        return rutaDatos;
    }


