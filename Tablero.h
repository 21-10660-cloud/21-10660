#ifndef TABLERO_H
#define TABLERO_H
class Tablero {
private:
    int filas;
    int columnas;
public:
    Tablero(int f, int c);
    void dibujar();
    long long calcularRutas(int x, int y);
};
#endif