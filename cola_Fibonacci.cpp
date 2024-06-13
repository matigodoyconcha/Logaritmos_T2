#include "structure.h"
#include <bits/stdc++.h>

using namespace std;

class node{
    public:
        double key;
        NodoDist data;
        int degree = 0;
        bool mark = false;
        node *child, *parent, *prev, *next;
};

// Insert a node into a double linked list
void insert(node *listToInsert, node *nodeToInsert){
    node *temp = listToInsert->prev;
    nodeToInsert->next = listToInsert;
    nodeToInsert->prev = temp;
    listToInsert->prev = nodeToInsert;
    temp->next = nodeToInsert;
}

// Erase a node from his double linked list
void erase(node *nodeToEliminate){
        nodeToEliminate->prev->next = nodeToEliminate->next;
        nodeToEliminate->next->prev = nodeToEliminate->prev;
    }

class cola_fibonacci : public Estructura{
    public:
        vector<NodoDist> heap;
        vector<node *> nodes;
        node *min = NULL;
        int n = 0;
        node raiz;
        node *toFree;

        // Push a node into an array waiting to be inserted into the fibonacci heap
        void push(NodoDist nodo) override {
            heap.push_back(nodo);
            n++;
        }

        // Insert a node into the fibonacci heap
        void insertInHeap(node *nodeToInsert){
            if (min == NULL){
                nodeToInsert->prev = nodeToInsert;
                nodeToInsert->next = nodeToInsert;
                min = nodeToInsert;
            }
            else{
                insert(min, nodeToInsert);
                if (nodeToInsert->key < min->key){
                    min = nodeToInsert;
                }
            }
        }

        // Make the union of two fibonacci heaps into just this one
        void Union(cola_fibonacci *H2){
            if (H2->min == NULL){
                return;
            }
            if (min == NULL){
                min = H2->min;
                n = H2->n;
                return;
            }
            node *temp1 = min->next;
            node *temp2 = H2->min->prev;
            min->next = H2->min;
            H2->min->prev = min;
            temp2->next = temp1;
            temp1->prev = temp2;
            if (H2->min->key < min->key){
                min = H2->min;
            }
            n += H2->n;
        }

        // Returns true if the heap is empty
        int empty() override{
            return min == NULL;
        }

        // Returns the minimum node of the heap
        NodoDist pop() override{
            node *z = min;
            node *temp, *x;
            if (z != NULL){
                x = z->child;
                    for (int i = 0; i <z->degree; i++){
                        temp = x->next;
                        insertInHeap(x);
                        x->parent = NULL;
                        x = temp;
                    }
                erase(z);
                if (z == z->next){
                    min = NULL;
                }
                else{
                    min = z->next;
                    consolidate();
                }
                n--;
            }
            NodoDist toReturn = z->data;
            return toReturn;
        }

        // Consolidate the fibonacci heap to just have one heap with each degree
        void consolidate(){
            double phi = (1 + sqrt(5)) / 2;
            int top = log(n)/log(phi);
            vector<node*> A(top, NULL);
            node *x = min;
            node *next;
            node *y;
            node *temp;
            int d;
            int InHeap = 1;
            node *toCount = x->next;
            while (toCount != x){
                InHeap++;
                toCount = toCount->next;
            }
            for (int i = 0; i < InHeap; i++){
                next = x->next;
                d = x->degree;
                while (A[d] != NULL){
                    y = A[d];
                    if (x->key > y->key){
                        temp = x;
                        x = y;
                        y = temp;
                    }
                    heap_link(y, x);
                    A[d] = NULL;
                    d++;
                }
                A[d] = x;
                x = next;
            }
            min = NULL;
            for (int i = 0; i < top; i++){
                if (A[i] != NULL){
                    if (min == NULL){
                        min = A[i];
                        min->prev = min;
                        min->next = min;
                    }
                    else{
                        insertInHeap(A[i]);
                        if (A[i]->key < min->key){
                            min = A[i];
                        }
                    }
                }
            }
        }

        // Make node y the child of node x
        void heap_link(node *y, node *x){
            erase(y);
            if (x->child == NULL){
                x->child = y;
                y->prev = y;
                y->next = y;
                y->parent = x;
            }
            else{
                insert(x->child, y);
                y->parent = x;
            }
            y->mark = false;
            x->degree++;
        }

        // Convert the array into a fibonacci heap
        void heapify() override{
            nodes.resize(n);
            node *locura = new node[n];
            toFree = locura;
            for (int i = 0; i < n; i++){
                locura[i] = node();
                locura[i].key = heap[i].weight;
                locura[i].data = heap[i];
                nodes[heap[i].neighbor] = locura;
                insertInHeap(&locura[i]);
            }
        }

        // Decrease the key of a node
        void decreaseKey(ull nodo, double newDistance) override{
            node *x = nodes[nodo];
            if (newDistance > x->key){
                return;
            }
            x->key = newDistance;
            x->data.weight = newDistance;
            node *y = x->parent;
            if (y != NULL && x->key < y->key){
                cut(x, y);
                cascading_cut(y);
            }
            if (x->key < min->key){
                min = x;
            }
        }

        // Cut a node from his parent
        void cut(node *x, node *y){
            y->degree--; 
            if (y->degree == 0){
                y->child = NULL;
            } else {
                if (y->child == x){
                    y->child = x->next;
                }
                erase(x);
            }
            insertInHeap(x);
            x->parent = NULL;
            x->mark = false;
        }

        // Cut a node from his parent and make the parent the child of the root
        void cascading_cut(node *y){
            node *z = y->parent;
            if (z != NULL){
                if (y->mark == false){
                    y->mark = true;
                }
                else{
                    cut(y, z);
                    cascading_cut(z);
                }
            }
        }
};