#include "../RTree.cpp"

#include <bits/stdc++.h>
using namespace std;

//archivos de salida
#define SALIDA_PUNTOS "puntos_encontrados.csv"
#define SALIDA_LECTURAS "lecturas_disco.csv"
//macro para escribir lo mismo en ambos archivos


vector<float> tamaños = {0.0025f, 0.005f, 0.01f, 0.025f, 0.05f};

ofstream puntos(SALIDA_PUNTOS);
ofstream lecturas(SALIDA_LECTURAS);

void procesar(string nombre, int seed) {
    for(float s : tamaños){
        RTree arbol(nombre + ".bin");
        vector<QueryResult> q = arbol.QueryS(s, seed);
        unsigned int p = 0;
        unsigned int d = 0;
        puntos << nombre << '[' << s << ']';
        lecturas << nombre << '[' << s << ']';
        for (QueryResult &r : q) {
            p += r.puntos;
            d += r.diskreads;
            puntos<<';'<<r.puntos;
            lecturas<<';'<<r.diskreads;
        }
        cout << '[' << nombre << ']' << " Tamaño: " << s << " Puntos encontrados: " << p << " I/Os: " << d << endl;
        puntos << endl;
        lecturas << endl;
    }
}


int main() {
    procesar("EuropaSTR",1);
    procesar("EuropaNX",42);
    procesar("RandomSTR",88523);
    procesar("RandomNX",998244353);

    puntos.close();
    lecturas.close();

    cout<<"Resultados guardados en "<<SALIDA_PUNTOS<<" y "<<SALIDA_LECTURAS<<endl;
    
    return 0;
}