#include "NodoKD.h"

NodoKD::NodoKD() {
    hijoIzq = nullptr;
    hijoDer = nullptr;
}

NodoKD::NodoKD(const punto& val) {
    dato = val;
    hijoIzq = nullptr;
    hijoDer = nullptr;
}

NodoKD::~NodoKD() {
    delete hijoIzq;
    delete hijoDer;
}

bool NodoKD::esHoja() const {
    return (hijoIzq == nullptr) && (hijoDer == nullptr);
}

punto NodoKD::obtenerDato() const {
    return dato;
}

void NodoKD::fijarDato(const punto& val) {
    dato = val;
}

NodoKD* NodoKD::obtenerHijoIzq() const {
    return hijoIzq;
}

NodoKD* NodoKD::obtenerHijoDer() const {
    return hijoDer;
}

void NodoKD::fijarHijoIzq(NodoKD* izq) {
    hijoIzq = izq;
}

void NodoKD::fijarHijoDer(NodoKD* der) {
    hijoDer = der;
}
