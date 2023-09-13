#include "ArbolAVL.h"

int menu()
{
    cout << "***Menu***" << endl;
    cout << "1. Insertar " << endl;
    cout << "2. Eliminar " << endl;
    cout << "3. Imprimir Arbol " << endl;
    cout << "4. Buscar " << endl;
    cout << "5. Altura " << endl;
    cout << "6. Tamaño " << endl;
    cout << "7. PreOrden " << endl;
    cout << "8. PostOrden " << endl;
    cout << "9. InOrden " << endl;
    cout << "10. NivelOrden " << endl;
    cout << "11. Salir " << endl;
    cout << "------------" << endl;
    cout << "Opcion: ";
    int opcion;
    cin >> opcion;

    return opcion;
}

int main() 
{
    ArbolAVL<int> arbol;

    int opcion = 0;

    while (opcion != 11)
    {

        if (opcion == 1)
        {
            cout << "Ingrese el valor a insertar: ";
            int valor;
            cin >> valor;
            
            bool status = arbol.insertar(valor);
            if (status)
            {
                cout << "Se inserto correctamente" << endl;
            }
            else
            {
                cout << "No se pudo insertar" << endl;
            }
        }

        if (opcion == 2)
        {
            cout << "Ingrese el valor a eliminar: ";
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

        if (opcion == 3)
        {
            cout << "---------------------" << endl;
            arbol.imprimirArbolGrafico();
            cout << "---------------------" << endl;
        }

     

        if (opcion == 4)
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

        if (opcion == 5)
        {
            cout << "La altura del arbol es: " << arbol.altura() << endl;
        }

        if (opcion == 6)
        {
            cout << "El tamaño del arbol es: " << arbol.tamano() << endl;
        }

        if (opcion == 7)
        {
            cout << "---------------------" << endl;
            cout << "Preorden: ";
            arbol.preOrden();
            cout << "\n" << "---------------------" << endl;
        }

        if (opcion == 8)
        {
            cout << "---------------------" << endl;
            cout << "Postorden: ";
            arbol.posOrden();
            cout << "\n" << "---------------------" << endl;
        }

        if (opcion == 9)
        {
            cout << "---------------------" << endl;
            cout << "Inorden: ";
            arbol.inOrden();
            cout << "\n" << "---------------------" << endl;
        }

        if (opcion == 10)
        {
            cout << "---------------------" << endl;
            cout << "Nivelorden: ";
            arbol.nivelOrden();
            cout << "\n" << "---------------------" << endl;
        }

        
        opcion = menu();
    }
    

    return 0;
}