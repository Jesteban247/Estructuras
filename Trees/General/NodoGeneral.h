#ifndef NODOGENERAL_H
#define NODOGENERAL_H

#include <iostream>
#include <list>
using namespace std;

template <class T>
class NodoGeneral {
protected:
    T dato;
    list<NodoGeneral<T>*> desc;

public:
    NodoGeneral();
    ~NodoGeneral();
    T& obtenerDato();
    void fijarDato(T& val);
    void limpiarLista();
    bool adicionarDesc(T& val);
    bool eliminarDesc(T& val);

    list<NodoGeneral<T>*>* obtenerDesc();

    void imprimir_desc();

};

#include "NodoGeneral.hxx"

#endif
