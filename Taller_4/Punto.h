#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>
#include <string>

struct punto {
    std::string nombre;
    float x;
    int y;
    
    punto& operator=(const punto& p) {
        nombre = p.nombre;
        x = p.x;
        y = p.y;
        return *this;
    }

    bool operator==(const punto& p) const {
        return (x == p.x && y == p.y);
    }

    friend std::ostream& operator<<(std::ostream& o, const punto& p) {
        o << "Fruta: " << p.nombre << " (" << p.x << "," << p.y << ")";
        return o;
    }
};

#endif // PUNTO_H
