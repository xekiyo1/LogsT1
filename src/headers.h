#ifndef HEADERS_H
#define HEADERS_H
#include <bits/stdc++.h>
using namespace std;

/**
 * Estructura auxiliar que busca empaquetar los puntos encontrados en una
 * consulta de RTree, y las lecturas a disco que fueron necesarias para ello.
 */
struct QueryResult{
    /// Cantidad de puntos obtenida por la consulta de RTree.
    int puntos;
    /// Cantidad de lecturas a disco realizadas en la lectura realizada de RTree.
    int diskreads;
};

#include "./RTreeConstructors/RTreeConstructor.h"
#include "util/calcTime/calcTime.h"


#endif