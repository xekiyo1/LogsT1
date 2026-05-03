#include "config.hp"
#include "headers.h"
#include "RandomSquare.cpp"
using namespace std;

class RTree{
private:
    fstream file;
    int diskreads = 0; //para medir las I/Os
public:
    void abrirArchivo(string nombre_archivo){
        file = fstream(nombre_archivo, std::ios::in);
        if(!file.is_open()) throw logic_error("RTree:: no se abrió el RTree");
    }

    RTree(string nombre_archivo){
        diskreads = 0;
        abrirArchivo(nombre_archivo);
    }

    void cerrarArchivo() {file.close();}

    int getReads() {return diskreads;} 

    void resetReads() {diskreads = 0;} 



    //busca un nodo según su índice
    Nodo obtenerIndice(unsigned long long i){
        Nodo extraido;
        file.seekg(i * sizeof(Nodo));
        file.read(reinterpret_cast<char *>(&extraido), sizeof(Nodo));
        diskreads++;
        return extraido;
    }

    //int cantidadNodos(); //no creo que se necesite

    //funciona como un macro pa cachar no más si un hijo se intersecta conmigo
    bool se_intersectan(float x1, float y1, float x2, float y2, Hijo &son){
        #define puntoContenido(a,b) (x1 <= a && a <= x2 && y1 <= b && b <= y2)

        //bastan con incluir un único punto del rectángulo
        if(puntoContenido(son.x1,son.y1)) return true;
        if(puntoContenido(son.x1,son.y2)) return true;
        if(puntoContenido(son.x2,son.y1)) return true;
        if(puntoContenido(son.x2,son.y2)) return true;
        
        #undef puntoContenido
        return false;
    }

    /*
    Lo que sugiero hacer aquí es un BFS, osea tener una queue FIFO en la que vayamos guardando los índices de los nodos
    que debemos revisar. Dejaré el esqueleto aquí con funciones de c++ que sirven pero puedes cambiarlo y preguntar señor xeki

    hora de aprender c++
    */
    vector<float> encontrarPuntos(float x1, float y1, float x2, float y2){
        //aquí guardamos la respuesta, la idea es guardar los puntos como [x1, y1, x2, y2, x3, y3 ...]
        //para añadir valores se usa: sans.push_back(numerito_que_quieres_añadir);
        vector<float> sans;

        queue<int> pendiente; //FIFO :o y queremos que parta con la raíz
        pendiente.push(0);

        while(!pendiente.empty()){
            //así avanzas una queue de C++
            int idx = pendiente.front();
            pendiente.pop();
            
            Nodo actual = obtenerIndice(idx); //aquí leemos el archivo

            //for cada hijo en actual.hijos (son actual.k hijos):

            // 1. si el rectangulito del hijo está contenido en el nuestro aka se_intersectan():
            //      - si es una hoja (valor == -1), guardar su x1, y1 con sans.push_back( double )
            //      - si no es una hoja, hay que hacerle pendiente.push( valor ) para añadir su índice al FIFO
            //
            // 2. si el rectangulito NO está includo en nuestra búsqueda, ignorarlo brutalmente

            for(int i = 0; i < actual.k; i++){
                Hijo son = actual.hijos[i];
                if(se_intersectan(x1,y1,x2,y2,son)){
                    if(son.valor == -1){ //es hoja
                        sans.push_back(son.x1);
                        sans.push_back(son.y1);
                    }else{ //no es hoja, hay que revisar su índice
                        pendiente.push(son.valor);
                    }
                }

            }
        }

        //retorna el vector de coordenadas encontradas
        return sans;
    }

        struct QueryResult{
        int puntos;
        int diskreads;
    };

    QueryResult puntosConsulta(float x1, float y1, float x2, float y2){
        QueryResult qr;
        qr.puntos = encontrarPuntos(x1,y1,x2,y2).size() / 2; // cada punto tiene 2 coordenadas
        qr.diskreads = getReads();
        resetReads();
        return qr;
    }
    
    QueryResult QueryS(float s, int seed){

        vector<QuerySquare> cuadrados = generarCuadrados(s, CUADRADOS, seed);
        QueryResult qfinal;
        qfinal.puntos = 0;
        qfinal.diskreads = 0;
        
        for(int i = 0;i<cuadrados.size();i++){
            QuerySquare &qs = cuadrados[i];
            QueryResult qr = puntosConsulta(qs.x1, qs.y1, qs.x2, qs.y2);
            qfinal.puntos += qr.puntos;
            qfinal.diskreads += qr.diskreads;
        }
        return qfinal;
    }

};