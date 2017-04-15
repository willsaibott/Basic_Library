#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "List.h"

class HeuristicTable : public List<Weight>{
public:
    HeuristicTable() : List<Weight>(){}

    void runIteration(Weight *(*function)(Weight*, int, int), Weight* p,  int iteration, int n){
        this->erase();
        this->vectorToList(function(p, iteration, n), n);
    }

};

#endif // HEURISTIC_H
