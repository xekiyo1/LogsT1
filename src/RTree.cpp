#include "headers.h"
#include "./util/RandomSquare/RandomSquare.h"
using namespace std;

/// Dirección donde están guardados los RTrees
const string T_PATH = "bin/trees/";

/**
 * Clase que gestiona la apertura de un RTree, la cuenta total de lecturas a disco y realiza la búsqueda de puntos en el mismo.
 */
class RTree{
private:
    /// Gestor del archivo binario que contiene al RTree
    fstream file;
    /// Cuenta de lecturas a disco, aumentado en uno en cada llamado de "obtenerIndice"
    unsigned int diskreads = 0; //para medir las I/Os
public:
    /**
     * Establece un archivo binario en T_PATH como el RTree a utilizar.
     * @param nombre_archivo Nombre del archivo (incluyendo extensión) que contiene el RTree deseado. Se busca desde T_PATH.
     */
    void abrirArchivo(const string &nombre_archivo){
        file = fstream(T_PATH + nombre_archivo, std::ios::in);
        if(!file.is_open()) throw logic_error("RTree:: no se abrió el RTree");
        resetReads();
    }

    /**
     * Inicializa un RTree con un archivo de origen ya establecido.
     * @param nombre_archivo Nombre del archivo (incluyendo extensión) con el RTree a usar. Se busca desde T_PATH.
     */
    RTree(const string &nombre_archivo){
        diskreads = 0;
        abrirArchivo(nombre_archivo);
    }

    /**
     * Cierra y guarda el archivo vinculado a esta instancia de RTree.
     */
    void cerrarArchivo() {file.close();}

    /** Retorna la cantidad de lecturas de disco realizadas en el archivo del RTree actual. */
    unsigned int getReads() {return diskreads;}

    /** Limpia la variable que guarda las lecturas de disco, estableciéndola en cero. */
    void resetReads() {diskreads = 0;}

    /**
     * Obtiene el Nodo 'i' (indexado desde el cero) a partir del archivo referenciado en esta instancia de RTree,
     * lo que además suma una lectura de disco.
     * @param i Índice del Nodo que se quiere recuperar.
     * @return La instancia de Nodo almacenada en la posición 'i' del archivo.
     */
    Nodo obtenerIndice(unsigned long long i){
        Nodo extraido;
        file.seekg(i * sizeof(Nodo));
        file.read(reinterpret_cast<char *>(&extraido), sizeof(Nodo));
        diskreads++;
        return extraido;
    }

    //int cantidadNodos(); //no creo que se necesite

    /**
     * Función auxiliar que comprueba si una instancia de Hijo tiene su MBB parcialmente contenida en un área específica.
     * Es decir, comprueba intersección de un rectángulo con un Hijo.
     * @param x1 Cota inferior del eje X en los puntos a buscar.
     * @param y1 Cota inferior del eje Y en los puntos a buscar.
     * @param x2 Cota superior del eje X en los puntos a buscar.
     * @param y2 Cota superior del eje Y en los puntos a buscar.
     * @param son Instancia de Hijo que comprobará intersección con el área dada.
     * @return True la MBB del Hijo intersecta con el área dada. False en caso contrario.
     */
    static bool se_intersectan(float x1, float y1, float x2, float y2, Hijo &son){
        return !(son.x2 < x1 || son.x1 > x2 || son.y2 < y1 || son.y1 > y2);
    }

    /**
     * Realiza una búsqueda en el archivo de RTree vinculado a esta instancia, guardando todos los puntos
     * encontrados en un vector.
     * @param x1 Cota inferior del eje X en los puntos a buscar.
     * @param y1 Cota inferior del eje Y en los puntos a buscar.
     * @param x2 Cota superior del eje X en los puntos a buscar.
     * @param y2 Cota superior del eje Y en los puntos a buscar.
     * @return Un vector de floats, donde las coordenadas (x,y) de un punto 'i' están en las posiciones 2i y 2i+1 respectivamente.
     */
    vector<float> encontrarPuntos(float x1, float y1, float x2, float y2){
        //aquí guardamos la respuesta, la idea es guardar los puntos como [x1, y1, x2, y2, x3, y3 ...]
        vector<float> sans;

        queue<int> pendiente; //BFS
        pendiente.push(0);

        while(!pendiente.empty()){
            int idx = pendiente.front();
            pendiente.pop();
            
            Nodo actual = obtenerIndice(idx); //aquí es donde realmente leemos el archivo

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

    /**
     * Realiza una consulta en el RTree y empaqueta los resultados en un QueryResult, descartando
     * los puntos obtenidos para, en cambio, almacenar la cantidad de puntos y lecturas de disco
     * detectados.
     * @param x1 Cota inferior del eje X en los puntos a buscar.
     * @param y1 Cota inferior del eje Y en los puntos a buscar.
     * @param x2 Cota superior del eje X en los puntos a buscar.
     * @param y2 Cota superior del eje Y en los puntos a buscar.
     * @return QueryResult conteniendo la cantidad de puntos encontrados y lecturas de disco realizadas.
     */
    QueryResult puntosConsulta(float x1, float y1, float x2, float y2){
        QueryResult qr;
        qr.puntos = encontrarPuntos(x1,y1,x2,y2).size() / 2; // cada punto tiene 2 coordenadas
        qr.diskreads = getReads();
        resetReads();
        return qr;
    }

    /**
     * Genera una cantidad de cuadrados aleatorios mediante la función generarCuadrados()
     * con un tamaño dado, y retorna la cantidad de puntos encontrados y lecturas a disco realizadas
     * al usar cada uno como consulta de RTree, guardando los resultados en un vector.
     * @param s Tamaño de los cuadrados a generar para las consultas.
     * @param seed Semilla para la pseudo-aleatoriedad de generarCuadrados.
     * @return Vector de QueryResult conteniendo los resultados de cada consulta individualmente.
     */
    vector<QueryResult> QueryS(float s, int seed){

        vector<QuerySquare> cuadrados = generarCuadrados(s, CUADRADOS, seed);
        vector<QueryResult> qfinal;
        
        for(unsigned int i = 0;i<cuadrados.size();i++){
            QuerySquare &qs = cuadrados[i];
            qfinal.push_back(puntosConsulta(qs.x1, qs.y1, qs.x2, qs.y2));
        }
        return qfinal;
    }
};