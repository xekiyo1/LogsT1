//
// Created by elnchou on 04-05-26.
//

#ifndef LOGST1_NODOCALCULADOR_H
#define LOGST1_NODOCALCULADOR_H
#include "../config.hp"

class NodoCalculador{
private:
    //actualiza el bounding box con nuevas variables
    void updateRect(float ox1, float ox2, float oy1, float oy2);
    //castear en hijo, poner mi rectángulo e índice en el arreglo
    void pasteChild(Hijo &obj);
    float x1,x2,y1,y2; // horizontal bounding box
public:
    Nodo nodo;
    int idx;

    float centerX(){ return (x1+x2) / 2.0; }
    float centerY(){ return (y1+y2) / 2.0; }

    NodoCalculador(){ nodo.k=0; } //necesario para updateRect

    //añadir hijo que ya está formateado como hijo
    void addChild(Hijo& other);

    //tomar otro nodo NodoCalculador y ponerlo como mi hijo sin tener que crear uno auxiliar
    void addChild(NodoCalculador& other);
};



#endif //LOGST1_NODOCALCULADOR_H
