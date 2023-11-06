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
void GrafoNoDirigido<T>::agregarArista(const T& origen, const T& destino, int peso) {
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        matrizAdyacencia[indiceOrigen][indiceDestino] = peso;
        matrizAdyacencia[indiceDestino][indiceOrigen] = peso; // El grafo es no dirigido, así que agregamos la arista en ambas direcciones
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
        return matrizAdyacencia[indiceOrigen][indiceDestino] != 0;
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
        if (matrizAdyacencia[i][j] != 0) {
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
            if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i]) {
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
                    if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i]) {
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
            if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i]) {
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
            if (matrizAdyacencia[nodoActual][nodoInicial] != 0) {
                ciclo.push_back(nodoInicial);
                return true;
            }
        }

        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i]) {
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
            if (matrizAdyacencia[indiceNodo][i] != 0) {
                grado++;
            }
        }
        return grado;
    }

    // Función auxiliar para el algoritmo de Euler
    template <class T>
    bool GrafoNoDirigido<T>::encontrarCaminoEulerRecursivo(vector<int>& camino, vector<vector<int>>& copiaMatrizAdyacencia, int nodoActual) {
        for (int i = 0; i < nodos.size(); i++) {
            int peso = copiaMatrizAdyacencia[nodoActual][i];
            if (copiaMatrizAdyacencia[nodoActual][i] != 0) {
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
                copiaMatrizAdyacencia[nodoActual][i] = peso;
                copiaMatrizAdyacencia[i][nodoActual] = peso;
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

// Algoritmo de Prim
    template <class T>
    void GrafoNoDirigido<T>::Prim(const T& nodoInicio)
    {
        // Crear un conjunto para almacenar los nodos visitados
        set<int> visitados;

        // Crear un conjunto para almacenar los nodos no visitados
        set<int> noVisitados;

        // Agregar el nodo de inicio al conjunto de visitados
        visitados.insert(nodosMap[nodoInicio]);

        // Agregar los demás nodos al conjunto de no visitados
        for (int i = 0; i < nodos.size(); i++) {
            if (i != nodosMap[nodoInicio]) {
                noVisitados.insert(i);
            }
        }

        // Mientras el conjunto de no visitados no esté vacío
        while (!noVisitados.empty()) 
        {
            int nodoActual = -1;
            int nodoAdyacente = -1;
            int pesoMinimo = 1000000;

            // Buscar la arista de menor peso entre los nodos visitados y no visitados
            for (int nodo : visitados) {
                for (int i = 0; i < nodos.size(); i++) {
                    if (noVisitados.find(i) != noVisitados.end() && matrizAdyacencia[nodo][i] != 0 && matrizAdyacencia[nodo][i] < pesoMinimo) {
                        nodoActual = nodo;
                        nodoAdyacente = i;
                        pesoMinimo = matrizAdyacencia[nodo][i];
                    }
                }
            }

            // Agregar el nodo adyacente al conjunto de visitados
            visitados.insert(nodoAdyacente);

            // Eliminar el nodo adyacente del conjunto de no visitados
            noVisitados.erase(nodoAdyacente);

            // Imprimir la arista de menor peso
            cout << nodos[nodoActual] << " - " << nodos[nodoAdyacente] << " (" << pesoMinimo << ")" << endl;
        }
    }


// Algoritmo de Dijkstra

    // Función para encontrar el vértice no visitado con la distancia mínima
    template <class T>
    int GrafoNoDirigido<T>::encontrarVerticeMinimo(const vector<int>& distancias, const vector<bool>& visitado) {
        int minDistancia = INT_MAX;
        int minVertice = -1;

        for (int i = 0; i < distancias.size(); i++) {
            if (!visitado[i] && distancias[i] < minDistancia) {
                minDistancia = distancias[i];
                minVertice = i;
            }
        }

        return minVertice;
    }

    template <class T>
    void GrafoNoDirigido<T>::Dijkstra(const T& nodoInicio) {
        
        int indiceInicio = nodosMap[nodoInicio];

        vector<int> distancias(cantidadVertices(), INT_MAX);
        vector<bool> visitado(cantidadVertices(), false);
        vector<int> padres(cantidadVertices(), -1);

        distancias[indiceInicio] = 0;

        for (int i = 0; i < cantidadVertices() - 1; i++) {
            int verticeMinimo = encontrarVerticeMinimo(distancias, visitado);
            visitado[verticeMinimo] = true;

            for (int j = 0; j < cantidadVertices(); j++) {
                if (!visitado[j] && matrizAdyacencia[verticeMinimo][j] && distancias[verticeMinimo] != INT_MAX &&
                    distancias[verticeMinimo] + matrizAdyacencia[verticeMinimo][j] < distancias[j]) {
                    distancias[j] = distancias[verticeMinimo] + matrizAdyacencia[verticeMinimo][j];
                    padres[j] = verticeMinimo;
                }
            }
        }

        cout << "Vertices de recubrimiento mínimo:" << endl;
        for (int i = 0; i < cantidadVertices(); i++) {
            if (i != indiceInicio) {
                cout << nodos[padres[i]] << " - " << nodos[i] << " (" << matrizAdyacencia[i][padres[i]] << ")" << endl;
            }
        }

    }

// Algoritmo de Kruskal

    // Función auxiliar para encontrar el conjunto al que pertenece un nodo
    template <class T>
    int GrafoNoDirigido<T>::encontrar(vector<int>& padres, int i) {
        if (padres[i] == -1) {
            return i;
        }
        return encontrar(padres, padres[i]);
    }

    // Función auxiliar para unir dos conjuntos
    template <class T>
    void GrafoNoDirigido<T>::unir(vector<int>& padres, int x, int y) {
        int xSet = encontrar(padres, x);
        int ySet = encontrar(padres, y);
        padres[xSet] = ySet;
    }

    template <class T>
    void GrafoNoDirigido<T>::Kruskal() {
        vector<vector<int>> arbol;
        vector<int> padres(cantidadVertices(), -1);

        // Crear una lista de aristas ordenadas por peso
        vector<vector<int>> aristas;
        for (int i = 0; i < cantidadVertices(); i++) {
            for (int j = i + 1; j < cantidadVertices(); j++) {
                if (matrizAdyacencia[i][j] != 0) {
                    aristas.push_back({ matrizAdyacencia[i][j], i, j });
                }
            }
        }
        
        // Ordenar las aristas por peso sin sort
        for (int i = 0; i < aristas.size(); i++) {
            for (int j = i + 1; j < aristas.size(); j++) {
                if (aristas[i][0] > aristas[j][0]) {
                    swap(aristas[i], aristas[j]);
                }
            }
        }

        // Agregar las aristas al árbol de recubrimiento mínimo
        for (int i = 0; i < aristas.size(); i++) {
            int peso = aristas[i][0];
            int origen = aristas[i][1];
            int destino = aristas[i][2];

            int x = encontrar(padres, origen);
            int y = encontrar(padres, destino);

            if (x != y) {
                arbol.push_back({ peso, origen, destino });
                unir(padres, x, y);
            }
        }

        // Imprimir el árbol de recubrimiento mínimo
        cout << "Vertices de recubrimiento mínimo:" << endl;
        for (int i = 0; i < arbol.size(); i++) {
            cout << nodos[arbol[i][1]] << " - " << nodos[arbol[i][2]] << " (" << arbol[i][0] << ")" << endl;
        }
    }

// Algoritmo de Floyd-Warshall
    
    // Crea una funcion para el algoritmo de Floyd-Warshall y muestrame las 2 matrices
    template <class T>
    void GrafoNoDirigido<T>::FloydWarshall() {
        vector<vector<int>> distancias = matrizAdyacencia;
        vector<vector<int>> caminos(cantidadVertices(), vector<int>(cantidadVertices(), -1));

        for (int i = 0; i < cantidadVertices(); i++) {
            for (int j = 0; j < cantidadVertices(); j++) {
                if (i != j && distancias[i][j] == 0) {
                    distancias[i][j] = INT_MAX;
                }
                caminos[i][j] = j;
            }
        }

        for (int k = 0; k < cantidadVertices(); k++) {
            for (int i = 0; i < cantidadVertices(); i++) {
                for (int j = 0; j < cantidadVertices(); j++) {
                    if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX && distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                        distancias[i][j] = distancias[i][k] + distancias[k][j];
                        caminos[i][j] = caminos[i][k];
                    }
                }
            }
        }

        cout << "Matriz de distancias:" << endl;

        int flag=0;
        for (int i = 0; i < cantidadVertices(); i++) {
            cout << nodos[i] << " |";
            for (int j = 0; j < cantidadVertices(); j++) {
                if (distancias[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    if (distancias[i][j] < 10) {
                        cout << distancias[i][j] << " |";
                        flag=1;
                    }
                    else {
                        cout << distancias[i][j] << "|";
                    }
                    
                }
            }
            cout << endl;
        }

        if (flag=1)
        {
            cout << "   ";
            for (int i = 0; i < cantidadVertices(); i++) {
                cout << nodos[i] << "  ";
            }
        }

        else
        {
            cout << "   ";
            for (int i = 0; i < cantidadVertices(); i++) {
                cout << nodos[i] << " ";
            }
        }

        cout << endl << "-------------------" << endl;

        cout << "Matriz de caminos:" << endl;

        //Imprimir los nodos en la primera fila
        cout << "  ";
        for (int i = 0; i < cantidadVertices(); i++) {
            cout << nodos[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < cantidadVertices(); i++) {
            cout << nodos[i] << " ";
            for (int j = 0; j < cantidadVertices(); j++) {
                cout << caminos[i][j] << " ";
            }
            cout << endl;
        }

        cout << "-------------------" << endl;

        //Preguntar por el camino más corto entre dos nodos
        string nodo1, nodo2;
        cout << "Ingrese el nodo de inicio: ";
        cin >> nodo1;
        cout << "Ingrese el nodo de destino: ";
        cin >> nodo2;

        int indiceNodo1 = nodosMap[nodo1];
        int indiceNodo2 = nodosMap[nodo2];

        if (distancias[indiceNodo1][indiceNodo2] == INT_MAX) {
            cout << "No hay un camino entre " << nodo1 << " y " << nodo2 << endl;
        } else {
            cout << "El camino más corto entre " << nodo1 << " y " << nodo2 << " es: " << endl;
            cout << nodo1 << " ";
            while (indiceNodo1 != indiceNodo2) {
                indiceNodo1 = caminos[indiceNodo1][indiceNodo2];
                cout << nodos[indiceNodo1] << " ";
            }
            cout << endl;
        }
    }
