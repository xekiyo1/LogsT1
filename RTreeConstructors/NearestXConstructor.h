//
// Created by ignac on 03-05-2026.
//

#ifndef LOGST1_NEARESTXCONSTRUCTOR_H
#define LOGST1_NEARESTXCONSTRUCTOR_H
#include "RTreeConstructor.h"
struct NearestXConstructor : AbstractRtreeConstructor{
    string name = "NearestX";
private:
    template <typename TipoNodo>
    void groupGeneric(vector<TipoNodo> &og, vector<NodoCalculador> &dest);
protected:
    void groupNodos(vector<Hijo> &og, vector<NodoCalculador> &dest) override{
        groupGeneric<Hijo>(og, dest);
    }
    void groupNodos(vector<NodoCalculador> &og, vector<NodoCalculador> &dest) override{
        groupGeneric<NodoCalculador>(og, dest);
    }
};

#endif //LOGST1_NEARESTXCONSTRUCTOR_H
