#ifndef PAISES_H
#define PAISES_H

#include <string>
using namespace std;

class Paises
{
    private:
        //Info
        int id;
        string continente;
        string nombre;  
        //Juego
        int estado;
        int id_jugador;
        int ejercitos;

    public:
        //Constructores
        Paises();
        Paises(int id, string continente, string nombre, int estado, int id_jugador, int ejercitos);
        //Destructor
        ~Paises();
        //Getters
        int getId();
        string getContinente();
        string getNombre();
        int getEstado();
        int getId_jugador();
        int getEjercitos();
        //Setters
        void setId(int id);
        void setContinente(string continente);
        void setNombre(string nombre);
        void setEstado(int estado);
        void setId_jugador(int id_jugador);
        void setEjercitos(int ejercitos);
};

#endif // PAISES_H
