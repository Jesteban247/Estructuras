#include "NodoKD.h"
#include <queue>
#include <cmath>

class ArbolKD {
protected:
    NodoKD* raiz;
    int dimension; // Variable interna para alternar entre dimensiones (0 para x, 1 para y)

public:
    ArbolKD();
    ArbolKD(const punto& val);
    ~ArbolKD();
    punto datoRaiz() const;
    NodoKD* obtenerRaiz() const;
    void fijarRaiz(NodoKD* n_raiz);
    bool esVacio() const;
    bool insertar(const punto& val);
    
    bool insertar_recursivo(NodoKD* nodo, const punto& val, int dim);

    void preOrden(NodoKD* nodo) const;
    void inOrden(NodoKD* nodo) const;
    void posOrden(NodoKD* nodo) const;
    void nivelOrden() const;

    // Agrega una función de búsqueda exacta
    bool buscarExacto(punto val);
    bool buscarExactoRecursivo(punto val, NodoKD* nodoActual);

    // Agrega una función de búsqueda cercana
    punto buscarCercano(punto val);
    void buscarCercanoRecursivo(NodoKD* nodoActual, punto val, double& distanciaMinima, punto& puntoCercano, int dim);
    double distancia(punto p1, punto p2);
};
