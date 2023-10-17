#include "Jugador.h"

        Jugador::Jugador(string nombre, int turno, int ejercitos)
        {
            this->nombre = nombre;
            this->turno = turno;
            this->ejercitos = ejercitos;
        }
        
        string Jugador::getNombre()
        {
            return nombre;
        }

        int Jugador::getTurno()
        {
            return turno;
        }

        void Jugador::setTurno(int turno)
        {
            this->turno = turno;
        }

        int Jugador::getEjercitos()
        {
            return ejercitos;
        }

        void Jugador::setEjercitos(int ejercitos)
        {
            this->ejercitos = ejercitos;
        }
        int Jugador::getDado()
        {
            return dado;
        }
        void Jugador::setDado(int dado)
        {
            this->dado = dado;
        }

        void Jugador::agregarPais(int id, int ejercitos)
        {
            paises[id] = ejercitos;
        }

        map<int, int> Jugador::getPaises()
        {
            return paises;
        }
    
        void Jugador::setPaises(map<int, int> paises)
        {
            this->paises = paises;
        }

        void Jugador::EliminarPais(int id)
        {
            paises.erase(id);
        }

        void Jugador::imprimirPaises()
        {
            for (auto it = paises.begin(); it != paises.end(); it++)
            {
                cout << it->first << ",";
            }
            cout << endl;
        }

        void Jugador::agregarTarjeta(int id)
        {
            Tarjetas.insert(id);
        }

        void Jugador::eliminarTarjeta(int id)
        {
            Tarjetas.erase(id);
        }

        set<int> Jugador::getTarjetas()
        {
            return Tarjetas;
        }
