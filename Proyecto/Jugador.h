#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <set>
using namespace std;

class Jugador
{
    private:
        //Info
        string nombre;
        int turno;
        int id;
        int tropas;
        set<int> Tarjetas;


    public:
        //Constructores
        Jugador();
        Jugador(string nombre,int turno, int id, int tropas);
        //Destructor
        ~Jugador();
        //Getters
        string getNombre();
        int getTurno();
        int getId();
        int getTropas();
        //Setters
        void setNombre(string nombre);
        void setTurno(int turno);
        void setId(int id);
        void setTropas(int tropas);
        //Metodos
        void agregarTarjeta(int id);
        void eliminarTarjetas();
        set <int> getTarjetas();
};

#endif // JUGADOR_H
