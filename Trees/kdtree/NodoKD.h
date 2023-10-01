#include "Punto.h"

class NodoKD {
protected:
    punto dato;
    NodoKD* hijoIzq;
    NodoKD* hijoDer;

public:
    NodoKD();
    NodoKD(const punto& val);
    ~NodoKD();
    bool esHoja() const;
    punto obtenerDato() const;
    void fijarDato(const punto& val);
    NodoKD* obtenerHijoIzq() const;
    NodoKD* obtenerHijoDer() const;
    void fijarHijoIzq(NodoKD* izq);
    void fijarHijoDer(NodoKD* der);
};