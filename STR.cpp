#ifndef HPEADER
    #define HPEADER
    #include "config.hp"
#endif

void STR(string infile, string outfile){
    float buffer[ FLOAT_BLOCK ]; // 512 puntos (1024 floats)

    vector<Hijo> init; // aquí se guardarán los puntos iniciales en bruto

    ifstream file(infile, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading."<<endl;
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
    int tamano = sqrt((double)(init.size()) / double(HIJOS_NODO)); //IMPLEMENTAR TAMAÑO
    for(unsigned int i=0;i<init.size();i+=tamano){
        auto begin = init.begin() + i;
        auto end = init.begin() + min<unsigned int>(i+tamano, init.size());
        sort(begin,end, [](Hijo &a, Hijo &b)
        { return a.y1 < b.y1; });

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
            nuevo.idx = final.size(); //añadir el nodo real al árbol final
            final.push_back(nuevo.nodo);
            bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
        }
    }
    init.clear();

    //hacer lo mismo pero en "bulk" hasta que se puedan guardar los nodos en la raíz
    // bulk: B  B
    // bulk2: BB
    while(bulk.size() > HIJOS_NODO){
        sort(bulk.begin(),bulk.end(), [](NodoCalculador &a, NodoCalculador &b)
            { return a.centerX() < b.centerX() ; });
        
        tamano = sqrt((double)(bulk.size()) / double(HIJOS_NODO));
        for(unsigned int i=0;i<bulk.size();i+=tamano){
            auto begin = bulk.begin() + i;
            auto end = bulk.begin() + min<unsigned int>(i+tamano, bulk.size());
            sort(begin,end, [](NodoCalculador &a, NodoCalculador &b)
            { return a.centerY() < b.centerY(); });

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
                nuevo.idx = final.size(); //añadir el nodo real al árbol final
                final.push_back(nuevo.nodo);
                bulk.push_back(nuevo); // y el nearestx al nivel actual de nodos
            }
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
}