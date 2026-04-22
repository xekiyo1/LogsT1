#include "config.h"
#include<algorithm>

void Nearest_X(string infile){

    ifstream file(infile, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading.";
        return 1;
    }

    int i=0;
    float puntos[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)

    std::vector<Nodo> bulk;
    std::vector<Nodo> final(1);

    //inicializa bulk
    std::vector<Hijo> init; // aquí se guardarán los puntos en bruto
    
    while (file.read((char*)puntos, BLOCK)) {
        // tener cuidado si la cosa no es múltiplo del bloque, qué se hace si nos quedamos sin bloques
        for(int i=0;i<FLOAT_BLOCK;i+=2){
            Hijo aux;
            aux.x1 = aux.x2 = puntos[i];
            aux.y1 = aux.y2 = puntos[i+1];
            init.push_back(aux); //guardo el punto en bruto
        }
    }

    std::sort(init.begin(),init.end(),
        [](Hijo &a, Hijo &b) //acá x1 y x2 son iguales por ser punto en bruto
        { return a.x1 < b.x1; });
    
    //nodo iniciales
    for(int i=0;i<init.size();i+=HIJOS_NODO){
        Nodo b;
        b.x1 = b.x2 = init[i+j].x1;
        b.y1 = b.y2 = init[i+j].y1;
        b.hijos[0] = init[i+j];
        //para cada hijo del segundo en adelante, expandir rectángulo y añadirlo al nodo
        for(int j=1;j<HIJOS_NODO;j++){
            b.x1 = min(b.x1, init[i+j].x1);
            b.x2 = max(b.x2, init[i+j].x2);
            b.y1 = min(b.y1, init[i+j].y1);
            b.y2 = max(b.y2, init[i+j].y2);
            //guardar hijos en el bloque
            hijos[j] = init[i+j];
        }

        //añadir nodo al vector final
        final.push_back(b);
    }

    //hacer lo mismo hasta que se puedan guardar los nodos en la raíz

    // Close file
    file.close();
}