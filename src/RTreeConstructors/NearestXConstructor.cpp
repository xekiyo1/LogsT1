#include "RTreeConstructor.h"
using namespace std;

/**
 * Agrupa los Nodos de un vector en instancias de NodoCalculador, agregándolas a un vector ya existente.
 * En este caso, los ordena por cercanía en coordenada X.
 *
 * Acepta tanto _Hijo_ como _NodoCalculador_.
 * @tparam TipoNodo Clase contenida en el vector entregado. Debe ser Hijo o NodoCalculador.
 * @param og Vector de instancias a agrupar en NodoCalculador. NOTA: Va a ser modificado durante la ejecución.
 * @param dest Vector de NodoCalculador
 */
template <typename TipoNodo>
void NearestXConstructor::groupGeneric(vector<TipoNodo> &og, vector<NodoCalculador> &dest){
    sorterX(og.begin(), og.end());

    for(unsigned long int i=0;i<og.size();i+=HIJOS_NODO){
        NodoCalculador nuevo;

        for(unsigned long int j=0;j<HIJOS_NODO && i+j<og.size();j++) //añadir los b hijos a partir de esta posición
            nuevo.addChild(og[i+j]);

        nuevo.idx = cantidadNodos++; //añadir el nodo real al árbol final

        final.push_back(nuevo.nodo);
        dest.push_back(nuevo); // y el nearestx al nivel actual de nodos
    }
}


void NearestXConstructor::groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) {
    groupGeneric<Hijo>(og, dest);
}
void NearestXConstructor::groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) {
    groupGeneric<NodoCalculador>(og, dest);
}