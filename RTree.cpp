#include "config.hp"
using namespace std;

class RTree{
private:
    fstream file;
public:
    void abrirArchivo(string nombre_archivo){
        file = fstream(filename, std::ios::in);
        if(!file.is_open()) throw logic_error("no se abrió el Rtree :c");
    }

    void cerrarArchivo() {file.close();}

    Rtree(string nombre_archivo){abrirArchivo(nombre_archivo);}

    //busca un nodo según su índice
    Nodo obtenerIndice(unsigned long long i){
        Nodo extraido;
        file.seekg(i * sizeof(Nodo));
        file.read(reinterpret_cast<char *>(&extraido), sizeof(Nodo));
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
            int idx = pendiente.top();
            pendiente.pop();
            
            Nodo actual = obtenerIndice(idx); //aquí leemos el archivo

            //for cada hijo en actual.hijos (son actual.k hijos):

            // 1. si el rectangulito del hijo está contenido en el nuestro aka se_intersectan():
            //      - si es una hoja (valor == -1), guardar su x1, y1 con sans.push_back( double )
            //      - si no es una hoja, hay que hacerle pendiente.push( valor ) para añadir su índice al FIFO
            //
            // 2. si el rectangulito NO está includo en nuestra búsqueda, ignorarlo brutalmente

            for(;;){

            }
        }

        //retorna el vector de coordenadas encontradas
        return sans;
    }
};
