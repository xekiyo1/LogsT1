#include "../headers.h"
#include <bits/stdc++.h>
using namespace std;

#define SALIDA "tiemposCreacion.csv"
const string BIN_PATH = "bin/data/";
const string OUT_PATH = "bin/trees/";

NearestXConstructor NearestX;
STRConstructor STR;
HPTimer tim;

//imprime resultados a consola y archivo
void showResults(vector<unsigned long long> &xs, ofstream &file, string name){
    cout<<"Tiempos de construcción "<<name<<':'<<endl;
    file<<name<<';';

    for(unsigned long long &x : xs){
        cout<<x<<' ';
        file<<x<<';';
    }
    cout<<'\n'<<endl;
    file<<'\n';
}


int main(int argc,char **argv) {
    vector<unsigned long long> timesNX_Eur;
    vector<unsigned long long> timesSTR_Eur;
    vector<unsigned long long> timesNX_Ran;
    vector<unsigned long long> timesSTR_Ran;

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