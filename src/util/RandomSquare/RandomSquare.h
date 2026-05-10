#ifndef RANDOMSQUARE_H
#define RANDOMSQUARE_H
#include "../../config.hp"

/**
 * Genera una cantidad de cuadrados de tamaño dado aleatoriamente para realizar consultas
 * en RTrees normalizados, es decir, asegura que los puntos estén entre los valores 0 y 1
 * para cada eje y en cada cuadrado.
 * @param s Tamaño del cuadrado a generar.
 * @param n Cantidad de cuadrados a generar.
 * @param seed Semilla de aleatoriedad para la generación de puntos.
 * @return Vector con n cuadrados generados aleatoriamente, con tamaño s y coordenadas entre 0 y 1.
 */
std::vector<QuerySquare> generarCuadrados(float s, int n, int seed);
#endif // RANDOMSQUARE_H
