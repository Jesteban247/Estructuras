#include "ArbolGeneral.h"

int menu()
{
    cout << "***Menu***" << endl;
    cout << "1. Fijar raiz" << endl;
    cout << "2. Insertar" << endl;
    cout << "3. Mostrar Hijos" << endl;
    cout << "4. Eliminar" << endl;
    cout << "5. Buscar" << endl;
    cout << "6. Altura" << endl;
    cout << "7. Tamaño" << endl;
    cout << "8. PreOrden" << endl;
    cout << "9. PostOrden" << endl;
    cout << "10. NivelOrden" << endl;
    cout << "11. Salir" << endl;
    cout << "------------" << endl;
    cout << "Opcion: ";
    int opcion;
    cin >> opcion;

    return opcion;
}

int main() 
{
    ArbolGeneral<int> arbol;

    int opcion = 0;

    while (opcion != 11)
    {

        if (opcion == 1)
        {
            cout << "Ingrese el valor de la raiz: ";
            int valor;
            cin >> valor;
            
            NodoGeneral<int>* nodo = new NodoGeneral<int>;
            nodo->fijarDato(valor);
            arbol.fijarRaiz(nodo);
            cout << "El arbol esta vacio? " << arbol.esVacio() << endl;
            cout << "La raiz es: " << arbol.obtenerRaiz()->obtenerDato() << endl;
        }

        if (opcion == 2)
        {
            cout << "Ingrese el valor del padre: ";
            int padre;
            cin >> padre;
            cout << "Ingrese el valor del hijo: ";
            int hijo;
            cin >> hijo;

            bool status = arbol.insertar(padre, hijo);

            if (status)
            {
                cout << "Se inserto correctamente" << endl;
            }
            else
            {
                cout << "No se pudo insertar" << endl;
            }
        }

        if (opcion == 3)
        {
            cout << "Ingrese el valor del padre: ";
            int padre;
            cin >> padre;

            arbol.mostrarHijos(padre);
        }

        if (opcion == 4)
        {
            cout << "Ingrese el valor del nodo a eliminar: ";
            int valor;
            cin >> valor;

            bool status = arbol.eliminar(valor);
            if (status)
            {
                cout << "Se elimino correctamente" << endl;
            }
            else
            {
                cout << "No se pudo eliminar" << endl;
            }

        }

        if (opcion == 5)
        {
            cout << "Ingrese el valor del nodo a buscar: ";
            int valor;
            cin >> valor;

            bool status = arbol.buscar(valor);
            if (status)
            {
                cout << "Se encontro el valor" << endl;
            }
            else
            {
                cout << "No se encontro el valor" << endl;
            }
        }

        if (opcion == 6)
        {
            cout << "La altura del arbol es: " << arbol.calcularAltura() << endl;
        }

        if (opcion == 7)
        {
            cout << "El tamaño del arbol es: " << arbol.calcularTamano() << endl;
        }

        if (opcion == 8)
        {
            arbol.PreOrdenRecorrido();
        }

        if (opcion == 9)
        {
            arbol.PostOrdenRecorrido();
        }

        if (opcion == 10)
        {
            arbol.NivelOrden();
        }

        opcion = menu();
    }
    

    return 0;
}