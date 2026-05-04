#include "RTreeConstructor.h"
using namespace std;

/// Dirección donde se almacenan los archivos binarios de puntos
const string BIN_PATH = "bin/data/";
/// Dirección donde se guardarán los árboles creados
const string OUT_PATH = "bin/trees/";


void AbstractTreeConstructor::CreateRTree(string infile, string outfile, int N){
    float buffer[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)
    cantidadNodos = 1;
    final.resize(1);

    vector<Hijo> init; // aquí se guardarán los puntos iniciales en bruto

    // FASE UNO: Leer puntos!!!!!
    ifstream file(BIN_PATH + infile, ios::binary);

    if (!file.is_open()) {
        cout << name << ":: Error opening file for reading named " << infile <<endl;
        exit(1);
    }

    while (file.read(reinterpret_cast<char *>(buffer), BLOCK) && N>0) {
        // tener cuidado si la cosa no es múltiplo del bloque, qué se hace si nos quedamos sin bloques
        for(int i=0;N>0 && i<FLOAT_BLOCK;i+=2){
            Hijo aux;
            aux.x1 = aux.x2 = buffer[i];
            aux.y1 = aux.y2 = buffer[i+1];
            aux.valor = -1;
            init.push_back(aux); //guardo el punto en bruto
            N--;
        }
    }
    file.close();


    //inicializar nodos
    vector<NodoCalculador> bulk,bulk2;
    #ifdef LOGLEVEL
        if constexpr (LOGLEVEL > 1)cout<<"Puntos incluidos: "<<init.size()<<endl;
    #endif

    groupNodos(init, bulk);
    init.clear(); //ya fueron copiados a bulk

    //LOOP PRINCIPAL: COMPRIMIR NODOS HASTA QUE ENTREN EN LA RAÍZ!!!1!!
    //ir comprimiendo los nodos y añadiéndolos al vector final hasta llegar al tamaño deseado
    while(bulk.size() > HIJOS_NODO){
        #ifdef LOGLEVEL
            if constexpr (LOGLEVEL > 1){
                cout<<"Nodos restantes por condensar: "<<bulk.size()<<endl;
                cout<<"Nodos totales: "<<cantidadNodos<<endl;
            }
        #endif
        //agarra los nodos y los comprime en bulk2
        groupNodos(bulk, bulk2);
        //limpia bulk1 y ahora hay que seguir comprimiendo los comprimidos
        bulk.clear();
        swap(bulk,bulk2);
    }

    #ifdef LOGLEVEL
        if constexpr (LOGLEVEL)cout<<"fin construcción de muchos nodos: "<<cantidadNodos<<endl;
    #endif

    // Finalmente, meter todos los que quedan en la raíz y escribirla al inicio
    NodoCalculador raiz;
    for(NodoCalculador &hijoraiz : bulk)
        raiz.addChild(hijoraiz);
    final[0] = raiz.nodo;

    ofstream resultado(OUT_PATH + outfile);
    for(Nodo& a : final)
        resultado.write(reinterpret_cast<const std::ostream::char_type *>(&a),sizeof(Nodo));
    resultado.close();
}


void AbstractTreeConstructor::sorterX(vector<Hijo>::iterator begin, vector<Hijo>::iterator end){
    sort(begin,end, [](Hijo &a, Hijo &b) { return a.x1 < b.x1; });
}

void AbstractTreeConstructor::sorterX(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end){
    sort(begin,end, [](NodoCalculador &a, NodoCalculador &b) { return a.centerX() < b.centerX(); });
}

void AbstractTreeConstructor::sorterY(vector<Hijo>::iterator begin, vector<Hijo>::iterator end){
    sort(begin,end, [](Hijo &a, Hijo &b) { return a.y1 < b.y1; });
}
void AbstractTreeConstructor::sorterY(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end){
    sort(begin,end, [](NodoCalculador &a, NodoCalculador &b) { return a.centerY() < b.centerY(); });
}