#include "Tablero.h"
#include <iostream>

Tablero::Tablero(int f, int c) : filas(f), columnas(c) {}

void Tablero::dibujar() {
    std::cout << "\nTablero " << filas << "x" << columnas << ":\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == 0 && j == 0) std::cout << "[ R ] ";
            else if (i == filas - 1 && j == columnas - 1) std::cout << "[ X ] ";
            else std::cout << "[ . ] ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

long long Tablero::calcularRutas(int x, int y) {
    // Condicion de parada: si llegamos al borde superior o izquierdo
    if (x == 0 || y == 0) return 1;
    // Recursion: rutas desde arriba + rutas desde la izquierda
    return calcularRutas(x - 1, y) + calcularRutas(x, y - 1);
}