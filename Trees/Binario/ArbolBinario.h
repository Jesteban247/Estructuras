#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "NodoBinario.h"
#include <queue>
#include <string>

template <class T>
class ArbolBinario
{
    protected:
    NodoBinario<T> *raiz;

    public:
    ArbolBinario();
    ~ArbolBinario();
    bool esVacio();
    T& obtenerDatoRaiz();

    bool insertar(T& dato);

    void imprimirArbolGrafico(NodoBinario<T>* nodo, int nivel, const std::string& prefijo);
    void imprimirArbolGrafico();
    
    bool eliminar(T& dato);

    bool buscar(T& val);
    bool buscarRecursivo(NodoBinario<T>* nodo, T& val);

    int calcularAltura(NodoBinario<T>* nodo);
    int altura();

    int calcularTamano(NodoBinario<T>* nodo);
    int tamano();

    void preOrdenRecursivo(NodoBinario<T>* nodo);
    void preOrden();

    void inOrdenRecursivo(NodoBinario<T>* nodo);
    void inOrden();

    void posOrdenRecursivo(NodoBinario<T>* nodo);
    void posOrden();

    void nivelOrden();
};

#include "ArbolBinario.hxx"

#endif