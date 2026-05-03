#include "config.hp"
#include "headers.h"
#include "RandomSquare.h"

std::vector<QuerySquare> generarCuadrados(float s, int n, int seed){

    std::vector<QuerySquare> resultado;
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0 - s);

    for(int i = 0; i < n; i++){
        float x = dist(rng);
        float y = dist(rng);
        resultado.push_back({x, y, x + s, y + s});
    }

    return resultado;

}
