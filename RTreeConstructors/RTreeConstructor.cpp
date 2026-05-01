#ifndef HPEADER
    #define HPEADER
    #include "config.hp"
    #include "headers.h"
#endif

struct AbstractRtreeConstructor{
private:
    virtual vector<NodoCalculador> groupHijos(vector<Hijo> &og, vector<Nodo> &final);
    virtual vector<NodoCalculador> groupNodos(vector<NodoCalculador> &og, vector<Nodo> &final);
public:
    string name;
    void CreateRtree(string infile, string outfile){
        float buffer[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)

        vector<Hijo> init; // aquí se guardarán los puntos iniciales en bruto

        ifstream file(infile, ios::binary);
        if (!file.is_open()) {
            cerr << name << ":: Error opening file for reading named " << infile <<endl;
            exit(1);
        }

        while (file.read(reinterpret_cast<char *>(buffer), BLOCK)) {
            // tener cuidado si la cosa no es múltiplo del bloque, qué se hace si nos quedamos sin bloques
            for(int i=0;i<FLOAT_BLOCK;i+=2){
                Hijo aux;
                aux.x1 = aux.x2 = buffer[i];
                aux.y1 = aux.y2 = buffer[i+1];
                aux.valor = -1;
                init.push_back(aux); //guardo el punto en bruto
            }
        }
        file.close();


        // aquí guardaremos los que estamos ordenando
        // aquí los nodos finales ya creados, que luego será escrito como archivo
        vector<Nodo> final(1);

        //nodo iniciales
        vector<NodoCalculador> bulk = groupHijos(init), bulk2;
        init.clear();

        //hacer lo mismo pero en "bulk" hasta que se puedan guardar los nodos en la raíz
        // bulk: B  B
        // bulk2: BB
        while(bulk.size() > HIJOS_NODO){
            bulk2 = groupNodos(bulk);
            bulk.clear(); //solo para ahorrar memoria
            swap(bulk,bulk2);
        }
        
        NodoCalculador raiz;
        for(NodoCalculador &hijoraiz : bulk)
            raiz.addChild(hijoraiz);
        final[0] = raiz.nodo;

        ofstream resultado(outfile);
        for(Nodo &xd : final)
            resultado.write(reinterpret_cast<const std::ostream::char_type *>(&xd),sizeof(Nodo));
        resultado.close();
    }
}