#include "ArbolAVL.h"

#include <fstream>
#include <sstream>
#include <string>
#include <set>

#include <ctime>


void leerArchivo_AVL(string nombreArchivo, ArbolAVL<int> &arbolAVL)
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
        int value;

        ss >> key >> value;

        if (key=="A")
            arbolAVL.insertar(value);
        else if (key=="E")
            arbolAVL.eliminar(value);
        else
            cout << "Comando no reconocido." << endl;
    }

    inputFile.close();
}

void leerArchivo_Set(string nombreArchivo, set<int> &arbolSet)
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
        int value;

        ss >> key >> value;

        if (key=="A")
            arbolSet.insert(value);
        else if (key=="E")
            arbolSet.erase(value);
        else
            cout << "Comando no reconocido." << endl;
    }

    inputFile.close();
}

int main(int argc, char* argv[]) 
{
    if (argc == 2) 
    {
        cout << "Argumento: " << argv[1] << std::endl;
        
        if (string(argv[1]) != "in_00.txt" &&
            string(argv[1]) != "in_01.txt" &&
            string(argv[1]) != "in_02.txt")
        {
            cout << "Archivo no encontrado." << endl;
            return 0;
        }
            
        cout << "Parte 1(Arbol AVL):" << endl;
        ArbolAVL<int> arbolAVL;
        clock_t init_time = std::clock( );
        leerArchivo_AVL(argv[1], arbolAVL);
        clock_t end_time = std::clock( );
        double calc_time = ( end_time - init_time ) / double( CLOCKS_PER_SEC );
        cout << "Tiempo de ejecucion: " << calc_time << " segundos" << endl;
        arbolAVL.inOrden_vector();
        
        cout << "-------------------------" << endl;

        cout << "Parte 2(Set):" << endl;
        set<int> arbolSet;
        clock_t init_time_2 = std::clock( );
        leerArchivo_Set(argv[1], arbolSet);
        clock_t end_time_2 = std::clock( );
        double calc_time_2 = ( end_time_2 - init_time_2 ) / double( CLOCKS_PER_SEC );
        cout << "Tiempo de ejecucion: " << calc_time_2 << " segundos" << endl;
        if (arbolSet.size()%2!=0)
        {
            auto it = arbolSet.begin();
            advance(it, arbolSet.size()/2);
            cout << "Mediana: " << *it << endl;
        }
        else
        {
            auto it = arbolSet.begin();
            advance(it, arbolSet.size()/2);
            float mediana1 = *it;
            advance(it, -1);
            float mediana2 = *it;
            float mediana = (mediana1+mediana2)/2;
            cout << "Mediana: " << mediana << endl;
        }

    } 
    
    else 
    {
        cout << "No se proporcionaron argumentos en línea de comandos." << endl;
    }
}
