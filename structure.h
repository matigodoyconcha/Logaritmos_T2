#include <tuple>
typedef long long ull;

#ifndef STRUCTURES_H
#define STRUCTURES_H

class Node{
    ull id;
};

class NodoDist{
    public:
        ull neighbor;
        double weight;
};

class Estructura{
    public:
        Node raiz;

        virtual void push(NodoDist tupla) = 0; //Lo inserta como un array!
        virtual void heapify()=0; //Lo convierte en una Cola de Prioridad!
        virtual int empty()=0; //Dice si ta vacio o no!
        virtual NodoDist pop()=0;
        virtual void decreaseKey(ull nodo,double newDistance)=0;

        virtual ~Estructura() {}
};

#endif