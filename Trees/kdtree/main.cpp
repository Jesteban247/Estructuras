#include <iostream>
#include "ArbolKD.h"


using namespace std;

int main() {
    ArbolKD arbol;


    // Insertra los siguientes valores: (35,40) (50,10) (60,75) (80,65) (85,15) (5,45) (25,35) (90,5)
    arbol.insertar({35, 40});
    arbol.insertar({50, 10});
    arbol.insertar({60, 75});
    arbol.insertar({80, 65});
    arbol.insertar({85, 15});
    arbol.insertar({5, 45});
    arbol.insertar({25, 35});
    arbol.insertar({90, 5});

    // Realizamos recorridos en el árbol
    std::cout << "Recorrido en Preorden: ";
    arbol.preOrden(arbol.obtenerRaiz());
    std::cout << std::endl;

    std::cout << "Recorrido en Inorden: ";
    arbol.inOrden(arbol.obtenerRaiz());
    std::cout << std::endl;

    std::cout << "Recorrido en Posorden: ";
    arbol.posOrden(arbol.obtenerRaiz());
    std::cout << std::endl;

    std::cout << "Recorrido en Nivel: ";
    arbol.nivelOrden();
    std::cout << std::endl;

    // Buscamos el valor (60,75)
    if (arbol.buscarExacto({0, 90})) {
        std::cout << "El valor (10,10) se encuentra en el árbol" << std::endl;
    } else {
        std::cout << "El valor (10,10) no se encuentra en el árbol" << std::endl;
        std::cout << "El valor más cercano es: " << arbol.buscarCercano({0,90}) << std::endl;
    }

    return 0;
}
