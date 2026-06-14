#ifndef KMEANS_H
#define KMEANS_H
#include "Estructuras.h"
#include <vector>

void ejecutarKMeans(int k, const std::vector<Coord_3D>& datos, std::vector<Labeled>& clasificados, std::vector<Coord_3D>& centroides, std::vector<double>& dispersiones);

#endif