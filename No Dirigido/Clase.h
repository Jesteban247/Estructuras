#ifndef Clase_H
#define NODO_H

class Clase 
{
    private:
        //Atributos
        int dato;
    public:
        //Constructor
        Clase(int d);
        //Comparador
        bool operator<(const Clase& otro) const;
};

// Constructor de la clase Clase
Clase::Clase(int d)
{
    dato = d;
}

// Sobrecarga del operador < para comparar objetos de la clase Clase
bool Clase::operator<(const Clase& otro) const
{
    return dato < otro.dato;
}


#endif
