#ifndef HPEADER
    #define HPEADER
    #include "config.hp"
    #include "headers.h"
#endif

void Nearest_X(string infile, string outfile){
    float buffer[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)

    vector<Hijo> init; // aquí se guardarán los puntos iniciales en bruto

    ifstream file(infile, ios::binary);
    if (!file.is_open()) {
        cerr << "Nearest_X.cpp:: Error opening file for reading named " << infile <<endl;
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

    sort(init.begin(),init.end(),
        [](Hijo &a, Hijo &b) //acá x1 y x2 son iguales por ser punto en bruto
        { return a.x1 < b.x1; });    

    // aquí guardaremos los que estamos ordenando
    vector<NodoCalculador> bulk, bulk2;
    // aquí los nodos finales ya creados, que luego será escrito como archivo
    vector<Nodo> final(1);

    //nodo iniciales
    for(unsigned long int i=0;i<init.size();i+=HIJOS_NODO){
        NodoCalculador nuevo;

        for(unsigned long int j=0;j<HIJOS_NODO && i+j<init.size();j++) //añadir los b hijos a partir de esta posición
            nuevo.addChild(init[i+j]);

        nuevo.idx = final.size(); //añadir el nodo real al árbol final
        final.push_back(nuevo.nodo);

        bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
    }
    init.clear();

    //hacer lo mismo pero en "bulk" hasta que se puedan guardar los nodos en la raíz
    // bulk: B  B
    // bulk2: BB
    while(bulk.size() > HIJOS_NODO){
        sort(bulk.begin(),bulk.end(), [](NodoCalculador &a, NodoCalculador &b)
            { return a.centerX() < b.centerX() ; });

        for(unsigned long int i=0;i<bulk.size();i+=HIJOS_NODO){
            NodoCalculador nuevo;

            for(int j=0;j<HIJOS_NODO;j++) //añadir los b hijos a partir de esta posición
                nuevo.addChild(bulk[i+j]);

            nuevo.idx = final.size(); //añadir el nodo real al árbol final
            final.push_back(nuevo.nodo);

            bulk2.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
        bulk.clear();
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

    return;
}