#include <iostream>
#include "ArbolQuad.h"
using namespace std;

int main() {
    ArbolQuad quadtree;

    //Define e inserta los siguientes puntos (32,25) (30,35) (35,30) (37,12) (25,45) (45,32) (5,15) (40,42)
    punto p1 = {32, 25};
    punto p2 = {30, 35};
    punto p3 = {35, 30};
    punto p4 = {37, 12};
    punto p5 = {25, 45};
    punto p6 = {45, 32};
    punto p7 = {5, 15};
    punto p8 = {40, 42};

    quadtree.insertar(p1);
    quadtree.insertar(p2);
    quadtree.insertar(p3);
    quadtree.insertar(p4);
    quadtree.insertar(p5);
    quadtree.insertar(p6);
    quadtree.insertar(p7);
    quadtree.insertar(p8);

    std::cout << "Recorrido Preorden: ";
    quadtree.preOrden();
    std::cout << std::endl;

    std::cout << "Recorrido Inorden: ";
    quadtree.inOrden();
    std::cout << std::endl;

    std::cout << "Recorrido Posorden: ";
    quadtree.posOrden();
    std::cout << std::endl;

    std::cout << "Recorrido por Niveles: ";
    quadtree.nivelOrden();
    std::cout << std::endl;

    std::cout << "Árbol Quadtree:" << std::endl;
    quadtree.imprimirArbol();

    cout << "-------------------" << endl;
    cout << "Busqueda de puntos Exacta" << endl;
    punto p9 = {32, 30};
    cout << "Busqueda de (32,25): " << quadtree.buscarExacto(p1) << endl;
    cout << "-------------------" << endl;
    cout << "Busqueda de puntos Cercanos" << endl;
    cout << "Busqueda de (32,30): " << quadtree.buscarCercano(p9) << endl;



    return 0;
}
