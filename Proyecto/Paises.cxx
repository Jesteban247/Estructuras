#include "Paises.h"

//Constructores
Paises::Paises()
{
    this->id = 0;
    this->continente = "";
    this->nombre = "";
    this->estado = 0;
    this->id_jugador = 0;
    this->ejercitos = 0;
}

Paises::Paises(int id, string continente, string nombre, int estado, int id_jugador, int ejercitos)
{
    this->id = id;
    this->continente = continente;
    this->nombre = nombre;
    this->estado = estado;
    this->id_jugador = id_jugador;
    this->ejercitos = ejercitos;
}

//Destructor
Paises::~Paises()
{
}

//Getters
int Paises::getId()
{
    return this->id;
}

string Paises::getContinente()
{
    return this->continente;
}

string Paises::getNombre()
{
    return this->nombre;
}

int Paises::getEstado()
{
    return this->estado;
}

int Paises::getId_jugador()
{
    return this->id_jugador;
}

int Paises::getEjercitos()
{
    return this->ejercitos;
}

//Setters
void Paises::setId(int id)
{
    this->id = id;
}

void Paises::setContinente(string continente)
{
    this->continente = continente;
}

void Paises::setNombre(string nombre)
{
    this->nombre = nombre;
}

void Paises::setEstado(int estado)
{
    this->estado = estado;
}

void Paises::setId_jugador(int id_jugador)
{
    this->id_jugador = id_jugador;
}

void Paises::setEjercitos(int ejercitos)
{
    this->ejercitos = ejercitos;
}




