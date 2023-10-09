#include "ArbolQuad.h"

ArbolQuad::ArbolQuad() : raiz(nullptr) {}

ArbolQuad::ArbolQuad(punto val) : raiz(new NodoQuad(val)) {}

ArbolQuad::~ArbolQuad() {
    // Implementa la liberación de memoria si es necesario
}

punto ArbolQuad::datoRaiz() {
    return raiz->obtenerDato();
}

NodoQuad* ArbolQuad::obtenerRaiz() {
    return raiz;
}

void ArbolQuad::fijarRaiz(NodoQuad* n_raiz) {
    raiz = n_raiz;
}

bool ArbolQuad::esVacio() {
    return raiz == nullptr;
}

bool ArbolQuad::insertar(punto val) {
    if (raiz == nullptr) {
        raiz = new NodoQuad(val);
        return true;
    } else {
        return insertarRecursivo(val, raiz);
    }
}

bool ArbolQuad::insertarRecursivo(punto val, NodoQuad* nodoActual) {
    if (val == nodoActual->obtenerDato()) {
        // El punto ya existe en el árbol, no se puede insertar de nuevo
        return false;
    }

    // Determinar en qué hijo debe insertarse el punto
    if (val.x < nodoActual->obtenerDato().x) {
        if (val.y < nodoActual->obtenerDato().y) {
            if (nodoActual->obtenerHijoInfIzq() == nullptr) {
                nodoActual->fijarHijoInfIzq(new NodoQuad(val));
                return true;
            } else {
                return insertarRecursivo(val, nodoActual->obtenerHijoInfIzq());
            }
        } else {
            if (nodoActual->obtenerHijoSupIzq() == nullptr) {
                nodoActual->fijarHijoSupIzq(new NodoQuad(val));
                return true;
            } else {
                return insertarRecursivo(val, nodoActual->obtenerHijoSupIzq());
            }
        }
    } else {
        if (val.y < nodoActual->obtenerDato().y) {
            if (nodoActual->obtenerHijoInfDer() == nullptr) {
                nodoActual->fijarHijoInfDer(new NodoQuad(val));
                return true;
            } else {
                return insertarRecursivo(val, nodoActual->obtenerHijoInfDer());
            }
        } else {
            if (nodoActual->obtenerHijoSupDer() == nullptr) {
                nodoActual->fijarHijoSupDer(new NodoQuad(val));
                return true;
            } else {
                return insertarRecursivo(val, nodoActual->obtenerHijoSupDer());
            }
        }
    }
}

void ArbolQuad::preOrden() {
    preOrdenRecursivo(raiz);
    std::cout << std::endl;
}

void ArbolQuad::preOrdenRecursivo(NodoQuad* nodo) {
    if (nodo != nullptr) {
        std::cout << nodo->obtenerDato() << " ";
        preOrdenRecursivo(nodo->obtenerHijoSupIzq());
        preOrdenRecursivo(nodo->obtenerHijoSupDer());
        preOrdenRecursivo(nodo->obtenerHijoInfIzq());
        preOrdenRecursivo(nodo->obtenerHijoInfDer());
    }
}

void ArbolQuad::inOrden() {
    inOrdenRecursivo(raiz);
    std::cout << std::endl;
}

void ArbolQuad::inOrdenRecursivo(NodoQuad* nodo) {
    if (nodo != nullptr) {
        inOrdenRecursivo(nodo->obtenerHijoSupIzq());
        std::cout << nodo->obtenerDato() << " ";
        inOrdenRecursivo(nodo->obtenerHijoSupDer());
        inOrdenRecursivo(nodo->obtenerHijoInfIzq());
        inOrdenRecursivo(nodo->obtenerHijoInfDer());
    }
}

void ArbolQuad::posOrden() {
    posOrdenRecursivo(raiz);
    std::cout << std::endl;
}

void ArbolQuad::posOrdenRecursivo(NodoQuad* nodo) {
    if (nodo != nullptr) {
        posOrdenRecursivo(nodo->obtenerHijoSupIzq());
        posOrdenRecursivo(nodo->obtenerHijoSupDer());
        posOrdenRecursivo(nodo->obtenerHijoInfIzq());
        posOrdenRecursivo(nodo->obtenerHijoInfDer());
        std::cout << nodo->obtenerDato() << " ";
    }
}

void ArbolQuad::nivelOrden() {
    if (raiz == nullptr) {
        return;
    }

    std::queue<NodoQuad*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        NodoQuad* nodo = cola.front();
        cola.pop();
        std::cout << nodo->obtenerDato() << " ";

        if (nodo->obtenerHijoSupIzq() != nullptr) {
            cola.push(nodo->obtenerHijoSupIzq());
        }
        if (nodo->obtenerHijoSupDer() != nullptr) {
            cola.push(nodo->obtenerHijoSupDer());
        }
        if (nodo->obtenerHijoInfIzq() != nullptr) {
            cola.push(nodo->obtenerHijoInfIzq());
        }
        if (nodo->obtenerHijoInfDer() != nullptr) {
            cola.push(nodo->obtenerHijoInfDer());
        }
    }
}


void ArbolQuad::imprimirArbol() {
    imprimirArbolRecursivo(raiz, "", "Raiz");
}

void ArbolQuad::imprimirArbolRecursivo(NodoQuad* nodo, const std::string& prefijo, const std::string& etiqueta) {
    if (nodo == nullptr) {
        return;
    }

    std::cout << prefijo;
    std::cout << "+-- " << etiqueta << ": " << nodo->obtenerDato() << std::endl;

    std::string nuevoPrefijo = prefijo;
    nuevoPrefijo += "|   ";

    imprimirArbolRecursivo(nodo->obtenerHijoSupIzq(), nuevoPrefijo, "NW");
    imprimirArbolRecursivo(nodo->obtenerHijoSupDer(), nuevoPrefijo, "NE");
    imprimirArbolRecursivo(nodo->obtenerHijoInfIzq(), nuevoPrefijo, "SW");
    imprimirArbolRecursivo(nodo->obtenerHijoInfDer(), nuevoPrefijo, "SE");
}

//Buscar cercano

punto ArbolQuad::buscarCercano(punto val) {
    if (raiz == nullptr) {
        throw std::runtime_error("El árbol está vacío");
    }

    double distanciaMinima = distancia(raiz->obtenerDato(), val);
    punto puntoCercano = raiz->obtenerDato();

    buscarCercanoRecursivo(raiz, val, distanciaMinima, puntoCercano);

    return puntoCercano;
}

void ArbolQuad::buscarCercanoRecursivo(NodoQuad* nodoActual, punto val, double& distanciaMinima, punto& puntoCercano) {
    if (nodoActual == nullptr) {
        return;
    }

    double distanciaActual = distancia(nodoActual->obtenerDato(), val);

    if (distanciaActual < distanciaMinima) {
        distanciaMinima = distanciaActual;
        puntoCercano = nodoActual->obtenerDato();
    }

    // Luego, verifica los nodos en los cuatro cuadrantes en orden:
    buscarCercanoRecursivo(nodoActual->obtenerHijoSupIzq(), val, distanciaMinima, puntoCercano);
    buscarCercanoRecursivo(nodoActual->obtenerHijoSupDer(), val, distanciaMinima, puntoCercano);
    buscarCercanoRecursivo(nodoActual->obtenerHijoInfIzq(), val, distanciaMinima, puntoCercano);
    buscarCercanoRecursivo(nodoActual->obtenerHijoInfDer(), val, distanciaMinima, puntoCercano);
}

// Implementa la función de distancia euclidiana
double ArbolQuad::distancia(punto p1, punto p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
