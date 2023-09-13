#include "ArbolBinario.h"

template <class T>
ArbolBinario<T>::ArbolBinario()
{
    raiz = nullptr;
}

template <class T>
ArbolBinario<T>::~ArbolBinario()
{

}

template <class T>
bool ArbolBinario<T>::esVacio()
{
    return raiz == nullptr;
}

template <class T>
T& ArbolBinario<T>::obtenerDatoRaiz()
{
    return raiz->dato;
}

template <class T>
bool ArbolBinario<T>::insertar(T& dato)
{
    // Crear un nuevo nodo con el dato proporcionado
    NodoBinario<T>* nuevoNodo = new NodoBinario<T>();
    nuevoNodo->fijarDato(dato);

    // Si el árbol está vacío, establecer el nuevo nodo como raíz
    if (esVacio()) {
        raiz = nuevoNodo;
        return true;
    }

    // Si el árbol no está vacío, comenzar desde la raíz
    NodoBinario<T>* actual = raiz;

    while (true) {
        // Comparar el dato con el nodo actual
        if (dato < actual->obtenerDato()) {
            // Si el dato es menor, ir al hijo izquierdo
            if (actual->obtenerHijoIzq() == nullptr) {
                // Si el hijo izquierdo está vacío, insertar el nuevo nodo aquí
                actual->fijarHijoIzq(nuevoNodo);
                return true;
            }
            // Si no está vacío, continuar con el hijo izquierdo
            actual = actual->obtenerHijoIzq();
        } else if (dato > actual->obtenerDato()) {
            // Si el dato es mayor, ir al hijo derecho
            if (actual->obtenerHijoDer() == nullptr) {
                // Si el hijo derecho está vacío, insertar el nuevo nodo aquí
                actual->fijarHijoDer(nuevoNodo);
                return true;
            }
            // Si no está vacío, continuar con el hijo derecho
            actual = actual->obtenerHijoDer();
        } else {
            // Si el dato ya existe en el árbol, no hacer nada
            delete nuevoNodo; // Liberar la memoria del nodo que no se usa
            return false;
        }
    }
}

template <class T>
void ArbolBinario<T>::imprimirArbolGrafico(NodoBinario<T>* nodo, int nivel, const std::string& prefijo)
{
    if (nodo == nullptr) {
        return;
    }

    const int espaciado = 4;

    imprimirArbolGrafico(nodo->obtenerHijoDer(), nivel + 1, "D:");
    std::cout << std::string(espaciado * nivel, ' ') << prefijo << nodo->obtenerDato() << std::endl;
    imprimirArbolGrafico(nodo->obtenerHijoIzq(), nivel + 1, "I:");
}

template <class T>
void ArbolBinario<T>::imprimirArbolGrafico()
{
    if (raiz == nullptr) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }
    
    std::cout << "Árbol Binario:" << std::endl;
    imprimirArbolGrafico(raiz, 0, "R:");
}

template <class T>
bool ArbolBinario<T>::eliminar(T& dato) {
    // Si el árbol está vacío, no hay nada que eliminar
    if (esVacio()) {
        return false;
    }

    // Declarar un nodo auxiliar y un padre auxiliar
    NodoBinario<T>* actual = raiz;
    NodoBinario<T>* padre = nullptr;

    // Buscar el nodo que contiene el dato
    while (actual != nullptr && actual->obtenerDato() != dato) {
        padre = actual;
        if (dato < actual->obtenerDato()) {
            actual = actual->obtenerHijoIzq();
        } else {
            actual = actual->obtenerHijoDer();
        }
    }

    // Si no se encontró el dato en el árbol, retornar false
    if (actual == nullptr) {
        return false;
    }

    // Caso 1: El nodo tiene dos hijos
    if (actual->obtenerHijoIzq() != nullptr && actual->obtenerHijoDer() != nullptr) {
        // Encontrar el sucesor inorden del nodo
        NodoBinario<T>* sucesor = actual->obtenerHijoDer();
        padre = actual;
        while (sucesor->obtenerHijoIzq() != nullptr) {
            padre = sucesor;
            sucesor = sucesor->obtenerHijoIzq();
        }

        // Copiar el dato del sucesor en el nodo actual
        actual->fijarDato(sucesor->obtenerDato());

        // Establecer el nodo actual para eliminar el sucesor
        actual = sucesor;
    }

    // Caso 2: El nodo tiene cero o un hijo
    NodoBinario<T>* hijo = (actual->obtenerHijoIzq() != nullptr) ? actual->obtenerHijoIzq() : actual->obtenerHijoDer();

    if (padre == nullptr) {
        raiz = hijo; // El nodo a eliminar era la raíz
    } else if (padre->obtenerHijoIzq() == actual) {
        padre->fijarHijoIzq(hijo);
    } else {
        padre->fijarHijoDer(hijo);
    }

    delete actual; // Liberar la memoria del nodo eliminado
    return true;
}


// Función para buscar un valor en el árbol binario
template <class T>
bool ArbolBinario<T>::buscar(T& val) {
    return buscarRecursivo(raiz, val);
}

// Función auxiliar para buscar un valor de forma recursiva en el árbol
template <class T>
bool ArbolBinario<T>::buscarRecursivo(NodoBinario<T>* nodo, T& val) {
    if (nodo == nullptr) {
        return false; // El valor no se encontró en el árbol
    }

    if (val == nodo->obtenerDato()) {
        return true; // El valor se encontró en el nodo actual
    } else if (val < nodo->obtenerDato()) {
        // Si el valor es menor, buscar en el subárbol izquierdo
        return buscarRecursivo(nodo->obtenerHijoIzq(), val);
    } else {
        // Si el valor es mayor, buscar en el subárbol derecho
        return buscarRecursivo(nodo->obtenerHijoDer(), val);
    }
}



template <class T>
int ArbolBinario<T>::calcularAltura(NodoBinario<T>* nodo) {
    if (nodo == nullptr) {
        return -1; // Árbol vacío o nodo hoja
    } else {
        int alturaIzq = calcularAltura(nodo->obtenerHijoIzq());
        int alturaDer = calcularAltura(nodo->obtenerHijoDer());
        return 1 + std::max(alturaIzq, alturaDer); // La altura es el máximo entre las alturas de los hijos más 1
    }
}


template <class T>
int ArbolBinario<T>::altura() {
    return calcularAltura(raiz);
}



template <class T>
int ArbolBinario<T>::calcularTamano(NodoBinario<T>* nodo) {
    if (nodo == nullptr) {
        return 0; // Árbol vacío
    } else {
        int tamanoIzq = calcularTamano(nodo->obtenerHijoIzq());
        int tamanoDer = calcularTamano(nodo->obtenerHijoDer());
        return 1 + tamanoIzq + tamanoDer; // El tamaño es 1 (el nodo actual) más los tamaños de los subárboles izquierdo y derecho
    }
}

template <class T>
int ArbolBinario<T>::tamano() {
    return calcularTamano(raiz);
}


template <class T>
void ArbolBinario<T>::preOrdenRecursivo(NodoBinario<T>* nodo) {
    if (nodo != nullptr) {
        // Visitar el nodo actual
        std::cout << nodo->obtenerDato() << " ";
        // Recorrer el subárbol izquierdo
        preOrdenRecursivo(nodo->obtenerHijoIzq());
        // Recorrer el subárbol derecho
        preOrdenRecursivo(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolBinario<T>::preOrden() {
    preOrdenRecursivo(raiz);
}



template <class T>
void ArbolBinario<T>::inOrdenRecursivo(NodoBinario<T>* nodo) {
    if (nodo != nullptr) {
        // Recorrer el subárbol izquierdo
        inOrdenRecursivo(nodo->obtenerHijoIzq());
        // Visitar el nodo actual
        std::cout << nodo->obtenerDato() << " ";
        // Recorrer el subárbol derecho
        inOrdenRecursivo(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolBinario<T>::inOrden() {
    inOrdenRecursivo(raiz);
}



template <class T>
void ArbolBinario<T>::posOrdenRecursivo(NodoBinario<T>* nodo) {
    if (nodo != nullptr) {
        // Recorrer el subárbol izquierdo
        posOrdenRecursivo(nodo->obtenerHijoIzq());
        // Recorrer el subárbol derecho
        posOrdenRecursivo(nodo->obtenerHijoDer());
        // Visitar el nodo actual
        std::cout << nodo->obtenerDato() << " ";
    }
}

template <class T>
void ArbolBinario<T>::posOrden() {
    posOrdenRecursivo(raiz);
}



// Función para realizar un recorrido por niveles (nivelorden) del árbol
template <class T>
void ArbolBinario<T>::nivelOrden() {
    if (esVacio()) {
        return;
    }

    std::queue<NodoBinario<T>*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        NodoBinario<T>* nodo = cola.front();
        cola.pop();

        // Visitar el nodo actual
        std::cout << nodo->obtenerDato() << " ";

        // Agregar los hijos a la cola (si existen)
        if (nodo->obtenerHijoIzq() != nullptr) {
            cola.push(nodo->obtenerHijoIzq());
        }
        if (nodo->obtenerHijoDer() != nullptr) {
            cola.push(nodo->obtenerHijoDer());
        }
    }
}
