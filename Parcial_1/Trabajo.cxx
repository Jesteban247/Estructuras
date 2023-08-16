#include "Trabajo.h"

Trabajo::Trabajo()
{
}

Trabajo::Trabajo(unsigned int identificador)
{
    this->identificador = identificador;
}


void Trabajo::setIdentificador(unsigned int identificador)
{
    this->identificador = identificador;
}

unsigned int Trabajo::getIdentificador()
{
    return this->identificador;
}

