#include <iostream>
#include "ArbolQuad.h"
#include "ArbolKD.h"

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

void leerArchivo_Quad(string nombreArchivo, ArbolQuad &quadtree)
{
    ifstream inputFile(nombreArchivo);

    if (!inputFile.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return ;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string key;
        float x;
        int y;

        ss >> key >> x >> y;

        punto p= {key, x, y};
        quadtree.insertar(p);
    }

    inputFile.close();
}

void leerArchivo_KD(string nombreArchivo, ArbolKD &kdtree)
{
    ifstream inputFile(nombreArchivo);

    if (!inputFile.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return ;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string key;
        float x;
        int y;

        ss >> key >> x >> y;
        
        punto p= {key, x, y};
        kdtree.insertar(p);
    }

    inputFile.close();
}

int main(int argc, char* argv[]) {

    if (argc == 2) 
    {
        cout << "Argumento: " << argv[1] << std::endl;
        if (string(argv[1]) != "ejemplo1.txt" &&
            string(argv[1]) != "ejemplo2.txt" &&
            string(argv[1]) != "ejemplo3.txt")
        {
            cout << "Archivo no encontrado." << endl;
            return 0;
        }

            cout << "Parte 1(Quadtree):" << endl;
            ArbolQuad quadtree;
            clock_t init_time = std::clock( );
            leerArchivo_Quad(argv[1], quadtree);
            clock_t end_time = std::clock( );
            double calc_time = ( end_time - init_time ) / double( CLOCKS_PER_SEC );
            cout << "Tiempo de ejecucion: " << calc_time << " segundos" << endl;
            
            cout << "-------------------------" << endl;

            cout << "Parte 2(Kdtree):" << endl;
            ArbolKD kdtree;
            clock_t init_time2 = std::clock( );
            leerArchivo_KD(argv[1], kdtree);
            clock_t end_time2 = std::clock( );
            double calc_time2 = ( end_time2 - init_time2 ) / double( CLOCKS_PER_SEC );
            cout << "Tiempo de ejecucion: " << calc_time2 << " segundos" << endl;

            cout << "-------------------------" << endl;
            cout << "Busqueda de un punto:" << endl;
            cout << "Digite el peso en gramos (hasta dos dígitos decimales): ";
            float peso;
            cin >> peso;
            cout << "Digite el código del color: ";
            int color;
            cin >> color;

            punto p = {"", peso, color};

            cout << "-------------------------" << endl;
            cout << "Parte 1(Quadtree):" << endl;
            clock_t init_time3 = std::clock( );
            if (quadtree.buscarExacto(p)) {
                cout << "El valor (" << p.x << ", " << p.y << ") se encuentra en el árbol" << endl;
            } else {
                cout << "El valor (" << p.x << ", " << p.y << ") no se encuentra en el árbol" << endl;
                cout << "El valor más cercano es: " << quadtree.buscarCercano(p) << endl;
            }
            clock_t end_time3 = std::clock( );
            double calc_time3 = ( end_time3 - init_time3 ) / double( CLOCKS_PER_SEC );
            cout << "Tiempo de ejecucion: " << calc_time3 << " segundos" << endl;

            cout << "-------------------------" << endl;
            cout << "Parte 2(Kdtree):" << endl;
            clock_t init_time4 = std::clock( );
            if (kdtree.buscarExacto(p)) {
                cout << "El valor (" << p.x << ", " << p.y << ") se encuentra en el árbol" << endl;
            } else {
                cout << "El valor (" << p.x << ", " << p.y << ") no se encuentra en el árbol" << endl;
                cout << "El valor más cercano es: " << kdtree.buscarCercano(p) << endl;
            }
            clock_t end_time4 = std::clock( );
            double calc_time4 = ( end_time4 - init_time4 ) / double( CLOCKS_PER_SEC );
            cout << "Tiempo de ejecucion: " << calc_time4 << " segundos" << endl;

    }

    else
    {
        cout << "Digite algo mal" << endl;
    }

    return 0;
}
