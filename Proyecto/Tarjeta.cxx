#include "Tarjeta.h"

// Constructor
Tarjeta::Tarjeta(int id, const string& pais, const string& tipo)
    : id(id), pais(pais), tipo(tipo), estado(0) {
}

// Métodos para obtener los valores de los atributos
int Tarjeta::getID() const {
    return id;
}

string Tarjeta::getPais() const {
    return pais;
}

string Tarjeta::getTipo() const {
    return tipo;
}

// Métodos para establecer los valores de los atributos
void Tarjeta::setID(int newID) {
    id = newID;
}

void Tarjeta::setPais(const string& newPais) {
    pais = newPais;
}

void Tarjeta::setTipo(const string& newTipo) {
    tipo = newTipo;
}

// Método para obtener el estado de la tarjeta
int Tarjeta::getEstado() const {
    return estado;
}

// Método para establecer el estado de la tarjeta
void Tarjeta::setEstado(int newEstado) {
    estado = newEstado;
}

// Método para imprimir los datos de la tarjeta
void Tarjeta::imprimir() const {
    cout << id << ";" << pais << ";" << tipo << endl;
}
