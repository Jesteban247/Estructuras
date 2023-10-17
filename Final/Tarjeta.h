#ifndef Tarjeta_H
#define Tarjeta_H

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
    Tarjeta(int id, const string& pais, const string& tipo)
        : id(id), pais(pais), tipo(tipo), estado(0) {
    }

    // Métodos para obtener los valores de los atributos
    int getID() const {
        return id;
    }

    string getPais() const {
        return pais;
    }

    string getTipo() const {
        return tipo;
    }

    // Métodos para establecer los valores de los atributos
    void setID(int newID) {
        id = newID;
    }

    void setPais(const string& newPais) {
        pais = newPais;
    }

    void setTipo(const string& newTipo) {
        tipo = newTipo;
    }

    // Método para obtener el estado de la tarjeta
    int getEstado() const {
        return estado;
    }

    // Método para establecer el estado de la tarjeta
    void setEstado(int newEstado) {
        estado = newEstado;
    }

    // Método para imprimir los datos de la tarjeta
    void imprimir() const {
        cout << id << ";" << pais << ";" << tipo << endl;
    }
};

#endif
