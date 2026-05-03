#include "headers.h"
#include <bits/stdc++.h>
using namespace std;

NearestXConstructor NearestX;
STRConstructor STR;
HPTimer tim;

int main() {
    tim.start();
    NearestX.CreateRTree("europa.bin","arbolitoNearestX.bin");
    cout<<"tiempito: "<<tim.end()<<endl;
    tim.start();
    STR.CreateRTree("europa.bin","arbolitoSTR.bin");
    cout<<"tiempito: "<<tim.end()<<endl;
    return 0;
}