#include <tuple>
typedef long long ull;

#ifndef STRUCTURE_H
#define STRUCTURE_H


class NodoDist{
    public:
        ull neighbor;
        double weight;
};

class Estructura{
    public:

        virtual void push(NodoDist tupla) = 0; //Lo inserta como un array!
        virtual void heapify()=0; //Lo convierte en una Cola de Prioridad!
        virtual int empty()=0; //Dice si ta vacio o no!
        virtual NodoDist pop()=0;
        virtual void decreaseKey(ull nodo,double newDistance)=0;

        virtual ~Estructura() {}
};

#endif
