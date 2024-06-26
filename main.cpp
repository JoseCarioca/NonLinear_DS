#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include <fstream>
#include <vector>
#include <filesystem>
#include "grafoPMC.h"
#include <clocale>

#include "peroOtraVezUnGrafo.h"
#include "practica6.h"
#include "Practica7.hpp"
#include "viajeZuelandia.h"

#include "laberinto.h"


//prueba de creacion DAT
void createTextDatFile(const std::string& filename);

//EJECUCION PRUEBA + EJER 1 (DIJKSTRAINV)
void ejer0y1();
//ejecucion ejercicio 2: pseudocentro
void ejer2();
//ejecucion ejercicio 3: aciclico
void ejer3();
//void ejer4 zuelandia
void ejer4();

//practica 7

void p7ejer1(); //antiFloyd o FloydMax

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

    if (false) ejer0y1();
    if (false) ejer2();
    if (false) ejer3();
    if (false) ejer4();

    //p7ejer1();
    casilla entrada = casilla(0,0);
    casilla salida = casilla(2,0);

    vector<pared> paredes;
    paredes.push_back(pared(casilla(0,0), casilla(1,0)));
    paredes.push_back(pared(casilla(1,0), casilla(1,1)));
    paredes.push_back(pared(casilla(0,1), casilla(1,1)));

    miCamino solucion = laberinto(3, paredes, entrada, salida);
    for (auto paso: solucion)
    {
        std::cout << "["  << paso.fila << ", " <<paso.columna << "]" " , ";
    }

    return 0;
}

void p7ejer1()
{
    std::cout <<"max: " << std::numeric_limits<unsigned>::max() << std::endl;
    std::cout <<"max: " << std::numeric_limits<size_t>::max() << std::endl;
    GrafoP<unsigned>Viajes("../entradaGrafo.dat");
    std::cout << Viajes << std::endl;
    Viaje<unsigned> viajeCaro = viajeMasCaro(Viajes);
    std::cout << "Precio: " <<viajeCaro.coste << std::endl;
    std::cout << "Origen: " <<viajeCaro.origen << std::endl;
    std::cout << "Destino: " <<viajeCaro.destino << std::endl;
}


void ejer4()
{

    GrafoP<unsigned>Mapa ("../zuelandia.dat");
    //secuancia de ciudades tomadas por rebeldes:
    vector<GrafoP<unsigned>::vertice> ciudades_tomadas{3};
    GrafoP<unsigned>::arista a(2,5),b(2,4);
    vector<GrafoP<unsigned>::arista> carreteras_tomadas{a,b};
    unsigned capital = 2;
    matriz<unsigned> NuevoMapa = viajeZuelandia(Mapa,ciudades_tomadas,carreteras_tomadas,capital);
    std::cout << "Nueva situacion en Zuelandia:\n" << NuevoMapa << std::endl;
}

void ejer3()
{
    GrafoP<unsigned> Grafociclo("../pseudoCentro.dat");
    std::cout << "El grafo:\n"<< Grafociclo << std::endl;
    if( aciclico(Grafociclo) )
    {
        std::cout << "Es aciclico"<< std::endl;
    }else std::cout << "No es aciclico"<< std::endl;

    GrafoP<unsigned> GrafoA("../entradaGrafo.dat");
    std::cout << "El grafo:\n"<< GrafoA << std::endl;
    if( aciclico(GrafoA) )
    {
        std::cout << "Es aciclico"<< std::endl;
    }else std::cout << "No es aciclico"<< std::endl;
}


void ejer2()
{
    GrafoP<unsigned> Grafopseudo("../pseudoCentro.dat");
    std::cout << Grafopseudo << std::endl;

    unsigned diametro = pseudoCentro(Grafopseudo);
    std::cout << "Diametro del grafo: " << diametro << std::endl;
}


void ejer0y1()
{
    using namespace std;

    /**
     * Añade '../' a cada fichero ya que la llamada la hace Cmake desde la carpeta cmake-build-debug
     */
    GrafoP<unsigned> Gcarreteras("../entradaGrafo.dat");
    vector<typename GrafoP<unsigned>::vertice> rutas;
    GrafoP<unsigned>::vertice origen = 1;

    cout << Gcarreteras << endl;
    vector<unsigned> distancias = Dijkstra(Gcarreteras,origen,rutas );

    cout << "Distancias mínimas a cada vértice: " << distancias << endl;
    cout << "Rutas a seguir: " << rutas << endl;

    vector<GrafoP<unsigned>::tCamino> caminos = calcCaminos<unsigned>(origen, distancias, rutas);

    //Prueba Dijkstra Inverso
    GrafoP<unsigned>::vertice destino = 5;
    vector<GrafoP<unsigned>::vertice> pInv;
    vector<unsigned> dInv = DijkstraInv(Gcarreteras,destino,pInv );

    cout << "Dist min de cada vertice a destino: " << dInv << endl;
    cout << "Rutas a seguir: " << pInv << endl;

    vector<GrafoP<unsigned>::tCamino> caminosInv = calcCaminos<unsigned>(destino, dInv, pInv);


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