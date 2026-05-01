#include "RTree.cpp"


#include <bits/stdc++.h>
using namespace std;

vector<float> tamaños = {0.0025f, 0.005f, 0.01f, 0.025f, 0.05f};

int main() {
    for(float s : tamaños){
        RTree arbol("arbolitoSTR.bin");
        RTree::QueryResult q = arbol.QueryS(s, 1);
        cout << "Tamaño: " << s << " Puntos encontrados: " << q.puntos << " I/Os: " << q.diskreads << endl;
    }

    for(float s : tamaños){
        RTree arbol("arbolitoNearestX.bin");
        RTree::QueryResult q = arbol.QueryS(s, 42);
        cout << "Tamaño: " << s << " Puntos encontrados: " << q.puntos << " I/Os: " << q.diskreads << endl;
    }
    
    return 0;
}