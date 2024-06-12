#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include <fstream>
#include <vector>
#include <filesystem>
#include "grafoPMC.h"
#include <clocale>
#include <codecvt>
#include <fcntl.h>

//prueba de creacion DAT
void createTextDatFile(const std::string& filename);

GrafoP<unsigned>::tCamino
micamino(GrafoP<unsigned>::vertice orig, GrafoP<unsigned>::vertice v,
       const vector<GrafoP<unsigned>::vertice>& P)
// Devuelve el camino de coste mínimo entre los vértices orig e v
// a partir de un vector P obtenido mediante la función Dijkstra().
{
    GrafoP<unsigned>::tCamino C;

    C.insertar(v, C.primera());
    do {
        C.insertar(P[v], C.primera());
        v = P[v];
    } while (v != orig);
    return C;
}


int main() {
    //typedef typename GrafoP<unsigned >::vertice vertice;
    using namespace std;
    setlocale(LC_ALL, "spanish");

    /**
     * Añade '../' a cada fichero ya que la llamada la hace Cmake desde la carpeta cmake-build-debug
     */
    GrafoP<unsigned> Gcarreteras("../entradaGrafo.dat");
    vector<typename GrafoP<unsigned>::vertice> rutas;

    cout << Gcarreteras << endl;
    vector<unsigned> distancias = Dijkstra(Gcarreteras,0,rutas );

    cout << "Distancias mínimas a cada vértice: " << distancias << endl;
    cout << "Rutas a seguir: " << rutas << endl;

    vector<GrafoP<unsigned>::tCamino> caminos(distancias.size());

    GrafoP<unsigned>::vertice dest = 1;

    //GrafoP<unsigned>::tCamino c = camino<unsigned>(0, 1, rutas);
    for (GrafoP<unsigned>::vertice i = 0; i < Gcarreteras.numVert(); i++)
    {
        caminos[i] = camino<unsigned>(0,i,rutas);
        cout << "camino desde origen hasta " << i << ": ";
        for (auto pos = caminos[i].primera(); pos != caminos[i].fin();
        pos = caminos[i].siguiente(pos))
        {
            cout << caminos[i].elemento(pos) << " ";
        }
        cout << endl;
    }



    //cout <<  << endl;

    return 0;
}





void createTextDatFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to create file " << filename << std::endl;
        return;
    }

    // Example text data
    unsigned n = 3;
    std::vector<std::vector<int>> costes = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    // Write the number of vertices
    outFile << n << std::endl;

    // Write the matrix data
    for (const auto& row : costes) {
        for (const auto& value : row) {
            outFile << value << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
    // Get the absolute path of the file
    std::filesystem::path filePath = std::filesystem::absolute(filename);
    std::cout << "Binary .dat file created successfully: " << filePath << std::endl;
}




//codigo antiguo
void pruebaMatriz0()
{
    //ejercicio 1
    vector<vector<int>> matrix;
    // Initialize the vector of vectors with values
    matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    matriz<int> viajes(4, INT_MAX);
    for(size_t i = 0; i < viajes.dimension(); ++i)
    {
        for(size_t j = 0; j < viajes.dimension(); ++j)
        {
            std::cin >> viajes[i][j];
        }
    }
    for(size_t i = 0; i < viajes.dimension(); ++i)
    {
        for(size_t j = 0; j < viajes.dimension(); ++j)
        {
            std::cout << viajes[i][j] << " ";
        }
        std::cout << std::endl;
    }
}