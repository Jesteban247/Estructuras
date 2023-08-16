#ifndef Trabajo_H
#define Trabajo_H

class Trabajo
{
    private:
        unsigned int identificador;

    public:
        Trabajo();
        Trabajo(unsigned int identificador);

        unsigned int getIdentificador();
        void setIdentificador(unsigned int identificador);
};


#endif