//
// Created by epicg on 12/06/2024.
//

#ifndef VIAJEZUELANDIA_H
#define VIAJEZUELANDIA_H
#include "alg_grafoPMC.h"
#include "matriz.h"
#include "grafoPMC.h"
#include "alg_grafo_E-S.h"
#include <iostream>

/**
 *
 * @tparam tCoste tipo de coste
 * @param G mapa de zuelandia
 * @param ciudadesR ciudades tomadas por los rebeldes
 * @param carreterasR carreteras tomadas por los rebeldes
 * @param capital capital de Zuelandia
 * @return matriz de costes de viaje entre ciudades con la situacion actual
 */
template <typename tCoste>
matriz<tCoste> viajeZuelandia(const GrafoP<tCoste>& G, vector<typename GrafoP<tCoste>::vertice>& ciudadesR,
    vector<typename GrafoP<tCoste>::arista>& carreterasR, typename GrafoP<tCoste>::vertice capital)
{
    size_t N = G.numVert();
    matriz<tCoste> CostesTotales(N,GrafoP<tCoste>::INFINITO);
    GrafoP<tCoste> R(G); //copiamos grafo para actualizar la situacion de los rebeldes
    //ponemos las ciudades que han sido tomadas por los rebeldes como inaccesibles
    for(auto ciudad : ciudadesR)
    {
        R[ciudad] = vector<tCoste>(N,R.INFINITO); //todas las salidas de esa ciudad cortadas
        for(size_t i = 0; i < N; ++i)
            R[i][ciudad] = R.INFINITO; //todo jaja R.INFINITO lo resuelve porque es static y de la clase
    }

    for(auto c : carreterasR)
        R[c.orig][c.dest] = R.INFINITO; //se cortan las carreteras...

    vector<tCoste> CostesHaciaC, CostesDesdeC;
    vector<typename GrafoP<tCoste>::vertice> caminosOC, caminosCD; //vectores de vertices para Dij y Dij inverso
    CostesDesdeC = Dijkstra(R, capital, caminosCD);
    CostesHaciaC = DijkstraInv(R, capital, caminosOC);
    std::cout << "Coste hacia capital" << std::endl << CostesHaciaC << std::endl;
    std::cout << "Coste desde capital" << std::endl << CostesDesdeC << std::endl;

    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            if(i != j)
                CostesTotales[i][j] = suma(CostesHaciaC[i],CostesDesdeC[j]);
        }
    }
    return CostesTotales;
}

#endif //VIAJEZUELANDIA_H
