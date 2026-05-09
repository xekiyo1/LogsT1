#include "RTreeConstructor.h"
using namespace std;

/**
 *
 * @tparam TipoNodo Define
 * @param bulk
 * @param dest
 */
template <typename TipoNodo>
void STRConstructor::groupGeneric(vector<TipoNodo> &bulk, vector<NodoCalculador> &dest){
    // primero, ordena en X y divide en subgrupos de tamaño raíz (n/b)
    sorterX(bulk.begin(), bulk.end());
    const int tamano = bulk.size() / sqrt(static_cast<double>(bulk.size()) / static_cast<double>(HIJOS_NODO));

    #ifdef LOGLEVEL
        if constexpr (LOGLEVEL > 1)
            cout << "división en STR: " << tamano << endl;
    #endif

    // Para cada subgrupo, ordena según coordenada Y
    // en (n / tamano) intervalos
    for(unsigned int i=0;i<bulk.size();i+=tamano){
        auto begin = bulk.begin() + i;
        auto end = bulk.begin() + min<unsigned int>(i + tamano, bulk.size());
        sorterY(begin,end);

        // tamano >> b, pero b es el máximo que podemos tener en un nodo
        // tamano = raiz(n/b)
        // tamano /= raiz(n/b)  no hay garantía que = b
        //así que llenaremos lo más posible
        while(begin!=end){
            NodoCalculador nuevo;
            for(int j=0;j<HIJOS_NODO && begin!=end; j++){
                nuevo.addChild(*begin);
                begin++;
            }
            nuevo.idx = cantidadNodos++; //añadir el nodo real al árbol final
            final.push_back(nuevo.nodo);
            dest.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
    }
}



void STRConstructor::groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) {
    groupGeneric<NodoCalculador>(og,dest);
}

void STRConstructor::groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest){
    groupGeneric<Hijo>(og,dest);
}