#include "../headers.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <fstream>
using namespace std;

/// Archivo .csv en el que se guardan los tiempos medidos
#define SALIDA "tiemposCreacion.csv"
/// Dirección donde se almacenan los archivos binarios de puntos
const string BIN_PATH = "bin/data/";
/// Dirección donde se guardarán los árboles creados
const string OUT_PATH = "bin/trees/";

/// Creador de árboles NearestX, instancia de NearestXConstructor
NearestXConstructor NearestX;
/// Creador de árboles STR, instancia de STRConstructor
STRConstructor STR;
/// Timer para medir el tiempo de creación
HPTimer tim;

/**
 * Recibe los resultados de la iteración al crear un cierto tipo de RTree con un archivo específico y
 * los muestra en consola, a la vez que los guarda a un archivo.
 * @param xs Vector de resultados en nanosegundos para cada iteración.
 * @param file Archivo en el que se escribirán los resultados (formato .csv)
 * @param name Nombre del árbol que se utilizará para la fila del archivo.
 */
void showResults(vector<long long> &xs, ofstream &file, string name){
    cout<<"Tiempos de construcción "<<name<<':'<<endl;
    file<<name<<';';

    for(long long &x : xs){
        cout<<x<<' ';
        file<<x<<';';
    }
    cout<<'\n'<<endl;
    file<<'\n';
}

/**
 * Crea árboles RTree utilizando los archivos de europa.bin y random.bin con el algoritmo NearestX y STR,
 * utilizando potencias de 2 entre 2^15 y 2^24 inclusive.
 *
 * Registra los resultados de tiempo para cada combinación de archivo-tamaño-algoritmo en un archivo .csv,
 * y los RTree resultantes corresponderán a los de tamaño 2^24.
 * @param argc Sin utilizar
 * @param argv Sin utilizar
 * @return Código de error C++
 */
int main(int argc,char **argv) {
    //Vectores donde se guardan los resultados de tiempo
    vector<long long> timesNX_Eur;
    vector<long long> timesSTR_Eur;
    vector<long long> timesNX_Ran;
    vector<long long> timesSTR_Ran;

    string infile = argv[0];

    ofstream file(SALIDA);

    for(unsigned int i=MIN_2N; i <= MAX_2N;i++){
        file<<';'<<i;
        const unsigned int N = 1<<i;
        tim.start();
        NearestX.CreateRTree(BIN_PATH + "europa.bin", OUT_PATH + "EuropaNX.bin", N);
        timesNX_Eur.push_back(tim.end());

        tim.start();
        STR.CreateRTree(BIN_PATH + "europa.bin", OUT_PATH + "EuropaSTR.bin", N);
        timesSTR_Eur.push_back(tim.end());

        tim.start();
        NearestX.CreateRTree(BIN_PATH + "random.bin", OUT_PATH + "RandomNX.bin", N);
        timesNX_Ran.push_back(tim.end());

        tim.start();
        STR.CreateRTree(BIN_PATH + "random.bin", OUT_PATH + "RandomSTR.bin", N);
        timesSTR_Ran.push_back(tim.end());
    }
    file<<'\n'; 

    cout<<"Se construyeron árboles para las potencias 2^i con i entre: ["<<MIN_2N<<" - "<<MAX_2N<<"]\n"<<endl;

    showResults(timesNX_Eur, file, "EuropaNX");
    showResults(timesSTR_Eur, file, "EuropaSTR");
    showResults(timesNX_Ran, file, "RandomNX");
    showResults(timesSTR_Ran, file, "RandomSTR");

    file.close();
    cout<<"Resultados guardados en "<<SALIDA<<endl;
    return 0;
}
#undef SALIDA