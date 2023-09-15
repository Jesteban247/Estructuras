#include "NodoBinario.h"

// Constructor de NodoBinario
template <class T>
NodoBinario<T>::NodoBinario()
{
    hijoIzq = nullptr;
    hijoDer = nullptr;
}

// Destructor de NodoBinario (vacío ya que no se necesita realizar ninguna acción especial en la destrucción)
template <class T>
NodoBinario<T>::~NodoBinario()
{

}

// Método para obtener el dato almacenado en el nodo
template <class T>
T& NodoBinario<T>::obtenerDato()
{
    return dato;
}

// Método para establecer el dato en el nodo
template <class T>
void NodoBinario<T>::fijarDato(T& dato)
{
    this->dato = dato;
}

// Método para obtener el puntero al hijo izquierdo del nodo
template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoIzq()
{
    return hijoIzq;
}

// Método para obtener el puntero al hijo derecho del nodo
template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoDer()
{
    return hijoDer;
}

// Método para establecer el puntero al hijo izquierdo del nodo
template <class T>
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T>* nodo)
{
    hijoIzq = nodo;
}

// Método para establecer el puntero al hijo derecho del nodo
template <class T>
void NodoBinario<T>::fijarHijoDer(NodoBinario<T>* nodo)
{
    hijoDer = nodo;
}
