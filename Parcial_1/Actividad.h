#ifndef Actividad_H
#define Actividad_H

#include <string>
#include "Trabajo.h"
#include <queue>
#include <iostream>

class Actividad
{
    private:
        std::string dia;
        std::string titulo;
        unsigned int hora_inicio;
        unsigned int duracion;
        std::string tipo;

        std::queue<Trabajo> cola_trabajo;

    public:

        Actividad(std::string dia, std::string titulo, unsigned int hora_inicio, unsigned int duracion, std::string tipo);

        std::string getDia();
        std::string getTitulo();
        unsigned int getHoraInicio();
        unsigned int getDuracion();
        std::string getTipo();

        void setDia(std::string dia);
        void setTitulo(std::string titulo);
        void setHoraInicio(unsigned int hora_inicio);
        void setDuracion(unsigned int duracion);
        void setTipo(std::string tipo);

        void agregarTrabajo(std::string dia, std::string titulo, unsigned int hora_inicio, unsigned int duracion, std::string tipo, unsigned int id);
        void mostrarTrabajo();
        void mostrarActividad();
        
};


#endif