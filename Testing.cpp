#include "Dijkstra.cpp"
#include <fstream>
#include <iostream>
#include "cola_Fibonacci.cpp"
#include "Heap.cpp"


using namespace std;
using namespace std::chrono;



void Heap_Test(vector<vector<NodoDist>>& graph, int i, int j, const string& filename){
    ofstream outfile("Testing/"+ filename + ".txt", ios::app);
    Estructura *heap = new Heap();
    auto start = high_resolution_clock::now();
    tuple<vector<double>, vector<ull>> res = Dijkstra(pow(2,i), graph, *heap, 0);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    outfile << duration << endl;
    delete heap;
    outfile.close();

}

void Fibonacci_Test(vector<vector<NodoDist>>& graph, int i, int j, const string& filename){
    ofstream outfile("Testing/"+ filename + ".txt", ios::app);
    cola_fibonacci *cola = new cola_fibonacci();
    auto start = high_resolution_clock::now();
    tuple<vector<double>, vector<ull>> res = Dijkstra(pow(2,i), graph, *cola, 0);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    outfile << duration << endl;
    delete cola->toFree;
    delete cola;
    outfile.close();

}