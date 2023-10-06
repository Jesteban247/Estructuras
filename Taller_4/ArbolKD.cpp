#include "ArbolKD.h"


ArbolKD::ArbolKD() {
    raiz = nullptr;
    dimension = 0; // Empezamos comparando en la dimensión x
}

ArbolKD::ArbolKD(const punto& val) {
    raiz = new NodoKD(val);
    dimension = 0; // Empezamos comparando en la dimensión x
}

ArbolKD::~ArbolKD() {
    delete raiz;
}

bool ArbolKD::esVacio() const {
    return raiz == nullptr;
}

punto ArbolKD::datoRaiz() const {
    if (raiz != nullptr) {
        return raiz->obtenerDato();
    } else {
        throw std::logic_error("El árbol está vacío");
    }
}

NodoKD* ArbolKD::obtenerRaiz() const {
    return raiz;
}

void ArbolKD::fijarRaiz(NodoKD* n_raiz) {
    raiz = n_raiz;
}

bool ArbolKD::insertar(const punto& val) {
    

    if (esVacio()) {
        raiz = new NodoKD(val);
        return true;
    } else {
        return insertar_recursivo(raiz, val, 0);
    }
}

bool ArbolKD::insertar_recursivo(NodoKD* nodo, const punto& val, int dim) {
    if (dim == 0) {
        if (val.x < nodo->obtenerDato().x || val.x == nodo->obtenerDato().x) {
            if (nodo->obtenerHijoIzq() == nullptr) {
                nodo->fijarHijoIzq(new NodoKD(val));
                return true;
            } else {
                return insertar_recursivo(nodo->obtenerHijoIzq(), val, 1);
            }
        } else if (val.x > nodo->obtenerDato().x) {
            if (nodo->obtenerHijoDer() == nullptr) {
                nodo->fijarHijoDer(new NodoKD(val));
                return true;
            } else {
                return insertar_recursivo(nodo->obtenerHijoDer(), val, 1);
            }
        } else {
            return false;
        }
    } else {
        if (val.y < nodo->obtenerDato().y || val.y == nodo->obtenerDato().y) {
            if (nodo->obtenerHijoIzq() == nullptr) {
                nodo->fijarHijoIzq(new NodoKD(val));
                return true;
            } else {
                return insertar_recursivo(nodo->obtenerHijoIzq(), val, 0);
            }
        } else if (val.y > nodo->obtenerDato().y) {
            if (nodo->obtenerHijoDer() == nullptr) {
                nodo->fijarHijoDer(new NodoKD(val));
                return true;
            } else {
                return insertar_recursivo(nodo->obtenerHijoDer(), val, 0);
            }
        } else {
            return false;
        }
    }
}

void ArbolKD::preOrden(NodoKD* nodo) const {
    if (nodo != nullptr) {
        std::cout << nodo->obtenerDato() << " ";
        preOrden(nodo->obtenerHijoIzq());
        preOrden(nodo->obtenerHijoDer());
    }
}

void ArbolKD::inOrden(NodoKD* nodo) const {
    if (nodo != nullptr) {
        inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato() << " ";
        inOrden(nodo->obtenerHijoDer());
    }
}

void ArbolKD::posOrden(NodoKD* nodo) const {
    if (nodo != nullptr) {
        posOrden(nodo->obtenerHijoIzq());
        posOrden(nodo->obtenerHijoDer());
        std::cout << nodo->obtenerDato() << " ";
    }
}

void ArbolKD::nivelOrden() const {
    // Implementa aquí el recorrido por nivel del árbol KD
    // Puedes utilizar una cola para realizar el recorrido por nivel.

    std::queue<NodoKD*> cola;
    if (raiz != nullptr) {
        cola.push(raiz);
    }

    while (!cola.empty()) {
        NodoKD* nodo = cola.front();
        cola.pop();

        std::cout << nodo->obtenerDato() << " ";

        if (nodo->obtenerHijoIzq() != nullptr) {
            cola.push(nodo->obtenerHijoIzq());
        }

        if (nodo->obtenerHijoDer() != nullptr) {
            cola.push(nodo->obtenerHijoDer());
        }
    }
}




// Implementa la búsqueda cercana e Implementa la función de distancia euclidiana

double ArbolKD::distancia(punto p1, punto p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

punto ArbolKD::buscarCercano(punto val) {
    if (raiz == nullptr) {
        throw std::runtime_error("El árbol está vacío");
    }

    double distanciaMinima = distancia(raiz->obtenerDato(), val);
    punto puntoCercano = raiz->obtenerDato();

    buscarCercanoRecursivo(raiz, val, distanciaMinima, puntoCercano, 0);

    return puntoCercano;
}

void ArbolKD::buscarCercanoRecursivo(NodoKD* nodoActual, punto val, double& distanciaMinima, punto& puntoCercano, int dim) {
    if (nodoActual == nullptr) {
        return;
    }

    double distanciaActual = distancia(nodoActual->obtenerDato(), val);

    if (distanciaActual < distanciaMinima) {
        distanciaMinima = distanciaActual;
        puntoCercano = nodoActual->obtenerDato();
    }

    int siguienteDim = (dim + 1) % 2; // Alternar entre las dimensiones x e y

    if (dim == 0) { // Si estamos en la dimensión x
        if (val.x < nodoActual->obtenerDato().x || val.x == nodoActual->obtenerDato().x) {
            buscarCercanoRecursivo(nodoActual->obtenerHijoIzq(), val, distanciaMinima, puntoCercano, siguienteDim);
            if (val.x - distanciaMinima <= nodoActual->obtenerDato().x) {
                buscarCercanoRecursivo(nodoActual->obtenerHijoDer(), val, distanciaMinima, puntoCercano, siguienteDim);
            }
        } else if (val.x > nodoActual->obtenerDato().x) {
            buscarCercanoRecursivo(nodoActual->obtenerHijoDer(), val, distanciaMinima, puntoCercano, siguienteDim);
            if (val.x + distanciaMinima >= nodoActual->obtenerDato().x) {
                buscarCercanoRecursivo(nodoActual->obtenerHijoIzq(), val, distanciaMinima, puntoCercano, siguienteDim);
            }
        }
    } else { // Si estamos en la dimensión y
        if (val.y < nodoActual->obtenerDato().y || val.y == nodoActual->obtenerDato().y) {
            buscarCercanoRecursivo(nodoActual->obtenerHijoIzq(), val, distanciaMinima, puntoCercano, siguienteDim);
            if (val.y - distanciaMinima <= nodoActual->obtenerDato().y) {
                buscarCercanoRecursivo(nodoActual->obtenerHijoDer(), val, distanciaMinima, puntoCercano, siguienteDim);
            }
        } else if (val.y > nodoActual->obtenerDato().y) {
            buscarCercanoRecursivo(nodoActual->obtenerHijoDer(), val, distanciaMinima, puntoCercano, siguienteDim);
            if (val.y + distanciaMinima >= nodoActual->obtenerDato().y) {
                buscarCercanoRecursivo(nodoActual->obtenerHijoIzq(), val, distanciaMinima, puntoCercano, siguienteDim);
            }
        }
    }
}

