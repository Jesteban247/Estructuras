#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <charconv>
#include <cmath>
#include "grafo.h"
#include "punto.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    string argumento1, argumento2; 

    if (argc == 3) 
    {
        argumento1 = argv[1]; 
        cout << "Archivo de entrada " << argumento1 << endl;
        argumento2 = argv[2];
        cout << "Archivo de salida " << argumento2 << endl;
    } 
    
    else {
        cout << "No se proporcionaron argumentos, o se proporcionaron más de los necesarios." << endl;
        return 0;
    }

    cout << "Lectura de archivo" << endl;

    ifstream archivo(argumento1);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int numCircuitos;
    archivo >> numCircuitos;

    vector<vector<Punto>> circuitos;

    for (int i = 0; i < numCircuitos; i++) {
        int numAgujeros;
        archivo >> numAgujeros;

        vector<Punto> agujeros;

        for (int j = 0; j < numAgujeros; j++) {
            double x, y;
            archivo >> x >> y;
            char letra = char(j+65);
            string a;
            a+=letra;
            agujeros.push_back(Punto(x, y, a));

        }

        circuitos.push_back(agujeros);
    }

    archivo.close();

    //Acceder a la información de los agujeros en la matriz "circuitos"
    for (int i = 0; i < numCircuitos; i++) {
        cout << "Circuito " << i + 1 << ":" << endl;
        for (const Punto &punto : circuitos[i]) {
            cout << punto.id << ": " << punto.x << " , " << punto.y << endl;
        }
    }

    cout << "----------------------"<< endl;

    cout << "Información basica" << endl;
    cout << "Numero de circuitos: " << numCircuitos << endl;
    for (int i = 0; i < numCircuitos; i++) {
        cout << "Circuito " << i + 1 << ": " << circuitos[i].size() << " agujeros" << endl;
    }

    cout << "----------------------"<< endl;

    ofstream archivo_salida(argumento2);

    if (archivo_salida.is_open())
    {
        archivo_salida << numCircuitos << endl;

        for (int i = 0; i < numCircuitos; i++) 
        {
            archivo_salida << circuitos[i].size() << endl;
            cout << "Circuito " << i + 1 << ":" << endl;
            GrafoNoDirigido<string> grafo;

            if (circuitos[i].size() > 0) 
            {

                //Agregamos los nodos al grafo
                for (const Punto &punto : circuitos[i]) 
                {
                    grafo.agregarNodo(punto.id);
                }

                //Agregamos las aristas al grafo
                for (int j = 0; j < circuitos[i].size(); j++) 
                {
                    for (int k = 0; k < circuitos[i].size(); k++) 
                    {
                        if (j != k) 
                        {
                            double distancia = sqrt(pow(circuitos[i][j].x - circuitos[i][k].x, 2) + pow(circuitos[i][j].y - circuitos[i][k].y, 2));
                            grafo.agregarArista(circuitos[i][j].id, circuitos[i][k].id, distancia);
                        }
                    }
                }

                //Buscar el nodo más cercano a (0.0)
                double distancia_mi= 1000;
                string nodo_cercano;
                int nodo_cercano_pos;
                for (int j = 0; j < circuitos[i].size(); j++) 
                {
                    double distancia = sqrt(pow(circuitos[i][j].x, 2) + pow(circuitos[i][j].y, 2));
                    if (distancia < distancia_mi) 
                    {
                        distancia_mi = distancia;
                        nodo_cercano = circuitos[i][j].id;
                        nodo_cercano_pos = j;
                    }
                }

                cout << "Nodo más cercano a (0.0): " << nodo_cercano << endl;

                vector<string> recorrido= grafo.Recorrido(nodo_cercano);

                //Guarda el circuito con los puntos x,y
                for (int j = 0; j < recorrido.size(); j++) 
                {
                    for (int k = 0; k < circuitos[i].size(); k++) 
                    {
                        if (recorrido[j] == circuitos[i][k].id) 
                        {
                            archivo_salida << circuitos[i][k].x << " , " << circuitos[i][k].y << endl;
                        }
                    }
                }
            

                cout << "----------------------"<< endl;
            }
        }

        archivo.close();
        cout << "Archivo creado exitosamente." << endl;
    } 
    
    else 
    {
        cout << "No se pudo abrir el archivo." << endl;
    }


    return 0;
}
