//
// Created by epicg on 12/06/2024.
//

#ifndef PEROOTRAVEZUNGRAFO_H
#define PEROOTRAVEZUNGRAFO_H
#include "grafoPMC.h"
#include "matriz.h"

/**
 *
 * @return devuelve true si el grafo es acíclico
 */
template <typename tCoste>
bool aciclico(const GrafoP<tCoste>& G)
//Floyd modificado con diagonal a INF para comprobar ciclos
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    matriz<tCoste> A(n);   // matriz de costes mínimos
    bool aciclico = true;

    // Iniciar A con caminos directos entre cada par de vértices.
    for (vertice i = 0; i < n; i++)
    {
        A[i] = G[i];                    // copia costes del grafo
        A[i][i] = GrafoP<tCoste>::INFINITO;                    // diagonal a 0
    }

      // Calcular costes mínimos
      // entre cualquier par de vértices i, j
      for (vertice k = 0;  k < n; k++)
      {
          for (vertice i = 0; i < n; i++)
          {
              for (vertice j = 0; aciclico && j < n; j++)
              {
                  tCoste ikj = suma(A[i][k], A[k][j]);
                  if (ikj < A[i][j])
                  {
                      if( i == j) aciclico = false; // si existe camino de i a i es que es cíclico
                      A[i][j] = ikj; //no se si hace falta ir actualizando
                  }
              }
          }
      }

    return aciclico;
}

#endif //PEROOTRAVEZUNGRAFO_H
