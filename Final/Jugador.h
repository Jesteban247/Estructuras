#ifndef Jugador_H
#define Jugador_H

#include "Pais.h"
#include <list>
#include <map>

class Jugador
{
    private:
        string nombre;
        int turno;
        int ejercitos;
        //Guarda el id del pais y la cantidad de ejercitos del pais
        map<int, int> paises;

    public:
        Jugador(string nombre, int turno, int ejercitos);
        
        string getNombre();

        int getTurno();
        
        void setTurno(int turno);
        
        int getEjercitos();
        
        void setEjercitos(int ejercitos);

        void agregarPais(int id, int ejercitos);
      
        map<int, int> getPaises();
       
        void setPaises(map<int, int> paises);

        void EliminarPais(int id);
       
        void imprimirPaises();
        
};
#endif
