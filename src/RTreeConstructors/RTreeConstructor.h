#ifndef RTREECONSTRUCTOR_H
#define RTREECONSTRUCTOR_H
#include "../config.hp"
#include <bits/stdc++.h> 
using namespace std;

/**
 * Clase básica que contiene el algoritmo necesario para crear un RTree y guardarlo en un archivo,
 * excepto por la forma en la que agrupa los nodos.
 *
 * Contiene métodos con overloads para comparar nodos en la primera iteración (Hijo) y en las siguientes (NodoCalculador),
 * y la interfaz necesaria para agruparlos también mediante overload.
 * @see NearestXConstructor STRConstructor
 */
class AbstractTreeConstructor{
protected:
    /// Archivo en el que se escribe el RTree resultante.
    ofstream resultado;
    /// Cuenta total de Nodos que se han escrito al archivo.
    int cantidadNodos = 0;

    /**
     * Ordena un intervalo de nodos Hijo según su coordenada x. Se asume que x1 y x2 son iguales.
     * @param begin Inicio de la sección del vector a ordenar.
    * @param end Término de la sección del vector a ordenar
     */
    void sorterX(vector<Hijo>::iterator begin, vector<Hijo>::iterator end);
    /**
     * Ordena un intervalo de nodos NodoCalculador observando el punto central de su rectángulo,
     * específicamente según la coordenada X.
     * @param begin Inicio de la sección del vector a ordenar.
     * @param end Término de la sección del vector a ordenar
     */
    void sorterX(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end);
    /**
     * Ordena un intervalo de nodos Hijo según su coordenada y. Se asume que y1 e y2 son iguales.
     * @param begin Inicio de la sección del vector a ordenar.
     * @param end Término de la sección del vector a ordenar
     */
    void sorterY(vector<Hijo>::iterator begin, vector<Hijo>::iterator end);
    /**
     * Ordena un intervalo de nodos NodoCalculador observando el punto central de su rectángulo,
     * específicamente según la coordenada Y.
     * @param begin Inicio de la sección del vector a ordenar.
     * @param end Término de la sección del vector a ordenar
     */
    void sorterY(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end);

    /**
     * Toma un vector de Hijo y los condensa en NodosCalculadores, los cuales son almacenados
     * en un vector de preferencia.
     * @param og Vector de hijos que serán agrupados en NodoCalculador-es.
     * @param dest Vector de Nodos en donde se almacenará el resultado de agrupar los puntos.
     * @note El vector de Hijo podría ser modificado en el proceso.
     */
    virtual void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) {};
    /**
     * Toma un vector de NodoCalculador y los condensa en otros NodosCalculadores, los cuales
     * almacenan el índice de cada uno y son almacenados en un vector de preferencia.
     * @param og Vector de nodos que serán agrupados en NodoCalculador-es.
     * @param dest Vector de Nodos en donde se almacenará el resultado de agrupar los puntos.
     * @note El vector de donde se obtienen los Nodos podría ser modificado en el proceso.
     */
    virtual void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) {};
public:
    /// Nombre el RTree, utilizado principalmente para display.
    string name = "UnknownRTree";

    /**
     * Crea un Rtree a partir de los puntos de un archivo binario, guardando los nodos en un archivo de destino.
     *
     * La estrategia utilizada depende de la clase que herede de esta.
     * @param infile Nombre del archivo del que se extraerán los datos.
     * @param outfile Nombre del archivo en el que se escribirán los nodos resultantes.
     * @param N Cantidad máxima de puntos a extraer de infile.
     */
    void CreateRTree(string infile, string outfile, int N=INT_MAX);
};


/**
 * Clase encargada de crear RTrees con la estrategia Nearest-X.
 * Hereda de AbstractTreeConstructor y agrupa los nodos mediante comparaciones de sus coordenadas X.
 * @see AbstractTreeConstructor
 */
class NearestXConstructor : public AbstractTreeConstructor{
protected:
    /**
     * Toma un vector de nodos Hijo o NodoCalculador y los condensa en nodos más profundos.
     * En teoría puede recibir cualquier tparam, pero durante la ejecución llamará a sorterX
     * por lo que debe existir algún overload de esa función que acepte el tipo entregado.
     * @tparam TipoNodo Indica si los punteros son para el tipo Hijo o NodoCalculador.
     * @param og Vector de datos que contiene los Hijo o NodoCalculador a agrupar.
     * @param dest Vector de NodoCalculador en donde se guardarán los Nodos creados.
     */
    template <typename TipoNodo>
    void groupGeneric(vector<TipoNodo> &og, vector<NodoCalculador> &dest);

    /**
     * Toma un vector de Hijo y los condensa en NodosCalculadores según cercanía en la coordenada X.
     * @param og Vector de hijos que serán agrupados en NodoCalculador-es.
     * @param dest Vector de Nodos en donde se almacenará el resultado de agrupar los puntos.
     * @note El vector de Hijo podría ser modificado en el proceso.
     */
    void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) override;
    /**
     * Toma un vector de NodoCalculador y los condensa en otros NodosCalculadores según cercanía en coordenada X de su centro.
     * @param og Vector de nodos que serán agrupados en NodoCalculador-es.
     * @param dest Vector de Nodos en donde se almacenará el resultado de agrupar los puntos.
     * @note El vector de donde se obtienen los Nodos podría ser modificado en el proceso.
     */
    void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) override;
public:
    /// Nombre el RTree, utilizado principalmente para display.
    string name = "NearestX";
};

/**
 * Clase encargada de crear RTrees con la estrategia Sort-Tile-Recursive.
 * Hereda de AbstractTreeConstructor, agrupa los nodos mediante comparaciones de sus coordenadas X
 * y ordenando subgrupos por la coordenada Y.
 * @see AbstractTreeConstructor
 */
class STRConstructor : public AbstractTreeConstructor{
    /**
     * Toma un vector de nodos Hijo o NodoCalculador y los condensa en nodos más profundos.
     * En teoría puede recibir cualquier tparam, pero durante la ejecución llamará a sorterX y sorterY
     * por lo que debe existir algún overload de dichas funciones que acepten el tipo entregado.
     * @tparam TipoNodo Indica si los punteros son para el tipo Hijo o NodoCalculador.
     * @param bulk Vector de datos que contiene los Hijo o NodoCalculador a agrupar.
     * @param dest Vector de NodoCalculador en donde se guardarán los Nodos creados.
     */
    template <typename TipoNodo>
    void groupGeneric(vector<TipoNodo> &bulk, vector<NodoCalculador> &dest);
protected:
    /**
     * Toma un vector de Hijo y los condensa en NodosCalculadores, ordenando según la estrategia STR.
     * @param og Vector de hijos que serán agrupados en NodoCalculador-es.
     * @param dest Vector de Nodos en donde se almacenará el resultado de agrupar los puntos.
     * @note El vector de Hijo podría ser modificado en el proceso.
     */
    void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) override;
    /**
     * Toma un vector de NodoCalculador y los condensa en otros NodosCalculadores, ordenando según la estrategia STR.
     * @param og Vector de nodos que serán agrupados en NodoCalculador-es.
     * @param dest Vector de Nodos en donde se almacenará el resultado de agrupar los puntos.
     * @note El vector de donde se obtienen los Nodos podría ser modificado en el proceso.
     */
    void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) override;
public:
    /// Nombre el RTree, utilizado principalmente para display.
    string name = "STR";
};
#endif // RTREECONSTRUCTOR_H
