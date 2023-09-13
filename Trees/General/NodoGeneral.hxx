#include "NodoGeneral.h"

template <class T>
NodoGeneral<T>::NodoGeneral() {}

template <class T>
NodoGeneral<T>::~NodoGeneral() 
{
    desc.clear();
}

template <class T>
T& NodoGeneral<T>::obtenerDato() 
{
    return dato;
}

template <class T>
void NodoGeneral<T>::fijarDato(T& val) 
{
    dato = val;
}

template <class T>
void NodoGeneral<T>::limpiarLista() 
{
    for (auto it = desc.begin(); it != desc.end(); ++it) 
    {
        delete *it;
    }
    desc.clear();
}

template <class T>
bool NodoGeneral<T>::adicionarDesc(T& val) 
{
    NodoGeneral<T>* nuevoNodo = new NodoGeneral<T>();
    nuevoNodo->fijarDato(val);
    desc.push_back(nuevoNodo);
    return true;
}

template <class T>
bool NodoGeneral<T>::eliminarDesc(T& val) 
{
    for (auto it = desc.begin(); it != desc.end(); ++it) 
    {
        if ((*it)->obtenerDato() == val) 
        {
            delete *it;
            desc.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
list<NodoGeneral<T>*>* NodoGeneral<T>::obtenerDesc() 
{
    return &desc;
}

template <class T>
void NodoGeneral<T>::imprimir_desc() 
{
    for (auto it = desc.begin(); it != desc.end(); ++it) 
    {
        cout << (*it)->obtenerDato() << " ";
    }
    cout << endl;
}

