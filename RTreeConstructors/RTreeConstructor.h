//
// Created by ignac on 03-05-2026.
//

#ifndef LOGST1_RTREECONSTRUCTOR_H
#define LOGST1_RTREECONSTRUCTOR_H
#include "../config.hp"

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
    virtual void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest);
    virtual void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest);
public:
    void CreateRTree(string infile, string outfile);
};

#endif //LOGST1_RTREECONSTRUCTOR_H
