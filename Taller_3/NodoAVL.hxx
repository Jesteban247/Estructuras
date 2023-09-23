#include "NodoAVL.h"

template <class T>
NodoAVL<T>::NodoAVL()
{
    hijoIzq = nullptr;
    hijoDer = nullptr;
    altura = 1; // Inicialmente, la altura es 1 para el nodo recién creado
}

template <class T>
NodoAVL<T>::~NodoAVL()
{

}

template <class T>
const T& NodoAVL<T>::obtenerDato() const
{
    return dato;
}

template <class T>
void NodoAVL<T>::fijarDato(const T& dato)
{
    this->dato = dato;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::obtenerHijoIzq()
{
    return hijoIzq;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::obtenerHijoDer()
{
    return hijoDer;
}

template <class T>
void NodoAVL<T>::fijarHijoIzq(NodoAVL<T>* nodo)
{
    hijoIzq = nodo;
}

template <class T>
void NodoAVL<T>::fijarHijoDer(NodoAVL<T>* nodo)
{
    hijoDer = nodo;
}

template <class T>
int NodoAVL<T>::obtenerAltura() const {
    return altura;
}

template <class T>
void NodoAVL<T>::actualizarAltura() {
    int alturaIzq = (hijoIzq != nullptr) ? hijoIzq->obtenerAltura() : 0;
    int alturaDer = (hijoDer != nullptr) ? hijoDer->obtenerAltura() : 0;
    altura = 1 + max(alturaIzq, alturaDer);
}

