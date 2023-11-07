#ifndef punto_H
#define punto_H

#include <string>

class Punto {
public:
    double x;
    double y;
    std::string id;

    Punto(double x, double y, std::string id);
};


Punto::Punto(double x, double y, std::string id) : x(x), y(y), id(id) {}


#endif
