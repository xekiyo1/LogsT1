#ifndef RTREECONSTRUCTOR_H
#define RTREECONSTRUCTOR_H
#include "../config.hp"
#include <bits/stdc++.h> 
using namespace std;

class AbstractTreeConstructor{
    public:
        ofstream resultado;
        int cantidadNodos;

        /// Overload que permite diferenciar entre la ordenación de Hijo y de NodoCalculador.
        /// Necesario para diferenciar las ordenaciones en groupNodos.
        void sorterX(vector<Hijo>::iterator begin, vector<Hijo>::iterator end);
        void sorterX(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end);
        void sorterY(vector<Hijo>::iterator begin, vector<Hijo>::iterator end);
        void sorterY(vector<NodoCalculador>::iterator begin, vector<NodoCalculador>::iterator end);

        /// Función que agrupa los nodos de og y añade los resultantes a dest, que puede ser
        /// vector de Hijo o vector de NodoCalculador.
        /// También los castea y añade al vector de nodos finales.
        virtual void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) {};
        virtual void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) {};

        void CreateRTree(string infile, string outfile, int N=INT_MAX);
        string name;
};



class NearestXConstructor : public AbstractTreeConstructor{
    string name = "NearestX";
public:
    template <typename TipoNodo>
    void groupGeneric(vector<TipoNodo> &og, vector<NodoCalculador> &dest);

    void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest);
    void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest);
};


class STRConstructor : public AbstractTreeConstructor{
    string name = "STR";
private:
    template <typename TipoNodo>
    void groupGeneric(vector<TipoNodo> &bulk, vector<NodoCalculador> &dest);
protected:
    void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest);
    void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest);
};
#endif // RTREECONSTRUCTOR_H
