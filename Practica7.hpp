//
// Created by epicg on 29/04/2024.
//

#ifndef GRAFOS_PRACTICA7_HPP
#define GRAFOS_PRACTICA7_HPP

//#include "matriz.h"
#include "grafoPMC.h"
#include "alg_grafo_E-S.h"

template <typename tCoste>
struct Viaje
{
    typedef typename GrafoP<tCoste>::vertice vertice;


    typename GrafoP<tCoste>::vertice origen, destino;
    tCoste coste;

    explicit Viaje(vertice v = vertice(), vertice w = vertice(),
                tCoste c = tCoste()): origen(v), destino(w), coste(c) {}
};

template <typename tCoste>
tCoste miMax(tCoste a, tCoste b, tCoste INF)
{
    if (a==INF)
        return b;
    else if (b==INF)
        return a;
    else return std::max(a, b);
}

//EJERCICIO 1. AntiFloyd y coger el camino más largo?
//claro es aciclico porque sino podriamos ir al infinito
//aunque podrias recibir restriccion de no pasar por el mismo bue
/**
 * Recibe: Matriz de costes directos
 */
template <typename tCoste>
matriz<tCoste> antiFloyd(const GrafoP<tCoste>& G,
                         matriz<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    const size_t n = G.numVert();
    matriz<tCoste> A(n);   // matriz de costes mínimos

    // Iniciar A y P con caminos directos entre cada par de vértices.
    P = matriz<vertice>(n);
    for (vertice i = 0; i < n; i++) {
        A[i] = G[i];                    // copia costes del grafo
        A[i][i] = INFINITO;                    // diagonal a INFIN
        P[i] = vector<vertice>(n, i);   // caminos directos
    }
    // Calcular costes mínimos y caminos correspondientes
    // entre cualquier par de vértices i, j
    for (vertice k = 0; k < n; k++)
        for (vertice i = 0; i < n; i++)
            for (vertice j = 0; j < n; j++) {
                tCoste ikj = suma(A[i][k], A[k][j]);
                //if ( ikj <= A[i][j]) {
                    A[i][j] = miMax(ikj,A[i][j],INFINITO);
                    P[i][j] = k; //todo matriz P estara bien?
                //}
            }
    return A;
}

Viaje<unsigned> viajeMasCaro(const GrafoP<unsigned> &G)
{
    typedef GrafoP<unsigned>::vertice vertice;
    size_t N = G.numVert();

    //inicializamos viaje y matriz P
    Viaje<unsigned> viaje;
    matriz<GrafoP<unsigned>::vertice> P;

    matriz<unsigned> Costes = antiFloyd(G,P);

    for( vertice v = 0; v < N; ++v){
        for(vertice w = 0; w < N; ++w)
        {
            if(Costes[v][w] != GrafoP<unsigned>::INFINITO && viaje.coste < Costes[v][w])
            {
                viaje.origen = v;
                viaje.destino = w;
                viaje.coste = Costes[v][w];
            }
        }
    }

    return viaje;
}



#endif //GRAFOS_PRACTICA7_HPP
