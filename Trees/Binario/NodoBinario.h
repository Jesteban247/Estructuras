#ifndef NODOBINARIO_H
#define NODOBINARIO_H

#include <iostream>
using namespace std;

template <class T>
class NodoBinario
{
protected:
    T dato;                      // Dato almacenado en el nodo
    NodoBinario<T> *hijoIzq;    // Puntero al hijo izquierdo
    NodoBinario<T> *hijoDer;    // Puntero al hijo derecho

public:
    // Constructor
    NodoBinario();

    // Destructor
    ~NodoBinario();

    // Métodos para establecer y obtener el dato del nodo

    //  Establece el valor de dato en el nodo.
    void fijarDato(T& dato);

    //  Obtiene el valor almacenado en el nodo.
    T& obtenerDato();

    // Métodos para establecer y obtener los hijos del nodo

    //  Obtiene el puntero al hijo izquierdo del nodo.
    NodoBinario<T>* obtenerHijoIzq();

    //  Obtiene el puntero al hijo derecho del nodo.
    NodoBinario<T>* obtenerHijoDer();

    //  Establece el puntero al hijo izquierdo del nodo.
    void fijarHijoIzq(NodoBinario<T>* nodo);

    //  Establece el puntero al hijo derecho del nodo.
    void fijarHijoDer(NodoBinario<T>* nodo);
};

#include "NodoBinario.hxx"

#endif
