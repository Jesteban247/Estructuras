#ifndef Jugador_H
#define Jugador_H

#include "Pais.h"
#include <map>
#include <set>

class Jugador
{
    protected:
        string nombre;
        int turno;
        int ejercitos;
        int dado;
        //Guarda el id del pais y la cantidad de ejercitos del pais
        map<int, int> paises;
        set<int> Tarjetas;


    public:
        Jugador(string nombre, int turno, int ejercitos);
        
        string getNombre();

        int getTurno();

        int getDado();

        void setDado(int dado);

        void setTurno(int turno);
        
        int getEjercitos();
        
        void setEjercitos(int ejercitos);

        void agregarPais(int id, int ejercitos);
      
        map<int, int> getPaises();
       
        void setPaises(map<int, int> paises);

        void EliminarPais(int id);
       
        void imprimirPaises();

        void agregarTarjeta(int id);

        void eliminarTarjeta(int id);

        set<int> getTarjetas();
        
};
#endif
