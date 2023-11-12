#include "Jugador.h"

//Constructores
Jugador::Jugador()
{
    nombre= "";
    turno= 0;
}

Jugador::Jugador(string nombre, int turno, int id, int tropas)
{
    this->nombre= nombre;
    this->turno= turno;
    this->id= id;
    this->tropas= tropas;
}

//Destructor
Jugador::~Jugador()
{
}

//Getters
string Jugador::getNombre()
{
    return nombre;
}

int Jugador::getTurno()
{
    return turno;
}

int Jugador::getId()
{
    return id;
}

int Jugador::getTropas()
{
    return tropas;
}

//Setters
void Jugador::setNombre(string nombre)
{
    this->nombre= nombre;
}

void Jugador::setTurno(int turno)
{
    this->turno= turno;
}

void Jugador::setId(int id)
{
    this->id= id;
}

void Jugador::setTropas(int tropas)
{
    this->tropas= tropas;
}

//Metodos
void Jugador::agregarTarjeta(int id)
{
    Tarjetas.insert(id);
}

void Jugador::eliminarTarjetas()
{
    Tarjetas.clear();
}

set <int> Jugador::getTarjetas()
{
    return Tarjetas;
}
