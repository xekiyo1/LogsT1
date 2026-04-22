#include "config.h"
#include<algorithm>

//esto es el nodo auxiliar que se utilizará, un poco grande o no
//INCLUYE: Método para añadir hijo, método para actualizar su rectángulo
struct NodoNearestX{
    Nodo nodo;
    int idx;
    float x1,x2,y1,y2; // horizontal bounding box

    NodoNearestX(){ nodo.k=0; } //necesario para updateRect

    //actualiza el bounding box con nuevas variables
    void updateRect(float ox1, float ox2, float oy1, float oy2){
        if(nodo.k == 0){ // si no tengo hijos con los que comparar
            x1 = ox1; y1 = oy1;
            x2 = ox2; y2 = oy2;
        }else{
            x1 = min(x1,ox1); y1 = min(y1,oy1);
            x2 = max(x2,ox2); y2 = max(y2,oy2);
        }
    }

    float center(){ return (x1+x2) / 2.0; }

    //añadir hijo que ya está formateado como hijo
    void addChild(Hijo& other){
        updateRect(other.x1, other.x2, other.y1, other.y2);
        nodo.hijos[k++] = other;
    }


    //A ESTOS LES FALTA REVISIÓN EN PROX REUNIÓN//
/*  //castear en hijo, poner mi rectángulo e índice en el arreglo
    void pasteChild(Hijo &obj){
        obj.x1 = x1; obj.x2 = x2;
        obj.y1 = y1; obj.y2 = y2;
        obj.value = idx;
    }
    
    //tomar otro nodo NodoNearestX y ponerlo como mi hijo sin tener que crear uno auxiliar
    void addChild(NodoNearestX& other){
        updateRect(other.x1, other.x2, other.y1, other.y2);
        other.pasteChild(hijos[k++]);
    }*/
};

void Nearest_X(string infile){
    int i=0;
    float puntos[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)

    std::vector<Hijo> init; // aquí se guardarán los puntos iniciales en bruto
    std::vector<NodoNearestX> bulk, bulk2; //aquí, los NodoNearestX con la información para ser comparados
    std::vector<Nodo> final(1); // aquí los nodos finales, que luego será escrito como archivo
    

    ifstream file(infile, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading.";
        return 1;
    }
    while (file.read((char*)puntos, BLOCK)) {
        // tener cuidado si la cosa no es múltiplo del bloque, qué se hace si nos quedamos sin bloques
        for(int i=0;i<FLOAT_BLOCK;i+=2){
            Hijo aux;
            aux.x1 = aux.x2 = puntos[i];
            aux.y1 = aux.y2 = puntos[i+1];
            init.push_back(aux); //guardo el punto en bruto
        }
    }
    file.close();

    
    std::sort(init.begin(),init.end(),
        [](Hijo &a, Hijo &b) //acá x1 y x2 son iguales por ser punto en bruto
        { return a.x1 < b.x1; });
    
    //nodo iniciales
    for(int i=0;i<init.size();i+=HIJOS_NODO){
        NodoNearestX nuevo;

        for(int j=0;j<HIJOS_NODO;j++) //añadir los b hijos a partir de esta posición
            nuevo.addChild(init[i+j]);

        nuevo.idx = final.size(); //añadir el nodo real al árbol final
        final.push_back(nuevo.nodo);

        bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
    }
    init.clear();

    //hacer lo mismo pero en "bulk" hasta que se puedan guardar los nodos en la raíz

}