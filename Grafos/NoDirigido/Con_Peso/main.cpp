#include "grafo.h"

int main() 
{
    GrafoNoDirigido<string> grafo;

    int opcion, peso;
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
        cout << "17. Algoritmo de Prim" << endl;
        cout << "18. Algoritmo de Dijkstra" << endl;
        cout << "19. Algoritmo de Kruskal" << endl;
        cout << "20. Algoritmo de Floyd-Warshall" << endl;
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
                cout << "Ingrese el peso de la arista: ";
                cin >> peso;
                grafo.agregarArista(origen, destino, peso);
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
              

                grafo.agregarArista("A","B",7);
                grafo.agregarArista("A","C",2);
                grafo.agregarArista("B","C",3);
                grafo.agregarArista("B","D",2);
                grafo.agregarArista("C","D",7);
                grafo.agregarArista("B","E",4);
                grafo.agregarArista("C","F",6);
                grafo.agregarArista("D","E",1);
                grafo.agregarArista("D","F",3);
                grafo.agregarArista("E","F",5);
                
                break;
            case 17:
                cout << "Ingrese el nodo de inicio para el MST (Prim): ";
                cin >> nodo;
                grafo.Prim(nodo);
                break;
            case 18:
                cout << "Ingrese el nodo de inicio para el MST (Dijkstra): ";
                cin >> nodo;
                grafo.Dijkstra(nodo);
                break;
            case 19:
                grafo.Kruskal();
                break;
            case 20:
                grafo.FloydWarshall();
                break;
            case 0:
                break;
            default:
                cout << "Opción no válida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
