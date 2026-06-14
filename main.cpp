#include "Estructuras.h"
#include "Cargador.h"
#include "KMeans.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
    // Verificar invocacion: cluster <k> <datos>
    if (argc != 3) {
        std::cerr << "Uso: cluster <k> <datos>\n";
        return 1;
    }

    int k = std::atoi(argv[1]);
    std::string archivoDatos = argv[2];

    if (k < 1 || k > 6) {
        std::cerr << "El numero de clusters (k) debe estar entre 1 y 6.\n";
        return 1;
    }

    // 1. Carga de datos
    std::vector<Coord_3D> datos = cargarDatos(archivoDatos);
    if (datos.empty()) return 1;

    // 2. Ejecutar Algoritmo
    std::vector<Labeled> clasificados;
    std::vector<Coord_3D> centroides;
    std::vector<double> dispersiones;
    ejecutarKMeans(k, datos, clasificados, centroides, dispersiones);

    // 3. Generar clasificados.csv
    std::ofstream outClasificados("clasificados.csv");
    for (const auto& p : clasificados) {
        outClasificados << p.coord.x << "," << p.coord.y << "," << p.coord.z << "," << p.label << "\n";
    }
    outClasificados.close();

    // 4. Generar summary.txt
    std::ofstream outSummary("summary.txt");
    std::vector<int> conteoPuntos(k, 0);
    for (const auto& p : clasificados) {
        conteoPuntos[p.label - 'A']++;
    }

    for (int i = 0; i < k; ++i) {
        char label = 'A' + i;
        outSummary << label << ": " << conteoPuntos[i] << ", (" 
                   << centroides[i].x << ", " << centroides[i].y << ", " << centroides[i].z 
                   << "), " << dispersiones[i] << "\n";
    }
    outSummary.close();

    std::cout << "Clasificacion finalizada. Revisa clasificados.csv y summary.txt\n";
    return 0;
}