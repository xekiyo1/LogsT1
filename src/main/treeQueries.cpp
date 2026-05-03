#include "RTree.cpp"


#include <bits/stdc++.h>
using namespace std;

//archivos de salida
#define SALIDA_PUNTOS "puntos_encontrados.csv"
#define SALIDA_LECTURAS "lecturas_disco.csv"
//macro para escribir lo mismo en ambos archivos
#define escribir(x); puntos<<x;lecturas<<x;

vector<float> tamaños = {0.0025f, 0.005f, 0.01f, 0.025f, 0.05f};


int main() {
    ofstream puntos(SALIDA_PUNTOS);
    ofstream lecturas(SALIDA_PUNTOS);

    escribir("Cuadrado");
    for(float s : tamaños){ escribir(';'<<s); }
    escribir('\n');

    escribir("STR");
    for(float s : tamaños){
        RTree arbol("arbolitoSTR.bin");
        RTree::QueryResult q = arbol.QueryS(s, 1);
        cout << "Tamaño: " << s << " Puntos encontrados: " << q.puntos << " I/Os: " << q.diskreads << endl;

        puntos<<';'<<q.puntos;
        lecturas<<';'<<q.diskreads;
    }

    escribir('\n');

    escribir("NearestX");
    for(float s : tamaños){
        RTree arbol("arbolitoNearestX.bin");
        RTree::QueryResult q = arbol.QueryS(s, 42);
        cout << "Tamaño: " << s << " Puntos encontrados: " << q.puntos << " I/Os: " << q.diskreads << endl;

        escribir(';');
        puntos<<q.puntos;
        lecturas<<q.diskreads;
    }

    puntos.close();
    lecturas.close();

    cout<<"Resultados guardados en "<<SALIDA_PUNTOS<<" y "<<SALIDA_LECTURAS<<endl;
    
    return 0;
}