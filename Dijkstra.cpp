#include "structure.h"
#include <vector>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

tuple<vector<double>,vector<ull>> Dijkstra(ull V ,vector<vector<NodoDist>> Aristas,Estructura &Q, ull raiz){
    // Paso 1
    vector<double> distancias(V);
    vector<ull> previos(V);

    // Paso 3
    ull nodo_previo = raiz; //(Id nodo previo de la raiz)
    previos[raiz] = nodo_previo;
    distancias[raiz]= 0;
    NodoDist tupla = {raiz,0.0};
    Q.push(tupla);

    // Paso 4
    //Iteramos hasta uno antes de la raiz
    for(ull i = 0; i< raiz; i++){
        distancias[i] = numeric_limits<double>::max();
        NodoDist tupla = {i,numeric_limits<double>::max()};
        Q.push(tupla);
    }
    // Iteramos desde la raiz (sin incluirla) hasta V
    for(ull i = raiz+1;i< V;i++ ){
        distancias[i] = numeric_limits<double>::max();
        NodoDist tupla = {i,numeric_limits<double>::max()};
        Q.push(tupla);
    }

    // Paso 5
    auto start = chrono::high_resolution_clock::now();
    Q.heapify();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    //cout << "Tiempo de heapify: " << duration.count() << " microsegundos" << endl;

    auto pop_time = chrono::duration_cast<chrono::microseconds>(start - start);
    auto decrease_time = chrono::duration_cast<chrono::microseconds>(start - start);
    ull pop_n = 0;
    ull decrease_n = 0;
    // Paso 6
    while(!Q.empty()){
        // Parte 6.a
        start = chrono::high_resolution_clock::now();
        NodoDist minimo = Q.pop();
        pop_n++;
        end = chrono::high_resolution_clock::now();
        pop_time += chrono::duration_cast<chrono::microseconds>(end - start);
        ull v = minimo.neighbor;
        vector<NodoDist> vecinos = Aristas[v];
        //Parte 6.b
        for(NodoDist vecino : vecinos){
            ull u = vecino.neighbor;
            if(distancias[u]> distancias[v]+ vecino.weight){
                distancias[u] = distancias[v]+ vecino.weight;
                previos[u] = v;
                start = chrono::high_resolution_clock::now();
                Q.decreaseKey(u,distancias[u]);
                end = chrono::high_resolution_clock::now();
                decrease_time += chrono::duration_cast<chrono::microseconds>(end - start);
                decrease_n++;
            }
        }
    }
    //cout << "Tiempo de pop: " << pop_time.count() << " microsegundos" << endl;
    //cout << "Tiempo de decreaseKey: " << decrease_time.count() << " microsegundos" << endl;
    //Paso 7
    return {distancias,previos};
}
