#ifndef Pais_H
#define Pais_H

#include <iostream>
#include <string>
using namespace std;

class Pais
{
    private:
        int id;
        string continente;
        string nombre;
        int estado;

    public:
        Pais(int id, string continente, string nombre);
        Pais(int id, string continente, string nombre, int estado);
        string getContinente();
        int getID();
        string getNombre();
        int getEstado();
        void setEstado(int estado);
         
};
#endif
