#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
class GrafoNoDirigido {
public:
    void agregarNodo(const T& nodo) {
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

    void agregarArista(const T& origen, const T& destino) {
        if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
            int indiceOrigen = nodosMap[origen];
            int indiceDestino = nodosMap[destino];
            matrizAdyacencia[indiceOrigen][indiceDestino] = 1;
            matrizAdyacencia[indiceDestino][indiceOrigen] = 1; // El grafo es no dirigido, así que agregamos la arista en ambas direcciones
        }
    }

    int cantidadVertices() {
        return nodos.size();
    }

    int cantidadAristas() {
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

    bool buscarVertice(const T& nodo) {
        return nodosMap.find(nodo) != nodosMap.end();
    }

    bool buscarArista(const T& origen, const T& destino) {
        if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
            int indiceOrigen = nodosMap[origen];
            int indiceDestino = nodosMap[destino];
            return matrizAdyacencia[indiceOrigen][indiceDestino] == 1;
        }
        return false;
    }

    void eliminarVertice(const T& nodo) {
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

    void eliminarArista(const T& origen, const T& destino) {
        if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end()) {
            int indiceOrigen = nodosMap[origen];
            int indiceDestino = nodosMap[destino];
            matrizAdyacencia[indiceOrigen][indiceDestino] = 0;
            matrizAdyacencia[indiceDestino][indiceOrigen] = 0;
        }
    }

    void imprimirMatrizAdyacencia() {
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

    void imprimirGrafo() {
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
    void dfs(int nodoActual, vector<bool>& visitado) {
        visitado[nodoActual] = true;
        cout << nodos[nodoActual] << " ";

        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[nodoActual][i] == 1 && !visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

    // Función para realizar el recorrido en profundidad (DFS) desde un nodo dado
    void recorridoEnProfundidad(const T& inicio) {
        if (nodosMap.find(inicio) != nodosMap.end()) {
            int indiceInicio = nodosMap[inicio];
            vector<bool> visitado(nodos.size(), false);
            dfs(indiceInicio, visitado);
        }
    }

    // Función para realizar el recorrido en anchura (BFS) desde un nodo dado
    void recorridoEnAnchura(const T& inicio) {
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
    void recorridoPlano() {
        vector<bool> visitado(nodos.size(), false);
        for (int i = 0; i < nodos.size(); i++) {
            if (!visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

    // Caminos de Hamilton

    // Función auxiliar para el algoritmo de Hamilton
    bool encontrarCaminoHamiltonRecursivo(vector<int>& camino, vector<bool>& visitado, int nodoActual) {
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
    bool encontrarCaminoHamilton() {
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
    bool encontrarCicloHamiltonRecursivo(vector<int>& ciclo, vector<bool>& visitado, int nodoActual, int nodoInicial) {
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
    bool encontrarCicloHamilton() {
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

    int gradoVertice(int indiceNodo) {
        int grado = 0;
        for (int i = 0; i < nodos.size(); i++) {
            if (matrizAdyacencia[indiceNodo][i] == 1) {
                grado++;
            }
        }
        return grado;
    }

    // Función auxiliar para el algoritmo de Euler
    bool encontrarCaminoEulerRecursivo(vector<int>& camino, vector<vector<int>>& copiaMatrizAdyacencia, int nodoActual) {
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
    bool encontrarCaminoEuler() {
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
    bool encontrarCicloEuler() {
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


private:
    map<T, int> nodosMap; // Mapeo de nodos a índices
    vector<T> nodos;
    vector<vector<int>> matrizAdyacencia;
};


int main() {
    GrafoNoDirigido<string> grafo;

    int opcion;
    string nodo, origen, destino;

    do {
        cout << "Menú:" << endl;
        cout << "1. Agregar nodo" << endl;
        cout << "2. Agregar arista" << endl;
        cout << "3. Imprimir matriz de adyacencia" << endl;
        cout << "4. Imprimir grafo" << endl;
        cout << "5. Cantidad de vértices" << endl;
        cout << "6. Cantidad de aristas" << endl;
        cout << "7. Buscar Vertice" << endl;
        cout << "8. Buscar Arista" << endl;
        cout << "9. Eliminar Vertice" << endl;
        cout << "10. Eliminar Arista" << endl;
        cout << "11. Recorrido en profundidad" << endl;
        cout << "12. Recorrido en anchura" << endl;
        cout << "13. Recorrido plano" << endl;
        cout << "14. Caminos de Hamilton" << endl;
        cout << "15. Caminos de Euler" << endl;
        cout << "16. Prueba" << endl;
        cout << "0. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre del nodo: ";
                cin >> nodo;
                grafo.agregarNodo(nodo);
                break;
            case 2:
                cout << "Ingrese el origen de la arista: ";
                cin >> origen;
                cout << "Ingrese el destino de la arista: ";
                cin >> destino;
                grafo.agregarArista(origen, destino);
                break;
            case 3:
                cout << "Matriz de adyacencia:" << endl;
                grafo.imprimirMatrizAdyacencia();
                break;
            case 4:
                cout << "Grafo:" << endl;
                grafo.imprimirGrafo();
                break;
            case 5:
                cout << "Cantidad de vértices: " << grafo.cantidadVertices() << endl;
                break;
            case 6:
                cout << "Cantidad de aristas: " << grafo.cantidadAristas() << endl;
                break;
            case 7:
                cout << "Ingrese el nodo a buscar: ";
                cin >> nodo;
                if (grafo.buscarVertice(nodo)) {
                    cout << "El nodo " << nodo << " existe en el grafo." << endl;
                } else {
                    cout << "El nodo " << nodo << " no existe en el grafo." << endl;
                }
                break;
            case 8:
                cout << "Ingrese el origen de la arista: ";
                cin >> origen;
                cout << "Ingrese el destino de la arista: ";
                cin >> destino;
                if (grafo.buscarArista(origen, destino)) {
                    cout << "La arista entre " << origen << " y " << destino << " existe en el grafo." << endl;
                } else {
                    cout << "La arista entre " << origen << " y " << destino << " no existe en el grafo." << endl;
                }
                break;
            case 9:
                cout << "Ingrese el nodo a eliminar: ";
                cin >> nodo;
                grafo.eliminarVertice(nodo);
                cout << "El nodo " << nodo << " ha sido eliminado." << endl;
                break;
            case 10:
                cout << "Ingrese el origen de la arista a eliminar: ";
                cin >> origen;
                cout << "Ingrese el destino de la arista a eliminar: ";
                cin >> destino;
                grafo.eliminarArista(origen, destino);
                cout << "La arista entre " << origen << " y " << destino << " ha sido eliminada." << endl;
                break;
            case 11:
                cout << "Ingrese el nodo de inicio: ";
                cin >> nodo;
                grafo.recorridoEnProfundidad(nodo);
                cout << endl;
                break;
            case 12:
                cout << "Ingrese el nodo de inicio: ";
                cin >> nodo;
                grafo.recorridoEnAnchura(nodo);
                cout << endl;
                break;
            case 13:
                grafo.recorridoPlano();
                cout << endl;
                break;
            
            case 14:
                grafo.encontrarCaminoHamilton();
                grafo.encontrarCicloHamilton();
                break;

            case 15:
                grafo.encontrarCaminoEuler();
                grafo.encontrarCicloEuler();
                break;

            case 16:
                grafo.agregarNodo("A");
                grafo.agregarNodo("B");
                grafo.agregarNodo("C");
                grafo.agregarNodo("D");
                grafo.agregarNodo("E");
                grafo.agregarNodo("F");

                grafo.agregarArista("A","B");
                grafo.agregarArista("A","C");
                grafo.agregarArista("A","D");
                grafo.agregarArista("B","D");
                grafo.agregarArista("B","C");
                grafo.agregarArista("C","E");
                grafo.agregarArista("C","F");
                grafo.agregarArista("D","E");
                grafo.agregarArista("D","F");

                break;
            case 0:
                break;
            default:
                cout << "Opción no válida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
