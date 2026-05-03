#include "STRConstructor.h"
using namespace std;

template <typename TipoNodo>
void STRConstructor::groupGeneric(vector<TipoNodo> &bulk, vector<NodoCalculador> &dest){
    sorterX(bulk.begin(), bulk.end());
    int tamano = max<int>(sqrt((double)(bulk.size()) / double(HIJOS_NODO)), HIJOS_NODO);

    cerr<<tamano<<endl;

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
            resultado.write(reinterpret_cast<const std::ostream::char_type *>(&nuevo.nodo),sizeof(Nodo));
            dest.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
    }
}