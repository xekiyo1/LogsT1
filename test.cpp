#include "headers.h"
#include <bits/stdc++.h>
using namespace std;

NearestXConstructor NearestX;
STRConstructor STR;

int main() {
    NearestX.CreateRTree("europa.bin","arbolitoNearestX.bin");
    STR.CreateRTree("europa.bin","arbolitoSTR.bin");
    return 0;
}