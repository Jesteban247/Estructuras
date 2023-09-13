#include "NodoBinario.h"

template <class T>
NodoBinario<T>::NodoBinario()
{
    hijoIzq = nullptr;
    hijoDer = nullptr;
}

template <class T>
NodoBinario<T>::~NodoBinario()
{

}

template <class T>
T& NodoBinario<T>::obtenerDato()
{
    return dato;
}

template <class T>
void NodoBinario<T>::fijarDato(T& dato)
{
    this->dato = dato;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoIzq()
{
    return hijoIzq;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoDer()
{
    return hijoDer;
}

template <class T>
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T>* nodo)
{
    hijoIzq = nodo;
}

template <class T>
void NodoBinario<T>::fijarHijoDer(NodoBinario<T>* nodo)
{
    hijoDer = nodo;
}

