//
// Created by epicg on 12/06/2024.
//

#ifndef PRACTICA6_H
#define PRACTICA6_H
#include <iostream>

#include "alg_grafoPMC.h"
#include "grafoPMC.h"


template <typename tCoste>
void alejadosMax(matriz<tCoste>& M, typename GrafoP<tCoste>::vertice& v1,
    typename GrafoP<tCoste>::vertice& v2);

/**
 *
 * @tparam tCoste
 * @param origen vertice inicial del camino
 * @param distancias vector con distancias minimas. Salida de Dijkstra
 * @param P vector de ulitmo vertice para llegar a i
 * @return vector de tCamino tamaño G.numVert() con caminos a cada nodo, tCamino vacio si no es posible
 * Para CaminoInv de DijkstraInv devuelve camino alreves
 */
template <typename tCoste>
vector<typename GrafoP<tCoste>::tCamino> calcCaminos(typename GrafoP<tCoste>::vertice origen,
    vector<tCoste> distancias, vector<typename GrafoP<tCoste>::vertice>& P)
{
    vector<typename GrafoP<tCoste>::tCamino> caminos(P.size());

    for (typename GrafoP<tCoste>::vertice i = 0; i < P.size(); ++i)
    {
        if(distancias[i] != GrafoP<tCoste>::INFINITO)
        {
            caminos[i] = camino<tCoste>(origen,i,P);
        } else if ( origen == i )
        { //con esto diferencio entre camino posible, mismo vertice, y camino imposible
            typename GrafoP<tCoste>::tCamino aux = typename GrafoP<tCoste>::tCamino();
            aux.insertar(origen, aux.primera());
            caminos[i] = aux;
        } else caminos[i] = typename GrafoP<tCoste>::tCamino();

        std::cout << "camino desde " << origen <<  " hasta " << i << ": ";
        for (auto pos = caminos[i].primera(); pos != caminos[i].fin();
        pos = caminos[i].siguiente(pos))
        {
            std::cout << caminos[i].elemento(pos) << " ";
        }
        std::cout << std::endl;
    }
    return caminos;
}

/**
*Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que
minimiza la suma de las distancias mínimas a sus dos nodos más alejados. Definiremos
el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más
alejados del pseudocentro del grafo.
Dado un grafo conexo representado mediante matriz de costes, implementa un
subprograma que devuelva la longitud de su diámetro.
 * @tparam tCoste tipo de dato aristas
 * @param G grafo
 * @return longitud del diamtero
 */
template<typename tCoste>
tCoste pseudocentroMal(const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    size_t n = G.numVert();

    vertice pseudoCentro, v1 ,v2; //v1 y v2 más alejados
    matriz<vertice> mVertices(G.numVert()); //matriz de vertices

    matriz<tCoste> mDistancias = Floyd(G,mVertices);
    alejadosMax(mDistancias, v1, v2);
    std::cout << "matriz coste:\n" << mDistancias << std::endl;
    std::cout << "nodos mas alejados: " << v1 << " y " << v2 << std::endl;
    tCoste orig, dest, diametro = GrafoP<tCoste>::INFINITO;

    //pseudocentro -> ¿qué vertice w hace que v1 <- w -> v2 sea mínimo?
    for(size_t i = 0; i < n; ++i)
    {
        //if i != v1 && i != v2 ??? //todo pseudocentro puede ser uno de los nodos ¿? supongo que sí
        if( suma(G[i][v1] , G[i][v2] ) < diametro )
        {
            diametro = G[i][v1] + G[i][v2]; //la suma aquí es 'safe' ya que es menor a INF
            pseudoCentro = i;
        }
    }

    std::cout << "pseudocentro es: " << pseudoCentro << std::endl; //no se pide pero testing
    return diametro;

}

/**
 * funcion auxiliar calcula nodos mas alejados de matriz de costes por Floyd
 */
template <typename tCoste>
void alejadosMax(matriz<tCoste>& M, typename GrafoP<tCoste>::vertice& v1,
    typename GrafoP<tCoste>::vertice& v2)
{
    auto n = M.dimension();
    tCoste distancia = 0;
    for(size_t i = 0; i< n; ++i)
    {
        for(size_t j = i+1; j<n; ++j)
        {
            auto aux = suma(M[i][j], M[j][i]);
            if(aux != GrafoP<tCoste>::INFINITO && distancia < aux )
            {// si aux = INF no hay camino y no guardarlo (el grafo aun asi debe ser (fuertemente?)) conexo
                distancia = aux;
                v1 = i; v2 = j; //guarda los vertices que lo hacen posible
            }
        }
    }
}

template <typename tCoste>
tCoste pseudoCentro(const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    size_t N = G.numVert();

    matriz<vertice> mVertices(N); //matriz de vertices (para Floyd)
    matriz<tCoste> mCoste = Floyd(G, mVertices);
    tCoste v1, v2, diametro = GrafoP<tCoste>::INFINITO;
    vertice pseudo;
    std::cout << mCoste << std::endl;

    for(vertice i = 0; i < N; ++i)
    {
       v1= 0;
       v2= 0;
        for(vertice j = 0; j < N; ++j)
        {
            if(mCoste[i][j] >= v1)
            {
               v2 = v1;
               v1= mCoste[i][j];
            }
            else if(mCoste[i][j] >= v2)
               v2= mCoste[i][j];
        }
        if(diametro > v1+ v2)
        {
            diametro = v1 + v2;
            pseudo = i;
        }
    }
    std::cout << "Pseudocentro: " << pseudo << std::endl;
    return diametro;
}
#endif //PRACTICA6_H
