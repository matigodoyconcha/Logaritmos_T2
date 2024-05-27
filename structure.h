#include <tuple>
typedef unsigned long long ull;

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

        virtual void push(NodoDist); //Lo inserta como un array!
        virtual void heapify(); //Lo convierte en una Cola de Prioridad!
        virtual int empty(); //Dice si ta vacio o no!
        virtual NodoDist pop();
        virtual void decreaseKey(ull nodo,double newDistance);
};

#endif