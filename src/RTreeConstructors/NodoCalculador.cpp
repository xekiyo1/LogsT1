//
// Created by elnchou on 04-05-26.
//

#include "NodoCalculador.h"
#include <stdexcept>
#include <algorithm>

//actualiza el bounding box con nuevas variables
void NodoCalculador::updateRect(float ox1, float ox2, float oy1, float oy2){
    if(nodo.k == 0){ // si no tengo hijos con los que comparar
        x1 = ox1; y1 = oy1;
        x2 = ox2; y2 = oy2;
    }else{
        x1 = std::min(x1,ox1); y1 = std::min(y1,oy1);
        x2 = std::max(x2,ox2); y2 = std::max(y2,oy2);
    }
}

//añadir hijo que ya está formateado como hijo
void NodoCalculador::addChild(Hijo& other){
    if(nodo.k==HIJOS_NODO) throw std::logic_error("te odio no puedo mantener tantos hijos");
    updateRect(other.x1, other.x2, other.y1, other.y2);
    nodo.hijos[nodo.k++] = other;
}

//castear en hijo, poner mi rectángulo e índice en el arreglo
void NodoCalculador::pasteChild(Hijo &obj){
    obj.x1 = x1; obj.x2 = x2;
    obj.y1 = y1; obj.y2 = y2;
    obj.valor = idx;
}

//tomar otro nodo NodoCalculador y ponerlo como mi hijo sin tener que crear uno auxiliar
void NodoCalculador::addChild(NodoCalculador& other){
    if(nodo.k==HIJOS_NODO) throw std::logic_error("te odio no puedo mantener tantos hijos");
    updateRect(other.x1, other.x2, other.y1, other.y2);
    other.pasteChild(nodo.hijos[nodo.k++]);
}