#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "NodoBinario.h"
#include <queue>
#include <string>

template <class T>
class ArbolBinario
{
protected:
    NodoBinario<T> *raiz;  // Puntero a la raíz del árbol

public:
    // Constructor y destructor
    ArbolBinario();
    ~ArbolBinario();

    // Métodos para verificar y obtener información

    //  Verifica si el árbol está vacío.
    bool esVacio();

    //  Obtiene el dato almacenado en la raíz del árbol.
    T& obtenerDatoRaiz();

    // Métodos de inserción y eliminación

    //  Inserta un dato en el árbol.
    bool insertar(T& dato);

    //  Elimina un dato del árbol.
    bool eliminar(T& dato);

    // Métodos de impresión

    //  Imprime el árbol de manera gráfica a partir de un nodo dado.
    void imprimirArbolGrafico(NodoBinario<T>* nodo, int nivel, const std::string& prefijo);

    //  Imprime el árbol de manera gráfica comenzando desde la raíz.
    void imprimirArbolGrafico();

    // Métodos de búsqueda

    //  Busca un valor específico en el árbol.
    bool buscar(T& val);

    //  Realiza una búsqueda recursiva de un valor en el árbol a partir de un nodo dado.
    bool buscarRecursivo(NodoBinario<T>* nodo, T& val);

    // Métodos para calcular la altura y el tamaño del árbol

    //  Calcula la altura de un subárbol a partir de un nodo dado.
    int calcularAltura(NodoBinario<T>* nodo);

    //  Calcula la altura total del árbol.
    int altura();

    //  Calcula el tamaño de un subárbol a partir de un nodo dado.
    int calcularTamano(NodoBinario<T>* nodo);

    //  Calcula el tamaño total (número de nodos) del árbol.
    int tamano();

    // Métodos de recorrido

    //  Realiza un recorrido preorden a partir de un nodo dado.
    void preOrdenRecursivo(NodoBinario<T>* nodo);

    //  Realiza un recorrido preorden comenzando desde la raíz.
    void preOrden();

    //  Realiza un recorrido inorden a partir de un nodo dado.
    void inOrdenRecursivo(NodoBinario<T>* nodo);

    //  Realiza un recorrido inorden comenzando desde la raíz.
    void inOrden();

    //  Realiza un recorrido posorden a partir de un nodo dado.
    void posOrdenRecursivo(NodoBinario<T>* nodo);

    //  Realiza un recorrido posorden comenzando desde la raíz.
    void posOrden();

    //  Realiza un recorrido por niveles comenzando desde la raíz.
    void nivelOrden();
};

#include "ArbolBinario.hxx"

#endif
