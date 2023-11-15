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

    // Agregar nodos
    miGrafo.agregarNodo(nodo0);
    miGrafo.agregarNodo(nodo1);
    miGrafo.agregarNodo(nodo2);
    miGrafo.agregarNodo(nodo3);
    miGrafo.agregarNodo(nodo4);
    miGrafo.agregarNodo(nodo5);
    miGrafo.agregarNodo(nodo6);
    miGrafo.agregarNodo(nodo7);
    miGrafo.agregarNodo(nodo8);

    // Agregar aristas
    miGrafo.agregarArista(nodo0, nodo1, 4);
    miGrafo.agregarArista(nodo1, nodo2, 8);
    miGrafo.agregarArista(nodo2, nodo3, 7);
    miGrafo.agregarArista(nodo3, nodo4, 9);
    miGrafo.agregarArista(nodo4, nodo5, 10);
    miGrafo.agregarArista(nodo5, nodo6, 2);
    miGrafo.agregarArista(nodo6, nodo7, 1);
    miGrafo.agregarArista(nodo7, nodo0, 8);
    miGrafo.agregarArista(nodo1, nodo7, 11);
    miGrafo.agregarArista(nodo7, nodo8, 7);
    miGrafo.agregarArista(nodo8, nodo2, 2);
    miGrafo.agregarArista(nodo8, nodo6, 6);
    miGrafo.agregarArista(nodo2, nodo5, 4);
    miGrafo.agregarArista(nodo3, nodo5, 14);


    // Eliminar arista
    //miGrafo.eliminarArista(nodo1, nodo2);

    // Eliminar nodo
    //miGrafo.eliminarVertice(nodo3);

    // Imprimir matriz de adyacencia
    miGrafo.imprimirMatrizAdyacencia();

    cout << endl;

    // Prim
    /*
    multimap<int, int> arbol = miGrafo.Prim(nodo0);
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
    vector<int> distancias = miGrafo.FloydWarshall(nodo0, nodo8);
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
