#ifndef ARBOLGENERAL_H
#define ARBOLGENERAL_H

#include "NodoGeneral.h"
#include <queue>

template <class T>
class ArbolGeneral 
{
    protected:
    NodoGeneral<T> *raiz;

    public:
    ArbolGeneral();
    ArbolGeneral(T& val);
    ~ArbolGeneral();
    bool esVacio();
    NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nodo);

    NodoGeneral<T>* buscarNodo(NodoGeneral<T>* nodo, T& valor);
    bool insertar(T& padre, T& val); 

    void mostrarHijos(T& val);

    NodoGeneral<T>* buscarNodo_padre(NodoGeneral<T>* nodo, T& valor);
    bool eliminar(T& val);

    bool buscar(T& val);

    int altura(NodoGeneral<T>* nodo);
    int calcularAltura();

    unsigned int tamano(NodoGeneral<T>* nodo);
    unsigned int calcularTamano();

    void PreOrden(NodoGeneral<T>* nodo);
    void PreOrdenRecorrido();

    void PostOrden(NodoGeneral<T>* nodo);
    void PostOrdenRecorrido();

    void NivelOrden();
   
};

#include "ArbolGeneral.hxx"

#endif
