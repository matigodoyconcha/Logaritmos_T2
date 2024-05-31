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
    node *temp = listToInsert->next;
    nodeToInsert->prev = listToInsert;
    nodeToInsert->next = temp;
    listToInsert->next = nodeToInsert;
    temp->prev = nodeToInsert;
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

        // Push a node into an array waiting to be inserted into the fibonacci heap
        void push(NodoDist nodo) override {
            heap.push_back(nodo);
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
            if (z != NULL){
                if (z->child != NULL){
                    vector<node *> children;
                    node *temp = z->child;
                    children.push_back(temp);
                    temp = temp->next;
                    while (temp!= z->child){
                        children.push_back(temp);
                        temp = temp->next;
                    }
                    for (int i = 0; i < children.size(); i++){
                        insertInHeap(children[i]);
                        children[i]->parent = NULL;
                    }
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
            NodoDist temp = z->data;
            return temp;
        }

        // Consolidate the fibonacci heap to just have one heap with each degree
        void consolidate(){
            vector<node*> A(n, NULL);
            node *x = min;
            vector <node *> newHeap;
            newHeap.push_back(x);
            x = x->next;
            while (x != min){
                newHeap.push_back(x);
                x = x->next;
            }
            for (int i = 0; i < newHeap.size(); i++){
                x = newHeap[i];
                int d = x->degree;
                while (A[d] != NULL){
                    node *y = A[d];
                    if (x->key > y->key){
                        node *temp = x;
                        x = y;
                        y = temp;
                    }
                    heap_link(y, x);
                    A[d] = NULL;
                    d++;
                }
                A[d] = x;
            }
            min = NULL;
            for (int i = 0; i < n; i++){
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
            nodes.resize(heap.size()+1);
            for (int i = 0; i < heap.size(); i++){
                node *temp = new node();
                temp->key = heap[i].weight;
                temp->data = heap[i];
                nodes[temp->data.neighbor] = temp;
                insertInHeap(temp);
                n++;
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

/* int main(){
    cola_fibonacci *cola = new cola_fibonacci();
    NodoDist nodo;
    nodo.neighbor = 0;nodo.weight = 5;
    cola->push(nodo);
    nodo.neighbor = 1;nodo.weight = 1;
    cola->push(nodo);
    nodo.neighbor = 2;nodo.weight = 2;
    cola->push(nodo);
    nodo.neighbor = 3;nodo.weight = 3;
    cola->push(nodo);
    nodo.neighbor = 4;nodo.weight = 4;
    cola->push(nodo);
    nodo.neighbor = 5;nodo.weight = 0;
    cola->push(nodo);
    for (auto i : cola->heap){
        cout << i.weight << " ";
    }
    cout << endl;
    cout << "-------------------" << endl;
    cola->heapify();
    cout << cola->min->key << endl;
    node *temp = cola->min;
    for (int i = 0; i < cola->n; i++){
        cout << temp->key << " ";
        temp = temp->next;
    }
    cout << endl;
    cout << "-------------------" << endl;
    cout << cola->pop().neighbor << endl;
    cola->decreaseKey(4, 0);
    cout << cola->pop().neighbor << endl;
    cola->decreaseKey(3, 0);
    cout << cola->pop().neighbor << endl;
    cout << cola->pop().neighbor << endl;
    cout << cola->pop().neighbor << endl;
    cout << cola->pop().neighbor << endl;
    return 0;
} */