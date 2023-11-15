#include <iostream>
using namespace std;

#include "Clase.h"
#include "Grafo.h"


int main() 
{
    Grafo<Clase> miGrafo;

    // Crear nodos
    Clase nodo0(0);
    Clase nodo1(1);
    Clase nodo2(2);
    Clase nodo3(3);
    Clase nodo4(4);
    Clase nodo5(5);
    Clase nodo6(6);
    Clase nodo7(7);
    Clase nodo8(8);
    Clase nodo9(9);


    // Agregar nodos
    miGrafo.agregarNodo(nodo0);
    miGrafo.agregarNodo(nodo1);
    miGrafo.agregarNodo(nodo2);
    miGrafo.agregarNodo(nodo3);
    miGrafo.agregarNodo(nodo4);

    // Agregar aristas
    miGrafo.agregarArista(nodo0, nodo1, 10);
    miGrafo.agregarArista(nodo0, nodo2, 5);
    miGrafo.agregarArista(nodo1, nodo3, 1);
    miGrafo.agregarArista(nodo1, nodo2, 2);
    miGrafo.agregarArista(nodo2, nodo3, 9);
    miGrafo.agregarArista(nodo2, nodo4, 2);
    miGrafo.agregarArista(nodo2, nodo1, 3);
    miGrafo.agregarArista(nodo3, nodo4, 4);
    miGrafo.agregarArista(nodo4, nodo3, 6);
    miGrafo.agregarArista(nodo4, nodo0, 7);


    // Eliminar arista
    //miGrafo.eliminarArista(nodo1, nodo2);

    // Eliminar nodo
    //miGrafo.eliminarVertice(nodo3);

    // Imprimir matriz de adyacencia
    miGrafo.imprimirMatrizAdyacencia();

    cout << endl;

    // Prim
    /*
    multimap<int, int> arbol = miGrafo.Prim(nodo1);
    if (arbol.size() > 0)
    {
        cout << "Arbol de expansion minima:" << endl;
        for (auto& arista : arbol)
        {
            cout << arista.first << " - " << arista.second << endl;
        }
    }
    */

    // Dijkstra
    /*
    multimap<int, int> distancias = miGrafo.Dijkstra(nodo0);
    if (distancias.size() > 0)
    {
        cout << "Distancias minimas:" << endl;
        for (auto& distancia : distancias)
        {
            cout << distancia.first << " - " << distancia.second << endl;
        }
    }
    */
    
    // Floyd-Warshall
    /*
    vector<int> distancias = miGrafo.FloydWarshall(nodo0, nodo3);
    if (distancias.size() > 0)
    {
        cout << "Distancias minimas:" << endl;
        for (auto& distancia : distancias)
        {
            cout << distancia << " ";
        }
    }
    cout << endl;
    */




    return 0;
}
