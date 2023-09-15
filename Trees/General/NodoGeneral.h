#ifndef NODOGENERAL_H
#define NODOGENERAL_H

#include <iostream>
#include <list>
using namespace std;

template <class T>
class NodoGeneral {
protected:
    T dato; // El dato almacenado en el nodo
    list<NodoGeneral<T>*> desc; // Lista de descendientes del nodo

public:
    // Constructor por defecto
    NodoGeneral();

    // Destructor
    ~NodoGeneral();

    // Método para obtener el dato almacenado en el nodo
    T& obtenerDato();

    // Método para establecer el dato en el nodo
    void fijarDato(T& val);

    // Método para limpiar la lista de descendientes del nodo
    void limpiarLista();

    // Método para agregar un nuevo nodo como descendiente de este nodo
    bool adicionarDesc(T& val);

    // Método para eliminar un nodo descendiente con un valor específico
    bool eliminarDesc(T& val);

    // Método para obtener un puntero a la lista de descendientes
    list<NodoGeneral<T>*>* obtenerDesc();

    // Método para imprimir los descendientes del nodo
    void imprimir_desc();
};

#include "NodoGeneral.hxx"

#endif
