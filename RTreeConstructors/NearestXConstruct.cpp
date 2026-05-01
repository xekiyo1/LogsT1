#ifndef HPEADER
    #define HPEADER
    #include "config.hp"
    #include "headers.h"
#endif

struct NearestXConstructor : AbstractRtreeConstructor{
    string name = "NearestX";
private:
    
    vector<NodoCalculador> groupHijos(vector<Hijo> &og, vector<Nodo> &final) override{
        sort(init.begin(),init.end(),
            [](Hijo &a, Hijo &b) //acá x1 y x2 son iguales por ser punto en bruto
            { return a.x1 < b.x1; });

        vector<NodoCalculador> bulk;

        for(unsigned long int i=0;i<og.size();i+=HIJOS_NODO){
            NodoCalculador nuevo;

            for(unsigned long int j=0;j<HIJOS_NODO && i+j<og.size();j++) //añadir los b hijos a partir de esta posición
                nuevo.addChild(og[i+j]);

            nuevo.idx = final.size(); //añadir el nodo real al árbol final
            final.push_back(nuevo.nodo);

            bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }

        return bulk;
    }

    vector<NodoCalculador> groupNodos(vector<NodoCalculador> &og, vector<Nodo> &final) override{
        sort(og.begin(),og.end(), [](NodoCalculador &a, NodoCalculador &b)
            { return a.centerX() < b.centerX() ; });

        vector<NodoCalculador> bulk;

        for(unsigned long int i=0;i<og.size();i+=HIJOS_NODO){
            NodoCalculador nuevo;

            for(int j=0;j<HIJOS_NODO;j++) //añadir los b hijos a partir de esta posición
                nuevo.addChild(og[i+j]);

            nuevo.idx = final.size(); //añadir el nodo real al árbol final
            final.push_back(nuevo.nodo);

            bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
    }
}