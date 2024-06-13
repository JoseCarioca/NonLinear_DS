//
// Created by epicg on 13/06/2024.
//

#ifndef LABERINTO_H
#define LABERINTO_H
#include <iostream>

#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

struct casilla
{
    unsigned fila, columna;
    explicit casilla(unsigned f = 0, unsigned c = 0): fila(f), columna(c) {}
};

bool sonAdyacentes(casilla c1, casilla c2) {
    return ( abs(static_cast<int>(c1.fila - c2.fila)) + abs(static_cast<int>(c1.columna - c2.columna)) == 1 );
}


struct pared
{
    casilla c1, c2;
    pared(const casilla& c1, const casilla& c2) : c1(c1), c2(c2){
        if (sonAdyacentes(c1, c2)) {
        } else {
            throw std::invalid_argument("No es una pared. Las casillas no son adyacentes.");
        }
    }

};



typedef GrafoP<unsigned>::vertice nodo;
typedef vector<casilla> miCamino;

casilla nodo2casilla(nodo nodo, unsigned TAM)
{
    unsigned fila, col;

    fila = nodo / TAM;
    col = nodo % TAM;

    return casilla(fila, col);

}

nodo casilla2nodo(casilla c, unsigned TAM)
{
    nodo nodo =  c.fila * TAM + c.columna;
    return nodo;
}

miCamino laberinto(size_t N, vector<pared> paredes, casilla E, casilla S)
{
    GrafoP<unsigned> Laberinto(N*N);
    size_t TAM = Laberinto.numVert(); //tam es numero de vertices para recorrer grafo
    nodo entrada = casilla2nodo(E,N); //para calcular camino despues
    nodo salida = casilla2nodo(S,N);
    miCamino solucion; //inicializo camino para solucion

    for(size_t i = 0; i < TAM; ++i)
    {
        Laberinto[i][i] = 0;
        for(size_t j = i+1; j < TAM; ++j)
        {
            if( sonAdyacentes(nodo2casilla(i,N),nodo2casilla(j,N)) )
            {
                Laberinto[i][j] = 1;
                Laberinto[j][i] = 1;
            }
        }
    }

    for(const pared pared : paredes)
    {
        nodo i, j;
        i = casilla2nodo(pared.c1,N);
        j = casilla2nodo(pared.c2,N);
        Laberinto[i][j] = GrafoP<unsigned>::INFINITO;
        Laberinto[j][i] = GrafoP<unsigned>::INFINITO;
    }

    std::cout << Laberinto << std::endl;

    vector<GrafoP<unsigned>::vertice> P(TAM);
    //calculamos camino desde origen
    vector<unsigned> Pasos = Dijkstra(Laberinto, entrada, P);
    std::cout << P << std::endl;

    //ahora devolvemos la sucesion de caminos casillas
    size_t i = salida;
    while( i != entrada)
    {
        casilla c = casilla(nodo2casilla(i,N));
        solucion.insert(solucion.begin(), c);
        i = P[i];
    }
    solucion.insert(solucion.begin(), casilla(nodo2casilla(entrada,N)) ); //metemos la casilla de entrada
    return solucion;
}
#endif //LABERINTO_H
