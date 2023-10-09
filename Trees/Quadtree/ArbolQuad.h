#ifndef ARBOLQUAD_H
#define ARBOLQUAD_H

#include "NodoQuad.h"
#include <queue>
#include <stack>
#include <cmath>

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

    // Métodos para buscar un punto cercano
    punto buscarCercano(punto val);
    void buscarCercanoRecursivo(NodoQuad* nodoActual, punto val, double& distanciaMinima, punto& puntoCercano);
    double distancia(punto p1, punto p2);

private:
    bool insertarRecursivo(punto val, NodoQuad* nodoActual);
    void preOrdenRecursivo(NodoQuad* nodo);
    void inOrdenRecursivo(NodoQuad* nodo);
    void posOrdenRecursivo(NodoQuad* nodo);

    void imprimirArbolRecursivo(NodoQuad* nodo, const std::string& prefijo, const std::string& etiqueta);
};

#endif // ARBOLQUAD_H
