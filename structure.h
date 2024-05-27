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

        void push(NodoDist); //Lo inserta como un array!
        void heapify(); //Lo convierte en una Cola de Prioridad!
        int empty(); //Dice si ta vacio o no!
        NodoDist pop();
        void decreaseKey(ull nodo,double newDistance);
};

#endif