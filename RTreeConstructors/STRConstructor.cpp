#ifndef HPEADER
    #define HPEADER
    #include "config.hp"
    #include "headers.h"
#endif

struct STRConstructor : AbstractRtreeConstructor{
    string name = "STR";
private:

    template <typename Nod>
    Nod groupInterval(iterator::vector<Nod> begin, iterator::vector<Nod> end,
        vector<NodoCalculador> &bulk, vector<Nodo> &final)
    {
        while(begin!=end){
            NodoCalculador nuevo;
            for(int j=0;j<HIJOS_NODO && begin!=end; j++){
                nuevo.addChild(*begin);
                begin++;
            }
            nuevo.idx = final.size(); //añadir el nodo real al árbol final
            final.push_back(nuevo.nodo);
            bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
    }

    vector<NodoCalculador> groupHijos(vector<Hijo> &og, vector<Nodo> &final) override{
        vector<NodoCalculador> bulk;

        sort(og.begin(),og.end(),
            [](Hijo &a, Hijo &b) //acá x1 y x2 son iguales por ser punto en bruto
            { return a.x1 < b.x1; });

        unsigned int tamano = sqrt((double)(og.size()) / double(HIJOS_NODO)); //IMPLEMENTAR TAMAÑO

        for(unsigned int i=0;i<og.size();i+=tamano){
            auto begin = og.begin() + i;
            auto end = og.begin() + min<unsigned int>(i+tamano, og.size());

            sort(begin,end, [](Hijo &a, Hijo &b)
            { return a.y1 < b.y1; });

            // tamano >> b, pero b es el máximo que podemos tener en un nodo
            // tamano = raiz(n/b)
            // tamano /= raiz(n/b)  no hay garantía que = b
            //así que llenaremos lo más posible
            groupInterval(begin, end, bulk, final);
        }

        return bulk;
    }

    vector<NodoCalculador> groupNodos(vector<NodoCalculador> &og, vector<Nodo> &final) override{
        vector<NodoCalculador> bulk;

        sort(og.begin(),og.end(), [](NodoCalculador &a, NodoCalculador &b)
            { return a.centerX() < b.centerX() ; });
        
        //notar que es un entero
        unsigned int tamano = sqrt((double)(og.size()) / double(HIJOS_NODO));

        for(unsigned int i=0;i<og.size();i+=tamano){
            //puntero al inicio y al final de este intervalo
            auto begin = og.begin() + i;
            auto end = og.begin() + min<unsigned int>(i+tamano, og.size());

            //Ordenar intervalo según Y
            sort(begin,end, [](NodoCalculador &a, NodoCalculador &b)
            { return a.centerY() < b.centerY(); });

            // tamano >> b, pero b es el máximo que podemos tener en un nodo
            // tamano = raiz(n/b)
            // tamano /= raiz(n/b)  no hay garantía que = b
            //así que llenaremos lo más posible
            groupInterval(begin, end, bulk, final);
        }

        return bulk;
    }
}