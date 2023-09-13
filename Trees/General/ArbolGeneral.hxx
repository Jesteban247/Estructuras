#include "ArbolGeneral.h"

template <class T>
ArbolGeneral<T>::ArbolGeneral() 
{
    raiz = nullptr;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T& val) 
{
    NodoGeneral<T>* nodo = new NodoGeneral<T>;
    nodo->fijarDato(val);
    raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() 
{
    delete raiz;
    raiz = NULL;
}

template  <class T>
bool ArbolGeneral<T>::esVacio() 
{
    return raiz == nullptr;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() 
{
    return raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nodo) 
{
    raiz = nodo;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::buscarNodo(NodoGeneral<T>* nodo, T& valor) 
{
    if (nodo == nullptr) {
        return nullptr; // No se encontró el valor
    }

    if (nodo->obtenerDato() == valor) {
        return nodo; // Se encontró el nodo con el valor dado
    }

    // Recorre la lista de descendientes del nodo actual para buscar el valor
    for (auto it = nodo->obtenerDesc()->begin(); it != nodo->obtenerDesc()->end(); ++it) 
    {
        NodoGeneral<T>* nodoEncontrado = buscarNodo(*it, valor);
        if (nodoEncontrado != nullptr) {
            return nodoEncontrado; // Se encontró el valor 
        }
    }

    return nullptr; // No se encontró el valor 
}

template <class T>
bool ArbolGeneral<T>::insertar(T& padre, T& val)
{
    NodoGeneral<T>* nodoPadre = buscarNodo(raiz, padre);

    if (nodoPadre == nullptr) {
        return false;
    }

    nodoPadre->adicionarDesc(val);

    return true;
}

template <class T>
void ArbolGeneral<T>::mostrarHijos(T& val) 
{
    // Busca el nodo padre en el árbol
    NodoGeneral<T>* nodoPadre = buscarNodo(raiz, val);

    // Si el nodo padre no se encontró, no se puede insertar
    if (nodoPadre == nullptr) {
        cout << "No se encontro el nodo" << endl;
        return;
    }

    cout << "Los hijos de " << val << " son: " << endl;
    nodoPadre->imprimir_desc();
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::buscarNodo_padre(NodoGeneral<T>* nodo, T& valor) 
{
    if (nodo == nullptr || nodo->obtenerDesc()->empty()) {
        return nullptr; // No se encontró el valor o el nodo no tiene descendientes
    }

    for (auto it = nodo->obtenerDesc()->begin(); it != nodo->obtenerDesc()->end(); ++it) 
    {
        if ((*it)->obtenerDato() == valor) {
            return nodo; // Se encontró el nodo padre del valor dado
        }

        NodoGeneral<T>* nodoEncontrado = buscarNodo_padre(*it, valor);
        if (nodoEncontrado != nullptr) {
            return nodoEncontrado; // Se encontró el valor en un descendiente
        }
    }

    return nullptr; // No se encontró el valor 
}

template <class T>
bool ArbolGeneral<T>::eliminar(T& valor) 
{
    // Busca el nodo a eliminar
    NodoGeneral<T>* nodoEliminar = buscarNodo(raiz, valor);

    // Si el nodo a eliminar no se encontró, no se puede eliminar
    if (nodoEliminar == nullptr) {
        return false;
    }

    // Busca el nodo padre del valor a eliminar
    NodoGeneral<T>* nodoPadre = buscarNodo_padre(raiz, valor);

    // Si el nodo padre no se encontró, no se puede eliminar
    if (nodoPadre == nullptr) {
        return false;
    }

    cout << "El nodo padre de " << valor << " es " << nodoPadre->obtenerDato() << endl;

    // Elimina el nodo
    nodoPadre->eliminarDesc(valor);

    return true;
}

template <class T>
bool ArbolGeneral<T>::buscar(T& val) 
{
    NodoGeneral<T>* nodo = buscarNodo(raiz, val);

    if (nodo == nullptr) 
    {
        return false;
    }

    return true;
}


template <class T>
int ArbolGeneral<T>::altura(NodoGeneral<T>* nodo) 
{
    if (nodo == nullptr) {
        return -1; // Árbol vacío
    }

    if (nodo->obtenerDesc()->empty()) {
        return 0; // Árbol con solo raíz
    }

    int maxAltura = 0;

    // Recorre la lista de descendientes del nodo actual para encontrar la altura máxima
    for (auto it = nodo->obtenerDesc()->begin(); it != nodo->obtenerDesc()->end(); ++it) 
    {
        int alturaActual = altura(*it);
        if (alturaActual > maxAltura) {
            maxAltura = alturaActual;
        }
    }

    // La altura del nodo actual es la altura máxima encontrada más 1
    return maxAltura + 1;
}


template <class T>
int ArbolGeneral<T>::calcularAltura() 
{
    return altura(raiz);
}


template <class T>
unsigned int ArbolGeneral<T>::tamano(NodoGeneral<T>* nodo) 
{
    if (nodo == nullptr) {
        return 0; // Árbol vacío
    }

    unsigned int tamanoArbol = 1; // Comenzamos con 1 para contar el nodo actual

    // Recorre la lista de descendientes del nodo actual y suma sus tamaños
    for (auto it = nodo->obtenerDesc()->begin(); it != nodo->obtenerDesc()->end(); ++it) 
    {
        tamanoArbol += tamano(*it);
    }

    return tamanoArbol;
}

template <class T>
unsigned int ArbolGeneral<T>::calcularTamano() 
{
    return tamano(raiz);
}

template <class T>
void ArbolGeneral<T>::PreOrden(NodoGeneral<T>* nodo) 
{
    if (nodo != nullptr) 
    {
        cout << nodo->obtenerDato() << " "; // Visitar el nodo actual
        for (auto it = nodo->obtenerDesc()->begin(); it != nodo->obtenerDesc()->end(); ++it) 
        {
            PreOrden(*it); // Llamar a preOrden para los descendientes
        }
    }
}

template <class T>
void ArbolGeneral<T>::PreOrdenRecorrido() 
{
    PreOrden(raiz);
    cout << endl;
}

template <class T>
void ArbolGeneral<T>::PostOrden(NodoGeneral<T>* nodo) 
{
    if (nodo != nullptr) 
    {
        for (auto it = nodo->obtenerDesc()->begin(); it != nodo->obtenerDesc()->end(); ++it) 
        {
            PostOrden(*it); // Llamar a postOrden para los descendientes
        }
        cout << nodo->obtenerDato() << " "; // Visitar el nodo actual
    }
}

template <class T>
void ArbolGeneral<T>::PostOrdenRecorrido() 
{
    PostOrden(raiz);
    cout << endl;
}

template <class T>
void ArbolGeneral<T>::NivelOrden() 
{
    if (raiz == nullptr) {
        return; // Árbol vacío
    }

    queue<NodoGeneral<T>*> cola;
    cola.push(raiz);

    while (!cola.empty()) 
    {
        NodoGeneral<T>* nodoActual = cola.front();
        cola.pop();

        cout << nodoActual->obtenerDato() << " "; // Visitar el nodo actual

        for (auto it = nodoActual->obtenerDesc()->begin(); it != nodoActual->obtenerDesc()->end(); ++it) 
        {
            cola.push(*it); // Agregar descendientes a la cola
        }
    }

    cout << endl;
}
