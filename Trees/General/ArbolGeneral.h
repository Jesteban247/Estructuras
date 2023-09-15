#ifndef ARBOLGENERAL_H
#define ARBOLGENERAL_H

#include "NodoGeneral.h"
#include <queue>

template <class T>
class ArbolGeneral 
{
protected:
    NodoGeneral<T> *raiz;  // Puntero a la raíz del árbol

public:
    // Constructor por defecto
    ArbolGeneral();

    // Constructor que crea un árbol con un valor específico en la raíz
    ArbolGeneral(T& val);

    // Destructor
    ~ArbolGeneral();

    // Métodos para verificar y obtener información

    //  Verifica si el árbol está vacío.
    bool esVacio();

    //  Obtiene el puntero al nodo raíz del árbol.
    NodoGeneral<T>* obtenerRaiz();

    //  Establece el puntero al nodo raíz del árbol.
    void fijarRaiz(NodoGeneral<T>* nodo);

    // Método para buscar un nodo con un valor específico a partir de un nodo dado
    NodoGeneral<T>* buscarNodo(NodoGeneral<T>* nodo, T& valor);

    // Método para insertar un nuevo nodo con un valor específico como hijo de otro nodo
    bool insertar(T& padre, T& val);

    // Método para mostrar los hijos de un nodo con un valor específico
    void mostrarHijos(T& val);

    // Método para buscar el nodo padre de un nodo con un valor específico
    NodoGeneral<T>* buscarNodo_padre(NodoGeneral<T>* nodo, T& valor);

    // Método para eliminar un nodo con un valor específico y sus descendientes
    bool eliminar(T& val);

    // Método para buscar un valor específico en el árbol
    bool buscar(T& val);

    // Método para calcular la altura de un subárbol a partir de un nodo dado
    int altura(NodoGeneral<T>* nodo);

    // Método para calcular la altura total del árbol
    int calcularAltura();

    // Método para calcular el tamaño de un subárbol a partir de un nodo dado
    unsigned int tamano(NodoGeneral<T>* nodo);

    // Método para calcular el tamaño total (número de nodos) del árbol
    unsigned int calcularTamano();

    // Método para realizar un recorrido en preorden a partir de un nodo dado
    void PreOrden(NodoGeneral<T>* nodo);

    // Método para realizar un recorrido en preorden comenzando desde la raíz
    void PreOrdenRecorrido();

    // Método para realizar un recorrido en postorden a partir de un nodo dado
    void PostOrden(NodoGeneral<T>* nodo);

    // Método para realizar un recorrido en postorden comenzando desde la raíz
    void PostOrdenRecorrido();

    // Método para realizar un recorrido por niveles comenzando desde la raíz
    void NivelOrden();
};

#include "ArbolGeneral.hxx"

#endif
