#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "NodoAVL.h"
#include <queue>
#include <string>
#include <vector>

template <class T>
class ArbolAVL
{
public:
    // Constructor y destructor
    ArbolAVL();
    ~ArbolAVL();

    // Métodos para verificar y obtener información
    bool esVacio() const;
    const T& obtenerDatoRaiz() const;
    int altura();
    int tamano();

    // Métodos de impresión
    void imprimirArbolGrafico();

    // Métodos de búsqueda
    bool buscar(T& val);

    // Métodos de recorrido
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();

    // Métodos de inserción y eliminación
    bool insertar(const T& dato);
    bool eliminar(const T& dato);

    //Metodo para el Taller_3 (Recorrido inOrden con un vector para guardar los datos)
    void inOrden_vector();

private:
    // Atributo de la clase
    NodoAVL<T> *raiz;

    // Métodos privados para operaciones internas

        // Métodos para verificar y obtener información
        int Altura_arbol(NodoAVL<T>* nodo);
        int calcularTamano(NodoAVL<T>* nodo);

        // Métodos de impresión
        void imprimirArbolGrafico(NodoAVL<T>* nodo, int nivel, const std::string& prefijo);

        // Métodos de búsqueda
        bool buscarRecursivo(NodoAVL<T>* nodo, T& val);

        // Métodos de recorrido
        void preOrdenRecursivo(NodoAVL<T>* nodo);
        void inOrdenRecursivo(NodoAVL<T>* nodo);
        void posOrdenRecursivo(NodoAVL<T>* nodo);

        // Métodos de inserción y eliminación
        NodoAVL<T>* insertarRecursivo(NodoAVL<T>* nodo, const T& dato);
        NodoAVL<T>* eliminarRecursivo(NodoAVL<T>* nodo, const T& dato);
        void balancear(NodoAVL<T>*& nodo);
        int calcularAltura(NodoAVL<T>* nodo) const;
        int calcularFactorEquilibrio(NodoAVL<T>* nodo) const;
        NodoAVL<T>* rotacionDerecha(NodoAVL<T>* nodo);
        NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* nodo);
        NodoAVL<T>* rotacionDerechaIzquierda(NodoAVL<T>* nodo);
        NodoAVL<T>* rotacionIzquierdaDerecha(NodoAVL<T>* nodo);

        //Metodo para el Taller_3 (Recorrido inOrden con un vector para guardar los datos)
        void inOrdenRecursivo_vector(NodoAVL<T>* nodo, vector<T>& resultado);
};

#include "ArbolAVL.hxx"

#endif

