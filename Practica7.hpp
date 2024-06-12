//
// Created by epicg on 29/04/2024.
//

#ifndef GRAFOS_PRACTICA7_HPP
#define GRAFOS_PRACTICA7_HPP

//#include "matriz.h"
#include "alg_grafo_E-S.h"

//EJERCICIO 1. AntiFloyd y coger el camino más largo?
//claro es aciclico porque sino podriamos ir al infinito
//aunque podrias recibir restriccion de no pasar por el mismo bue
/**
 * Recibe: Matriz de costes directos
 */
template <typename tCoste>
matriz<tCoste> antiFloyd(const GrafoP<tCoste>& G,
                         matriz<typename GrafoP<tCoste>::vertice>& P);


//no tengo idea de qué es esto

#endif //GRAFOS_PRACTICA7_HPP
