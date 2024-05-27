#include "structure.h"
#include <vector>
using namespace std;

class Nodo{
    public:
        NodoDist tupla;
        Nodo *izq;
        Nodo *der;
};

class Heap: public Estructura{
    public:
        //Array incial, donde se insertan los elementos en tiempo constante
        vector<NodoDist> array;

        //Raiz del heap
        Nodo *raiz = NULL;

        void push(NodoDist tupla) override {
            array.push_back(tupla); //Cambiar para que quede ordenado en el array!
        }

        //Lo convierte en una Cola de Prioridad!
        void heapify()override{

        }

         //Dice si ta vacio o no!
        int empty()override{
            return raiz == NULL;
        }


        NodoDist pop()override{
            Nodo menor = *raiz;
            //Sacar la raiz del heap y ordenar nuevamente


            return menor.tupla;
        }

        // Cambia la distancia y reordena el Heap de ser necesario
        void decreaseKey(ull nodo,double newDistance)override {

        }
};