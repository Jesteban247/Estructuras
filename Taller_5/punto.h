#ifndef punto_H
#define punto_H

#include <iostream>
#include <string>

class Punto {
public:
    double x;
    double y;
    string id;

    Punto(double x, double y, string id) : x(x), y(y) , id(id) {}
};


#endif
