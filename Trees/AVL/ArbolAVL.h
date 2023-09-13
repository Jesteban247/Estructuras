#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "NodoAVL.h"

template <class T>
class ArbolAVL
{
    protected:
    NodoAVL<T> *raiz;

    public:
    ArbolAVL();
    ~ArbolAVL();
    bool esVacio() const;
    const T& obtenerDatoRaiz() const;

    bool insertar(const T& dato);
    bool eliminar(const T& dato);

    void imprimirArbolGrafico(NodoAVL<T>* nodo, int nivel, const std::string& prefijo);
    void imprimirArbolGrafico();

    bool buscar(T& val);
    bool buscarRecursivo(NodoAVL<T>* nodo, T& val);

    int altura();
    int calcularAltura(NodoAVL<T>* nodo);

    int tamano();
    int calcularTamano(NodoAVL<T>* nodo);

    void preOrdenRecursivo(NodoAVL<T>* nodo);
    void preOrden();

    void inOrdenRecursivo(NodoAVL<T>* nodo);
    void inOrden();

    void posOrdenRecursivo(NodoAVL<T>* nodo);
    void posOrden();

    void nivelOrden();

    
    NodoAVL<T>* insertarRecursivo(NodoAVL<T>* nodo, const T& dato);
    NodoAVL<T>* eliminarRecursivo(NodoAVL<T>* nodo, const T& dato);
    void balancear(NodoAVL<T>*& nodo);
    int calcularAltura(NodoAVL<T>* nodo) const;
    int calcularFactorEquilibrio(NodoAVL<T>* nodo) const;
    NodoAVL<T>* rotacionDerecha(NodoAVL<T>* nodo);
    NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* nodo);
    NodoAVL<T>* rotacionDerechaIzquierda(NodoAVL<T>* nodo);
    NodoAVL<T>* rotacionIzquierdaDerecha(NodoAVL<T>* nodo);
    void imprimirArbolGrafico(NodoAVL<T>* nodo, int nivel, const std::string& prefijo) const;
    bool buscarRecursivo(const NodoAVL<T>* nodo, const T& val) const;
    int calcularTamano(NodoAVL<T>* nodo) const;
    void preOrdenRecursivo(const NodoAVL<T>* nodo) const;
    void inOrdenRecursivo(const NodoAVL<T>* nodo) const;
    void posOrdenRecursivo(const NodoAVL<T>* nodo) const;
};

#include "ArbolAVL.hxx"

#endif
