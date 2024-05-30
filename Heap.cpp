#include "structure.h"
#include <vector>
#include <iostream>
using namespace std;

class Heap: public Estructura{
public:
    // Array incial, donde se insertan los elementos en tiempo constante
    vector<NodoDist> array;
    // Array para saber ubicacion del nodo.
    vector<ull> nodos;
    ull contador_nodos = 0;

    void push(NodoDist tupla) override {
        array.push_back(tupla); // Insert at the end
        contador_nodos++;
        if (tupla.neighbor >= nodos.size()) {
            nodos.resize(tupla.neighbor + 1, -1);
        }
        nodos[tupla.neighbor] = array.size() - 1;
    }

    // Lo convierte en una Cola de Prioridad!
    void heapify() override {
        // Hay que actualizar el array de nodos!
        nodos.resize(contador_nodos);
        ull n = array.size();
        for (int j = array.size() / 2 - 1; j >= 0; j--) {
            int i = j;
            while (true) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int smallest = i;

                if (left < n && array[left].weight < array[smallest].weight)
                    smallest = left;
                if (right < n && array[right].weight < array[smallest].weight)
                    smallest = right;

                if (smallest == i) {
                    break;
                }

                // Hacemos swap
                swap(array[i], array[smallest]);
                nodos[array[i].neighbor] = i;
                nodos[array[smallest].neighbor] = smallest;
                i = smallest;
            }
        }
    }

    // Dice si está vacío o no!
    int empty() override {
        return array.size() == 0;
    }

    NodoDist pop() override {
        NodoDist menor = array[0];
        ull n = array.size();
        array[0] = array[n - 1];
        array.pop_back(); // Remove the last node
        n--;
        // Restore the heap property by sifting down the new root
        int i = 0;
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && array[left].weight < array[smallest].weight)
                smallest = left;
            if (right < n && array[right].weight < array[smallest].weight)
                smallest = right;

            if (smallest == i) {
                break;
            }

            // Swap elements
            swap(array[i], array[smallest]);
            nodos[array[i].neighbor] = i;
            nodos[array[smallest].neighbor] = smallest;
            i = smallest;
        }
        nodos[menor.neighbor] = -1;
        return menor;
    }

    // Cambia la distancia y reordena el Heap de ser necesario
    void decreaseKey(ull nodo, double newDistance) override {
        ull i = nodos[nodo];
        array[i].weight = newDistance;
        // Restore the heap property by sifting up the updated node
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (array[i].weight < array[parent].weight) {
                NodoDist aux = array[i];
                array[i] = array[parent];
                array[parent] = aux;
                nodos[array[i].neighbor] = i;
                nodos[array[parent].neighbor] = parent;
                i = parent;
            } else {
                break;
            }
        }
    }
};