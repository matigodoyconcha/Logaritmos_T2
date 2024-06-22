#include "structure.h"
#include <bits/stdc++.h>

using namespace std;

struct node{
        double key;
        NodoDist data;
        int degree;
        bool mark;
        node *child, *parent, *prev, *next;
};

class cola_fibonacci : public Estructura{
    public:
        vector<node *> nodes;
        node *min = nullptr;
        int n = 0;

        // Erase a node from his double linked list
        void erase(node *nodeToEliminate){
            nodeToEliminate->prev->next = nodeToEliminate->next;
            nodeToEliminate->next->prev = nodeToEliminate->prev;
        }

        // Insert a node into a double linked list
        void insert(node *listToInsert, node *nodeToInsert){
            node *temp = listToInsert->prev;
            nodeToInsert->next = listToInsert;
            nodeToInsert->prev = temp;
            listToInsert->prev = nodeToInsert;
            temp->next = nodeToInsert;
        }
        // Push a node into an array waiting to be inserted into the fibonacci heap
        void push(NodoDist nodo) override {
            if (nodo.neighbor >= nodes.size()){
                nodes.resize(nodo.neighbor + 1);
            }
            node *temp = new node();
            temp->key = nodo.weight;
            temp->data = nodo;
            temp->degree = 0;
            temp->mark = false;
            temp->child = nullptr;
            temp->parent = nullptr;
            temp->prev = nullptr;
            temp->next = nullptr;
            nodes[nodo.neighbor] = temp;
            n++;
            insertInHeap(temp);
        }

        // Insert a node into the fibonacci heap
        void insertInHeap(node *nodeToInsert){
            nodeToInsert->mark = false;
            nodeToInsert->parent = nullptr;
            if (min == nullptr){
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
        
        // Returns true if the heap is empty
        int empty() override{
            return min == nullptr;
        }

        // Returns the minimum node of the heap
        NodoDist pop() override{
            node *z = min;
            node *temp, *x;
            if (z != nullptr){
                x = z->child;
                for (int i = 0; i <z->degree; i++){
                    temp = x->next;
                    insertInHeap(x);
                    x->parent = nullptr;
                    x = temp;
                }
                erase(z);
                if (z == z->next){
                    min = nullptr;
                }
                else{
                    min = z->next;
                    consolidate();
                }
                n--;
            }
            return z->data;
        }

        // Consolidate the fibonacci heap to just have one heap with each degree
        void consolidate(){
            double phi = (1 + sqrt(5))/2;
            int top = log(n)/log(phi) + 1;
            vector<node*> A(top, nullptr);
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
                while (A[d] != nullptr){
                    y = A[d];
                    if (x->key > y->key){
                        temp = x;
                        x = y;
                        y = temp;
                    }
                    heap_link(y, x);
                    A[d] = nullptr;
                    d++;
                }
                A[d] = x;
                x = next;
            }
            min = nullptr;
            for (int i = 0; i < top; i++){
                if (A[i] != nullptr){
                    if (min == nullptr){
                        min = A[i];
                        min->prev = min;
                        min->next = min;
                    }
                    else{
                        insertInHeap(A[i]);
                    }
                }
            }
        }

        // Make node y the child of node x
        void heap_link(node *y, node *x){
            erase(y);
            if (x->child == nullptr){
                x->child = y;
                y->prev = y;
                y->next = y;
            }
            else{
                insert(x->child, y);
            }
            y->parent = x;
            y->mark = false;
            x->degree++;
        }

        // Convert the array into a fibonacci heap
        void heapify() override{
        }

        // Decrease the key of a node
        void decreaseKey(ull nodo, double newDistance) override{
            node *x = nodes[nodo];
            if (x->key < newDistance){
                return;
            }
            x->key = newDistance;
            x->data.weight = newDistance;
            node *y = x->parent;
            if (y != nullptr && x->key < y->key){
                cut(x, y);
                cascading_cut(y);
            }
        }

        // Cut a node from his parent
        void cut(node *x, node *y){
            y->degree--;
            if (y->degree == 0){
                y->child = nullptr;
            } else {
                if (y->child == x){
                    y->child = x->next;
                }
                erase(x);
            }
            insertInHeap(x);
        }

        // Cut a node from his parent and make the parent the child of the root
        void cascading_cut(node *y){
            node *z = y->parent;
            if (z != nullptr){
                if (y->mark == false){
                    y->mark = true;
                } else{
                    cut(y, z);
                    cascading_cut(z);
                }
            }
        }
};