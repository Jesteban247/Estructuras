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
        getContinente();
        getID();
        getNombre();
        getEstado();
        setEstado(int estado);
         
};
#endif
