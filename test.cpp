#include "headers.h"

#include <bits/stdc++.h>
#include <RTreeConstructor/NearestXConstructor.cpp>
#include <RTreeConstructor/STRConstructor.cpp>
using namespace std;

const unsigned long startN = 1<<15;
const unsigned long endN = 1<<24;

vector timeConstruction(RTreeConstructor creator, string filedir){
    vector times;
    for(unsigned long n = startN; n <= endN; n<<=1){
        startTime();

        creator.CreateRTree(filedir, "RTree"+creator.name+".bin");

        endTime();
    }
}

int main() {
    STRConstructor str;
    NearestXConstructor nearX;

    return 0;
}