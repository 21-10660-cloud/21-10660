#include "KMeans.h"
#include <cmath>
#include <limits>

double calcularDistancia(const Coord_3D& a, const Coord_3D& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2));
}

/*
 * CONDICION DE PARADA DEL PROGRAMA
 * Parametros:
 * - centroidesAntiguos: La posicion de los centroides en la iteracion anterior.
 * - centroidesNuevos: La posicion de los centroides en la iteracion actual.
 * - umbral: Tolerancia de movimiento (0.0001).
 * * ¿Por que es una buena condicion?
 * Esta condicion evalua si los centroides han dejado de moverse de forma significativa en el espacio 3D. 
 * Si la distancia que se mueve cada centroide entre una iteracion y otra es menor a un umbral microscopico, 
 * significa que los grupos han alcanzado un estado de equilibrio (convergencia) y seguir iterando 
 * seria un gasto incesario de computo.
 */
bool condicionParada(const std::vector<Coord_3D>& centroidesAntiguos, const std::vector<Coord_3D>& centroidesNuevos, double umbral = 0.0001) {
    for (size_t i = 0; i < centroidesAntiguos.size(); ++i) {
        if (calcularDistancia(centroidesAntiguos[i], centroidesNuevos[i]) > umbral) {
            return false; 
        }
    }
    return true; 
}

void ejecutarKMeans(int k, const std::vector<Coord_3D>& datos, std::vector<Labeled>& clasificados, std::vector<Coord_3D>& centroides, std::vector<double>& dispersiones) {
    centroides.clear();
    for (int i = 0; i < k; ++i) {
        centroides.push_back(datos[i % datos.size()]);
    }

    std::vector<int> asignaciones(datos.size(), 0);
    bool finalizado = false;

    while (!finalizado) {
        for (size_t i = 0; i < datos.size(); ++i) {
            double minDist = std::numeric_limits<double>::max();
            int mejorCluster = 0;
            for (int c = 0; c < k; ++c) {
                double dist = calcularDistancia(datos[i], centroides[c]);
                if (dist < minDist) {
                    minDist = dist;
                    mejorCluster = c;
                }
            }
            asignaciones[i] = mejorCluster;
        }

        std::vector<Coord_3D> nuevosCentroides(k, {0.0, 0.0, 0.0});
        std::vector<int> conteo(k, 0);

        for (size_t i = 0; i < datos.size(); ++i) {
            int c = asignaciones[i];
            nuevosCentroides[c].x += datos[i].x;
            nuevosCentroides[c].y += datos[i].y;
            nuevosCentroides[c].z += datos[i].z;
            conteo[c]++;
        }

        for (int c = 0; c < k; ++c) {
            if (conteo[c] > 0) {
                nuevosCentroides[c].x /= conteo[c];
                nuevosCentroides[c].y /= conteo[c];
                nuevosCentroides[c].z /= conteo[c];
            }
        }

        finalizado = condicionParada(centroides, nuevosCentroides);
        centroides = nuevosCentroides;
    }

    clasificados.clear();
    dispersiones.assign(k, 0.0);
    std::vector<int> conteosFinales(k, 0);

    for (size_t i = 0; i < datos.size(); ++i) {
        int c = asignaciones[i];
        Labeled p;
        p.coord = datos[i];
        p.label = 'A' + c; 
        clasificados.push_back(p);
        dispersiones[c] += calcularDistancia(datos[i], centroides[c]);
        conteosFinales[c]++;
    }

    for (int c = 0; c < k; ++c) {
        if (conteosFinales[c] > 0) {
            dispersiones[c] /= conteosFinales[c];
        }
    }
}