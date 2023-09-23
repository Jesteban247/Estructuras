#ifndef NodoAVL_H
#define NodoAVL_H

#include <iostream>
using namespace std;

template <class T>
class NodoAVL
{
    protected:
    T dato;
    NodoAVL<T> *hijoIzq;
    NodoAVL<T> *hijoDer;

    int altura; // Altura del subárbol con raíz en este nodo

    public:
    NodoAVL();
    ~NodoAVL();
    void fijarDato(const T& dato);
    const T& obtenerDato() const;
    NodoAVL<T>* obtenerHijoIzq();
    NodoAVL<T>* obtenerHijoDer();
    void fijarHijoIzq(NodoAVL<T>* nodo);
    void fijarHijoDer(NodoAVL<T>* nodo);

    int obtenerAltura() const;
    void actualizarAltura();

};

#include "NodoAVL.hxx"

#endif
