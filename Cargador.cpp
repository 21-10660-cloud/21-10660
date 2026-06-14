#include "Cargador.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Coord_3D> cargarDatos(const std::string& nombreArchivo) {
    std::vector<Coord_3D> datos;
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de datos.\n";
        return datos;
    }

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string valor;
        Coord_3D p = {0.0, 0.0, 0.0};
        
        if (std::getline(ss, valor, ',')) p.x = std::stod(valor);
        if (std::getline(ss, valor, ',')) p.y = std::stod(valor);
        if (std::getline(ss, valor, ',')) p.z = std::stod(valor);
        
        datos.push_back(p);
    }
    return datos;
}