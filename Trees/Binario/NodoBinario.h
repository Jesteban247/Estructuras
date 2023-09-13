#ifndef NODOBINARIO_H
#define NODOBINARIO_H

#include <iostream>
using namespace std;

template <class T>
class NodoBinario
{
    protected:
    T dato;
    NodoBinario<T> *hijoIzq;
    NodoBinario<T> *hijoDer;

    public:
    NodoBinario();
    ~NodoBinario();
    void fijarDato(T& dato);
    T& obtenerDato();
    NodoBinario<T>* obtenerHijoIzq();
    NodoBinario<T>* obtenerHijoDer();
    void fijarHijoIzq(NodoBinario<T>* nodo);
    void fijarHijoDer(NodoBinario<T>* nodo);
};

#include "NodoBinario.hxx"

#endif