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

Clase::Clase(int d)
{
    dato = d;
}

bool Clase::operator<(const Clase& otro) const
{
    return dato < otro.dato;
}


#endif
