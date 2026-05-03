#include "RTreeConstructor.cpp"
struct NearestXConstructor : RtreeConstructor{
    static string name = "NearestX";
private:
    template <typename TipoNodo>
    void groupGeneric(vector<TipoNodo> &og, vector<NodoCalculador> &dest){
        sorterX(og.begin(), og.end());

        for(unsigned long int i=0;i<og.size();i+=HIJOS_NODO){
            NodoCalculador nuevo;

            for(unsigned long int j=0;j<HIJOS_NODO && i+j<og.size();j++) //añadir los b hijos a partir de esta posición
                nuevo.addChild(og[i+j]);

            nuevo.idx = cantidadNodos++; //añadir el nodo real al árbol final
            resultado.write(reinterpret_cast<const std::ostream::char_type *>(&nuevo.nodo),sizeof(Nodo));

            dest.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
    }
protected:
    void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) override{
        groupGeneric<Hijo>(og, dest);
    }
    void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) override{
        groupGeneric<NodoCalculador>(og, dest);
    }
}
/** Constructor de RTrees con NearestX */
NearestX;