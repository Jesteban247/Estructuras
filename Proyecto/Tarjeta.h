#ifndef TARJETA_H
#define TARJETA_H

#include <iostream>
#include <string>
using namespace std;

class Tarjeta {
private:
    int id;
    string pais;
    string tipo;
    int estado;

public:
    // Constructor
    Tarjeta(int id, const string& pais, const string& tipo);

    // Métodos para obtener los valores de los atributos
    int getID() const;
    string getPais() const;
    string getTipo() const;

    // Métodos para establecer los valores de los atributos
    void setID(int newID);
    void setPais(const string& newPais);
    void setTipo(const string& newTipo);

    // Método para obtener el estado de la tarjeta
    int getEstado() const;

    // Método para establecer el estado de la tarjeta
    void setEstado(int newEstado);

    // Método para imprimir los datos de la tarjeta
    void imprimir() const;
};

#endif // TARJETA_H
