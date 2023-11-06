#include "grafo.h"

template <class T>
void GrafoNoDirigido<T>::agregarNodo(const T& nodo) {
    if (nodosMap.find(nodo) == nodosMap.end()) {
        nodosMap[nodo] = nodos.size();
        nodos.push_back(nodo);
        // Añadir una fila y columna a la matriz de adyacencia
        for (vector<int>& fila : matrizAdyacencia) {
            fila.push_back(0);
        }
        matrizAdyacencia.push_back(vector<int>(nodos.size(), 0));
    }
}

template <class T>
void GrafoNoDirigido<T>::agregarArista(const T& origen, const T& destino) {
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        matrizAdyacencia[indiceOrigen][indiceDestino] = 1;
        matrizAdyacencia[indiceDestino][indiceOrigen] = 1; // El grafo es no dirigido, así que agregamos la arista en ambas direcciones
    }
}

template <class T>
int GrafoNoDirigido<T>::cantidadVertices() {
    return nodos.size();
}

template <class T>
int GrafoNoDirigido<T>::cantidadAristas() {
    int conteo = 0;
    for (const vector<int>& fila : matrizAdyacencia) {
        for (int valor : fila) {
            if (valor != 0) {
                conteo++;
            }
        }
    }
    return conteo / 2; // El grafo es no dirigido, dividir por 2 para contar cada arista una sola vez
}

template <class T>
bool GrafoNoDirigido<T>::buscarVertice(const T& nodo) {
    return nodosMap.find(nodo) != nodosMap.end();
}

template <class T>
bool GrafoNoDirigido<T>::buscarArista(const T& origen, const T& destino) {
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        return matrizAdyacencia[indiceOrigen][indiceDestino] == 1;
    }
    return false;
}

template <class T>
void GrafoNoDirigido<T>::eliminarVertice(const T& nodo) {
    if (nodosMap.find(nodo) != nodosMap.end()) {
        int indice = nodosMap[nodo];
        nodosMap.erase(nodo);
        nodos.erase(nodos.begin() + indice);
        matrizAdyacencia.erase(matrizAdyacencia.begin() + indice);
        for (vector<int>& fila : matrizAdyacencia) {
            fila.erase(fila.begin() + indice);
        }
    }
}

template <class T>
void GrafoNoDirigido<T>::eliminarArista(const T& origen, const T& destino) {
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        matrizAdyacencia[indiceOrigen][indiceDestino] = 0;
        matrizAdyacencia[indiceDestino][indiceOrigen] = 0;
    }
}

template <class T>
void GrafoNoDirigido<T>::imprimirMatrizAdyacencia() {
    cout << "    ";
    for (const T& nodo : nodos) {
        cout << nodo << " ";
    }
    cout << endl;
    cout << "______";
    for (const T& nodo : nodos) {
        cout << "__";
    }
    cout << endl;
    for (int i = 0; i < nodos.size(); i++) {
        cout << nodos[i] << " | ";
        for (int j = 0; j < nodos.size(); j++) {
            cout << matrizAdyacencia[i][j] << " ";
        }
        cout << endl;
    }
}

template <class T>
void GrafoNoDirigido<T>::imprimirGrafo() {
    for (int i = 0; i < nodos.size(); i++) {
    cout << nodos[i] << " -> ";
    for (int j = 0; j < nodos.size(); j++) {
        if (matrizAdyacencia[i][j] == 1) {
            cout << nodos[j] << " ";
        }
    }
    cout << endl;
    }
}

//Recorridos
    
    // Función auxiliar para el DFS
    template <class T>
    void GrafoNoDirigido<T>::dfs(int nodoActual, vector<bool>& visitado) {
        visitado[nodoActual] = true;
        cout << nodos[nodoActual] << " ";

        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[nodoActual][i] == 1 && !visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

    // Función para realizar el recorrido en profundidad (DFS) desde un nodo dado
    template <class T>
    void GrafoNoDirigido<T>::recorridoEnProfundidad(const T& inicio) {
        if (nodosMap.find(inicio) != nodosMap.end()) {
            int indiceInicio = nodosMap[inicio];
            vector<bool> visitado(nodos.size(), false);
            dfs(indiceInicio, visitado);
        }
    }

    // Función para realizar el recorrido en anchura (BFS) desde un nodo dado
    template <class T>
    void GrafoNoDirigido<T>::recorridoEnAnchura(const T& inicio) {
        if (nodosMap.find(inicio) != nodosMap.end()) {
            int indiceInicio = nodosMap[inicio];
            vector<bool> visitado(nodos.size(), false);
            queue<int> cola;

            visitado[indiceInicio] = true;
            cola.push(indiceInicio);

            while (!cola.empty()) {
                int nodoActual = cola.front();
                cola.pop();
                cout << nodos[nodoActual] << " ";

                for (int i = 0; i < nodos.size(); i++) {
                    if (matrizAdyacencia[nodoActual][i] == 1 && !visitado[i]) {
                        visitado[i] = true;
                        cola.push(i);
                    }
                }
            }
        }
    }

    // Función para realizar el recorrido plano
    template <class T>
    void GrafoNoDirigido<T>::recorridoPlano() {
        vector<bool> visitado(nodos.size(), false);
        for (int i = 0; i < nodos.size(); i++) {
            if (!visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

// Caminos de Hamilton

    // Función auxiliar para el algoritmo de Hamilton
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCaminoHamiltonRecursivo(vector<int>& camino, vector<bool>& visitado, int nodoActual) {
        if (camino.size() == nodos.size()) {
            // Se encontró un camino de Hamilton
            return true;
        }

        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[nodoActual][i] == 1 && !visitado[i]) {
                visitado[i] = true;
                camino.push_back(i);

                if (encontrarCaminoHamiltonRecursivo(camino, visitado, i)) {
                    return true;
                }

                visitado[i] = false;
                camino.pop_back();
            }
        }

        return false;
    }

    // Función para encontrar un camino de Hamilton en el grafo
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCaminoHamilton() {
        vector<int> camino;
        vector<bool> visitado(nodos.size(), false);

        // Comenzar desde el primer nodo
        int nodoInicial = 0;
        camino.push_back(nodoInicial);
        visitado[nodoInicial] = true;

        if (encontrarCaminoHamiltonRecursivo(camino, visitado, nodoInicial)) {
            // Se encontró un camino de Hamilton, imprímelo
            cout << "Camino de Hamilton encontrado: ";
            for (int nodo : camino) {
                cout << nodos[nodo] << " ";
            }
            cout << endl;
            return true;
        } else {
            cout << "No se encontró un camino de Hamilton en el grafo." << endl;
            return false;
        }
    }


// Ciclos de Hamilton

    // Función auxiliar para el algoritmo de Hamilton
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCicloHamiltonRecursivo(vector<int>& ciclo, vector<bool>& visitado, int nodoActual, int nodoInicial) {
        if (ciclo.size() == nodos.size()) {
            // Se encontró un ciclo de Hamilton
            if (matrizAdyacencia[nodoActual][nodoInicial] == 1) {
                ciclo.push_back(nodoInicial);
                return true;
            }
        }

        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[nodoActual][i] == 1 && !visitado[i]) {
                visitado[i] = true;
                ciclo.push_back(i);

                if (encontrarCicloHamiltonRecursivo(ciclo, visitado, i, nodoInicial)) {
                    return true;
                }

                visitado[i] = false;
                ciclo.pop_back();
            }
        }

        return false;
    }

    // Función para encontrar un ciclo de Hamilton en el grafo
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCicloHamilton() {
        vector<int> ciclo;
        vector<bool> visitado(nodos.size(), false);

        // Comenzar desde el primer nodo
        int nodoInicial = 0;
        ciclo.push_back(nodoInicial);
        visitado[nodoInicial] = true;

        if (encontrarCicloHamiltonRecursivo(ciclo, visitado, nodoInicial, nodoInicial)) {
            // Se encontró un ciclo de Hamilton, imprímelo
            cout << "Ciclo de Hamilton encontrado: ";
            for (int nodo : ciclo) {
                cout << nodos[nodo] << " ";
            }
            cout << endl;
            return true;
        } else {
            cout << "No se encontró un ciclo de Hamilton en el grafo." << endl;
            return false;
        }
    }


// Caminos de Euler
    template <class T>
    int GrafoNoDirigido<T>::gradoVertice(int indiceNodo) {
        int grado = 0;
        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[indiceNodo][i] == 1) {
                grado++;
            }
        }
        return grado;
    }

    // Función auxiliar para el algoritmo de Euler
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCaminoEulerRecursivo(vector<int>& camino, vector<vector<int>>& copiaMatrizAdyacencia, int nodoActual) {
        for (int i = 0; i < nodos.size(); i++) {
            if (copiaMatrizAdyacencia[nodoActual][i] == 1) {
                copiaMatrizAdyacencia[nodoActual][i] = 0;
                copiaMatrizAdyacencia[i][nodoActual] = 0;
                camino.push_back(i);

                if (camino.size() == (cantidadAristas() + 1)) {
                    return true;  // Se encontró un camino de Euler
                }

                if (encontrarCaminoEulerRecursivo(camino, copiaMatrizAdyacencia, i)) {
                    return true;
                }

                camino.pop_back();
                copiaMatrizAdyacencia[nodoActual][i] = 1;
                copiaMatrizAdyacencia[i][nodoActual] = 1;
            }
        }

        return false;
    }

    // Función para encontrar un camino de Euler en el grafo
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCaminoEuler() {
        vector<int> camino;

        // Buscar un nodo inicial para comenzar el camino
        int nodoInicial = 0;
        for (int i = 0; i < cantidadVertices(); i++) {
            if (gradoVertice(i) > 0) {
                nodoInicial = i;
                break;
            }
        }

        camino.push_back(nodoInicial);

        // Copiar la matriz de adyacencia para marcar aristas visitadas
        vector<vector<int>> copiaMatrizAdyacencia = matrizAdyacencia;

        if (encontrarCaminoEulerRecursivo(camino, copiaMatrizAdyacencia, nodoInicial)) {
            // Se encontró un camino de Euler, imprímelo
            cout << "Camino de Euler encontrado: ";
            for (int nodo : camino) {
                cout << nodos[nodo] << " ";
            }
            cout << endl;
            return true;
        } else {
            cout << "No se encontró un camino de Euler en el grafo." << endl;
            return false;
        }
    }


// Ciclos de Euler

    // Función para encontrar un ciclo de Euler en el grafo
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCicloEuler() {
        vector<int> ciclo;

        // Copiar la matriz de adyacencia para marcar aristas visitadas
        vector<vector<int>> copiaMatrizAdyacencia = matrizAdyacencia;

        // Buscar un nodo inicial para comenzar el ciclo
        int nodoInicial = 0;
        for (int i = 0; i < cantidadVertices(); i++) {
            if (gradoVertice(i) > 0) {
                nodoInicial = i;
                break;
            }
        }

        if (encontrarCaminoEulerRecursivo(ciclo, copiaMatrizAdyacencia, nodoInicial)) {
            // Verificar si el ciclo encontrado es un ciclo de Euler
            if (ciclo.size() == (cantidadAristas() + 1) && copiaMatrizAdyacencia[nodoInicial][ciclo.back()] == 1) {
                // Se encontró un ciclo de Euler, imprímelo
                cout << "Ciclo de Euler encontrado: ";
                for (int nodo : ciclo) {
                    cout << nodos[nodo] << " ";
                }
                cout << endl;
                return true;
            }
        }

        cout << "No se encontró un ciclo de Euler en el grafo." << endl;
        return false;
    }


