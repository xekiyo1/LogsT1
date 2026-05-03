#include "RTree.h"
using namespace std;


void AbstractTreeConstructor::CreateRTree(string infile, string outfile, int N){
    float buffer[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)

    vector<Hijo> init; // aquí se guardarán los puntos iniciales en bruto

    ifstream file(infile, ios::binary);

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

    //inicializar información de salida
    resultado = ofstream(outfile);
    //dejar espacio para la raíz
    resultado.seekp(sizeof(Nodo));
    cantidadNodos = 1;

    //inicializar nodos
    vector<NodoCalculador> bulk,bulk2;
    if(DEBUG)cout<<init.size()<<endl;
    groupNodos(init, bulk);
    init.clear(); //ya fueron copiados a bulk

    //ir comprimiendo los nodos y añadiéndolos al vector final hasta llegar al tamaño deseado
    while(bulk.size() > HIJOS_NODO){
        if(DEBUG)cout<<"Nodos restantes: "<<bulk.size()<<endl;
        if(DEBUG)cout<<"Nodos totales: "<<cantidadNodos<<endl;
        //agarra los nodos y los comprime en bulk2
        groupNodos(bulk, bulk2);
        //limpia bulk1 y ahora hay que seguir comprimiendo los comprimidos
        bulk.clear();
        swap(bulk,bulk2);
    }

    if(DEBUG)cout<<"fin"<<endl;

    NodoCalculador raiz;
    for(NodoCalculador &hijoraiz : bulk)
        raiz.addChild(hijoraiz);
    resultado.seekp(0);
    resultado.write(reinterpret_cast<const std::ostream::char_type *>(&raiz.nodo),sizeof(Nodo));

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