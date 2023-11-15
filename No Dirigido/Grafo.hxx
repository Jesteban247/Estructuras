#include "Grafo.h"

template <class T>
void Grafo<T>::agregarNodo(const T& nodo) {
    if (nodosMap.find(nodo) == nodosMap.end()) {
        int indice = nodos.size();
        nodosMap[nodo] = indice;
        nodos.push_back(nodo);

        for (auto& fila : matrizAdyacencia) {
            fila.push_back(0);
        }
        matrizAdyacencia.push_back(vector<int>(nodos.size(), 0));
    }
}

template <class T>
void Grafo<T>::eliminarVertice(const T& nodo) {
    if (nodosMap.find(nodo) != nodosMap.end()) {
        int indice = nodosMap[nodo];
        nodosMap.erase(nodo);
        nodos.erase(nodos.begin() + indice);
        matrizAdyacencia.erase(matrizAdyacencia.begin() + indice);

        for (auto& fila : matrizAdyacencia) {
            fila.erase(fila.begin() + indice);
        }
    }
}

template <class T>
void Grafo<T>::agregarArista(const T& origen, const T& destino, int peso) {
    int indiceOrigen = nodosMap[origen];
    int indiceDestino = nodosMap[destino];
    matrizAdyacencia[indiceOrigen][indiceDestino] = peso;
    matrizAdyacencia[indiceDestino][indiceOrigen] = peso; // Agrega esta línea
}


template <class T>
void Grafo<T>::eliminarArista(const T& origen, const T& destino) {
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        matrizAdyacencia[indiceOrigen][indiceDestino] = 0;
        matrizAdyacencia[indiceDestino][indiceOrigen] = 0; // Agrega esta línea
    }
}


template <class T>
void Grafo<T>::imprimirMatrizAdyacencia() {
    cout << "   ";
    for (size_t i = 0; i < nodos.size(); i++) {
        cout << i << " ";
    }
    cout << endl;

    for (size_t i = 0; i < matrizAdyacencia.size(); i++) {
        cout << i  << " | ";
        for (size_t j = 0; j < matrizAdyacencia[i].size(); j++) {
            cout << matrizAdyacencia[i][j] << " ";
        }
        cout << endl;
    }
}

template <class T>
bool Grafo<T>::Conectado() {
    if (nodos.empty()) return false; // Si no hay nodos, el grafo no está conectado.

    vector<bool> visitado(nodos.size(), false);
    stack<int> pila;
    int nodoInicial = nodosMap.begin()->second; // Empezamos por el primer nodo.

    pila.push(nodoInicial);
    visitado[nodoInicial] = true;
    int nodosVisitados = 1; // Contamos el nodo inicial como visitado.

    while (!pila.empty()) {
        int nodoActual = pila.top();
        pila.pop();
        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i]) {
                pila.push(i);
                visitado[i] = true;
                nodosVisitados++;
            }
        }
    }

    return nodosVisitados == nodos.size(); // Si todos los nodos han sido visitados, el grafo está conectado.
}


template <class T>
multimap<int, int> Grafo<T>::Prim(const T& nodoInicio) 
{
    // Verifica si el nodoInicio está en el grafo
    if (nodosMap.find(nodoInicio) == nodosMap.end()) {
        cout << "Nodo de inicio no existe en el grafo." << endl;
        return multimap<int, int>();
    }

    // Verifica si el grafo está conectado
    if (!Conectado()) {
        cout << "El grafo no esta conectado." << endl;
        return multimap<int, int>();
    }

    int indiceInicio = nodosMap[nodoInicio];
    multimap<int, int> arbolRecubrimientoMinimo;
    vector<int> pesoMinimoHastaNodo(nodos.size(), INFINITO);
    vector<bool> nodoIncluido(nodos.size(), false);
    vector<int> padre(nodos.size(), -1);

    pesoMinimoHastaNodo[indiceInicio] = 0;
    padre[indiceInicio] = -1;

    for (int count = 0; count < nodos.size() - 1; count++) {
        int u = -1;
        int minPeso = INFINITO;
        for (int j = 0; j < nodos.size(); j++) {
            if (!nodoIncluido[j] && pesoMinimoHastaNodo[j] < minPeso) {
                minPeso = pesoMinimoHastaNodo[j];
                u = j;
            }
        }

        nodoIncluido[u] = true;

        for (int v = 0; v < nodos.size(); v++) {
            if (matrizAdyacencia[u][v] && !nodoIncluido[v] && matrizAdyacencia[u][v] < pesoMinimoHastaNodo[v]) {
                padre[v] = u;
                pesoMinimoHastaNodo[v] = matrizAdyacencia[u][v];
            }
        }
    }

    for (int i = 0; i < nodos.size(); i++) {
        if(padre[i] != -1) {
            arbolRecubrimientoMinimo.insert(pair<int, int>(padre[i], i));
        }
    }

    return arbolRecubrimientoMinimo;
}


template <class T>
multimap<int, int> Grafo<T>::Dijkstra(const T& origen) {
    // Encuentra el índice del nodo de origen.
    int indiceOrigen = nodosMap[origen];
    if (indiceOrigen < 0 || indiceOrigen >= nodos.size()) {
        cout << "El nodo de origen no existe" << endl;
        return multimap<int, int>(); // Retorna un mapa vacío si el nodo de origen no existe.
    }

    // Verificar si el grafo está conectado.
    if (!Conectado()) {
        cout << "El grafo no esta conectado" << endl;
        return multimap<int, int>(); // Retorna un mapa vacío si el grafo no está conectado.
    }

    // Inicialización de las estructuras de datos.
    vector<int> distancias(nodos.size(), INFINITO);
    vector<bool> visitado(nodos.size(), false);
    vector<int> padres(nodos.size(), -1);
    distancias[indiceOrigen] = 0;

    // La cola de prioridad tendrá pares de (distancia, indiceNodo).
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cola;
    cola.push(make_pair(0, indiceOrigen));

    while (!cola.empty()) {
        int indiceActual = cola.top().second;
        cola.pop();
        
        if (visitado[indiceActual]) continue; // Asegurar no procesar un nodo ya visitado.
        visitado[indiceActual] = true;

        // Revisar vecinos del nodo actual.
        for (int i = 0; i < nodos.size(); ++i) {
            if (matrizAdyacencia[indiceActual][i] != 0) { // Hay una arista.
                int pesoArista = matrizAdyacencia[indiceActual][i];
                if (distancias[indiceActual] + pesoArista < distancias[i]) {
                    padres[i] = indiceActual;
                    distancias[i] = distancias[indiceActual] + pesoArista;
                    cola.push(make_pair(distancias[i], i));
                }
            }
        }
    }

    // Construir el multimap con los caminos más cortos.
    multimap<int, int> caminosMasCortos;
    for (int i = 0; i < nodos.size(); ++i) {
        if (i != indiceOrigen && padres[i] != -1) { // Si hay camino hasta el nodo.
            caminosMasCortos.insert({padres[i], i});
        }
    }

    return caminosMasCortos;
}


template <class T>
vector<int> Grafo<T>::FloydWarshall(const T& origen, const T& destino) 
{
    // Verifica que ambos nodos existan en el grafo
    if (nodosMap.find(origen) == nodosMap.end() || nodosMap.find(destino) == nodosMap.end()) {
        cout << "Uno o ambos nodos no existen en el grafo." << endl;
        return vector<int>();
    }

    int n = nodos.size();
    vector<vector<int>> dist(n, vector<int>(n, INFINITO));
    vector<vector<int>> next(n, vector<int>(n, -1));

    // Inicialización de las matrices para Floyd-Warshall
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (int j = 0; j < n; j++) {
            if (matrizAdyacencia[i][j] != 0) {
                dist[i][j] = matrizAdyacencia[i][j];
                next[i][j] = j;
            }
        }
    }

    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INFINITO && dist[k][j] < INFINITO && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Reconstrucción del camino más corto
    vector<int> path;
    int u = nodosMap[origen];
    int v = nodosMap[destino];

    if (next[u][v] == -1) return path; // No hay camino

    path.push_back(u);
    while (u != v) {
        u = next[u][v];
        path.push_back(u);
    }

    return path; // Devuelve los índices de los nodos en la ruta más corta
}


