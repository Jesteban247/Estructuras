#include "Pais.h"
    
        Pais::Pais(int id, string continente, string nombre)
        {
            this->id = id;
            this->continente = continente;
            this->nombre = nombre;
            this->estado = 0;
        }
        Pais::Pais(int id, string continente, string nombre, int estado)
        {
            this->id = id;
            this->continente = continente;
            this->nombre = nombre;
            this->estado = estado;
        }

        int Pais::getId()
        {
            return id;
        }

        string Pais::getContinente()
        {
            return continente;
        }

        string Pais::getNombre()
        {
            return nombre;
        }

        int Pais::getEstado()
        {
            return estado;
        }

        void Pais::setEstado(int estado)
        {
            this->estado = estado;
        }

