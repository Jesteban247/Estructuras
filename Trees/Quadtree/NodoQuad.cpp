#include "NodoQuad.h"

NodoQuad::NodoQuad() : hijoSupIzq(nullptr), hijoSupDer(nullptr), hijoInfIzq(nullptr), hijoInfDer(nullptr) {}

NodoQuad::NodoQuad(punto val) : dato(val), hijoSupIzq(nullptr), hijoSupDer(nullptr), hijoInfIzq(nullptr), hijoInfDer(nullptr) {}

NodoQuad::~NodoQuad() {
    // Implementa la liberación de memoria si es necesario
}

punto NodoQuad::obtenerDato() {
    return dato;
}

void NodoQuad::fijarDato(punto val) {
    dato = val;
}

NodoQuad* NodoQuad::obtenerHijoSupIzq() {
    return hijoSupIzq;
}

NodoQuad* NodoQuad::obtenerHijoSupDer() {
    return hijoSupDer;
}

NodoQuad* NodoQuad::obtenerHijoInfIzq() {
    return hijoInfIzq;
}

NodoQuad* NodoQuad::obtenerHijoInfDer() {
    return hijoInfDer;
}

void NodoQuad::fijarHijoSupIzq(NodoQuad* sizq) {
    hijoSupIzq = sizq;
}

void NodoQuad::fijarHijoSupDer(NodoQuad* sder) {
    hijoSupDer = sder;
}

void NodoQuad::fijarHijoInfIzq(NodoQuad* iizq) {
    hijoInfIzq = iizq;
}

void NodoQuad::fijarHijoInfDer(NodoQuad* ider) {
    hijoInfDer = ider;
}

bool NodoQuad::esHoja() {
    return (hijoSupIzq == nullptr && hijoSupDer == nullptr && hijoInfIzq == nullptr && hijoInfDer == nullptr);
}
