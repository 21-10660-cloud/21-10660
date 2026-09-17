#include "Tablero.h"
#include <iostream>

int main() {
    int f, c;
    std::cout << "--- Calculadora de Rutas Combinatorias ---\n";
    std::cout << "Ingrese el numero de filas: ";
    std::cin >> f;
    std::cout << "Ingrese el numero de columnas: ";
    std::cin >> c;

    if (f < 1 || c < 1) {
        std::cout << "Las dimensiones deben ser mayores a 0.\n";
        return 1;
    }

    Tablero t(f, c);
    t.dibujar();

    // Los indices matematicos van de 0 a N-1
    long long rutas = t.calcularRutas(f - 1, c - 1);
    std::cout << "Numero de rutas unicas posibles para la pieza: " << rutas << "\n";
    std::cout << "(Resolucion basada en teoria de grafos)\n";

    return 0;
}