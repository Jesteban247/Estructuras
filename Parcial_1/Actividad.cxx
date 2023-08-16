#include "Actividad.h" 

//Desarrolla los cinstructores

Actividad::Actividad(std::string dia, std::string titulo, unsigned int hora_inicio, unsigned int duracion, std::string tipo)
{
    this->dia = dia;
    this->titulo = titulo;
    this->hora_inicio = hora_inicio;
    this->duracion = duracion;
    this->tipo = tipo;
}

//Haz lo setters y getters

void Actividad::setDia(std::string dia)
{
    this->dia = dia;
}

void Actividad::setTitulo(std::string titulo)
{
    this->titulo = titulo;
}

void Actividad::setHoraInicio(unsigned int hora_inicio)
{
    this->hora_inicio = hora_inicio;
}

void Actividad::setDuracion(unsigned int duracion)
{
    this->duracion = duracion;
}

void Actividad::setTipo(std::string tipo)
{
    this->tipo = tipo;
}

std::string Actividad::getDia()
{
    return dia;
}

std::string Actividad::getTitulo()
{
    return titulo;
}

unsigned int Actividad::getHoraInicio()
{
    return hora_inicio;
}

unsigned int Actividad::getDuracion()
{
    return duracion;
}

std::string Actividad::getTipo()
{
    return tipo;
}

//agrega trabajo a la queue

void Actividad::agregarTrabajo(std::string dia, std::string titulo, unsigned int hora_inicio, unsigned int duracion, std::string tipo, unsigned int id)
{
    //verificar que esa actividad exista
    if (dia != this->dia || titulo != this->titulo || hora_inicio != this->hora_inicio || duracion != this->duracion || (tipo != "poster" && tipo != "short"))
    {
        std::cout << "La actividad no existe" << std::endl;
        return;
    }
    else
    {
        //verificar que el id no este repetido
        std::queue<Trabajo> cola_trabajo_aux = cola_trabajo;
        while (!cola_trabajo_aux.empty())
        {
            if (cola_trabajo_aux.front().getIdentificador() == id)
            {
                std::cout << "El trabajo ya existe" << std::endl;
                return;
            }
            cola_trabajo_aux.pop();
        }
        
        //agregar trabajo
        Trabajo trabajo(id);
        cola_trabajo.push(trabajo);
    }
}

//Mostra la cola de trabajo

void Actividad::mostrarTrabajo()
{
    std::queue<Trabajo> cola_trabajo_aux = cola_trabajo;
    while (!cola_trabajo_aux.empty())
    {
        std::cout << cola_trabajo_aux.front().getIdentificador() << std::endl;
        cola_trabajo_aux.pop();
    }
}

//Muestra la actividad

void Actividad::mostrarActividad()
{
    std::cout << "Dia: " << dia << std::endl;
    std::cout << "Titulo: " << titulo << std::endl;
    std::cout << "Hora de inicio: " << hora_inicio << std::endl;
    std::cout << "Duracion: " << duracion << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Trabajos: " << std::endl;
    mostrarTrabajo();
}