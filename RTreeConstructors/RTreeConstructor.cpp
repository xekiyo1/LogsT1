struct AbstractRtreeConstructor{
    string name = "RTree";
protected:
    ofstream resultado;
    int cantidadNodos;

    /// Overload que permite diferenciar entre la ordenación de Hijo y de NodoCalculador.
    /// Necesario para diferenciar las ordenaciones en groupNodos.
    void sorterX(vector<Hijo>::iterator begin, vector<Hijo>::iterator end){
        sort(begin,end, [](Hijo &a, Hijo &b) { return a.x1 < b.x1; });
    }
    void sorterX(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end){
        sort(begin,end, [](NodoCalculador &a, NodoCalculador &b) { return a.centerX() < b.centerX(); });
    }
    void sorterY(vector<Hijo>::iterator begin, vector<Hijo>::iterator end){
        sort(begin,end, [](Hijo &a, Hijo &b) { return a.y1 < b.y1; });
    }
    void sorterY(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end){
        sort(begin,end, [](NodoCalculador &a, NodoCalculador &b) { return a.centerY() < b.centerY(); });
    }

    /// Función que agrupa los nodos de og y añade los resultantes a dest, que puede ser
    /// vector de Hijo o vector de NodoCalculador.
    /// También los castea y añade al vector de nodos finales.
    virtual void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest){}
    virtual void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest){}
public:
    void CreateRTree(string infile, string outfile){
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

        //inicializar información de salida
        resultado = ofstream(outfile);
        //dejar espacio para la raíz
        resultado.seekp(sizeof(Nodo));
        cantidadNodos = 1;

        //inicializar nodos
        vector<NodoCalculador> bulk,bulk2;
        cerr<<init.size()<<endl;
        groupNodos(init, bulk);
        init.clear(); //ya fueron copiados a bulk

        //ir comprimiendo los nodos y añadiéndolos al vector final hasta llegar al tamaño deseado
        while(bulk.size() > HIJOS_NODO){
            cerr<<"Nodos restantes: "<<bulk.size()<<endl;
            cerr<<"Nodos totales: "<<cantidadNodos<<endl;
            //agarra los nodos y los comprime en bulk2
            groupNodos(bulk, bulk2);
            //limpia bulk1 y ahora hay que seguir comprimiendo los comprimidos
            bulk.clear();
            swap(bulk,bulk2);
        }
        
        cerr<<"fin"<<endl;

        NodoCalculador raiz;
        for(NodoCalculador &hijoraiz : bulk)
            raiz.addChild(hijoraiz);
        resultado.seekp(0);
        resultado.write(reinterpret_cast<const std::ostream::char_type *>(&raiz.nodo),sizeof(Nodo));
        
        resultado.close();
    }
};