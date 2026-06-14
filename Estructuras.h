#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct Coord_3D {
    double x;
    double y;
    double z;
};

struct Labeled {
    Coord_3D coord;
    char label;
};

#endif