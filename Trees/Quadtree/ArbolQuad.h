#ifndef ARBOLQUAD_H
#define ARBOLQUAD_H

#include "NodoQuad.h"
#include <queue>

class ArbolQuad {
protected:
    NodoQuad* raiz;

public:
    ArbolQuad();
    ArbolQuad(punto val);
    ~ArbolQuad();
    punto datoRaiz();
    NodoQuad* obtenerRaiz();
    void fijarRaiz(NodoQuad* n_raiz);
    bool esVacio();
    bool insertar(punto val);
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();

    void imprimirArbol();

private:
    bool insertarRecursivo(punto val, NodoQuad* nodoActual);
    void preOrdenRecursivo(NodoQuad* nodo);
    void inOrdenRecursivo(NodoQuad* nodo);
    void posOrdenRecursivo(NodoQuad* nodo);

    void imprimirArbolRecursivo(NodoQuad* nodo, const std::string& prefijo, const std::string& etiqueta);
};

#endif // ARBOLQUAD_H
