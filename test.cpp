#include "headers.h"
#include <bits/stdc++.h>
using namespace std;

#define SALIDA "constTest.csv"

NearestXConstructor NearestX;
STRConstructor STR;
HPTimer tim;

ofstream file(SALIDA);

//imprime resultados a consola y archivo
void showResults(vector<unsigned long long> &xs){
    for(unsigned long long &x : xs){
        cout<<x<<' ';
        file<<x<<';';
    }
    cout<<'\n'<<endl;
    file<<'\n';
}


int main() {
    vector<unsigned long long> timesNX;
    vector<unsigned long long> timesSTR;

    for(unsigned int i=MIN_2N; i <= MAX_2N;i++){
        file<<';'<<i;
        unsigned int N = 1<<i;
        tim.start();
        NearestX.CreateRTree("europa.bin", "arbolitoNearestX.bin", N);
        timesNX.push_back(tim.end());

        tim.start();
        STR.CreateRTree("europa.bin", "arbolitoSTR.bin", N);
        timesSTR.push_back(tim.end());
    }
    file<<'\n'; 

    cout<<"Se construyeron árboles para las potencias 2^i con i entre: ["<<MIN_2N<<" - "<<MAX_2N<<"]\n"<<endl;

    cout<<"Tiempos de construcción NearestX:"<<endl;
    file<<"NearestX;";
    showResults(timesNX);
    
    cout<<"Tiempos de construcción STR:"<<endl;
    file<<"STR;";
    showResults(timesSTR);

    file.close();
    cout<<"Resultados guardados en "<<SALIDA<<endl;
    return 0;
}
#undef SALIDA