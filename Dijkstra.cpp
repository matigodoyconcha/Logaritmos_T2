#include "structure.h"
#include <vector>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

tuple<vector<double>,vector<ull>> Dijkstra(ull V ,vector<vector<NodoDist>> Aristas,Estructura &Q, ull raiz){
    // Paso 1
    vector<double> distancias(V);
    vector<ull> previos(V);

    // Paso 3
    ull nodo_previo = -1; //(Id nodo previo de la raiz)
    previos[raiz] = nodo_previo;
    distancias[raiz]= 0;
    NodoDist tupla = {0,raiz};
    Q.push(tupla);

    // Paso 4
    //Iteramos hasta uno antes de la raiz
    for(ull i = 0; i< raiz; i++){
        distancias[i] = ULLONG_MAX;
        NodoDist tupla = {ULLONG_MAX,i};
        Q.push(tupla);
    }
    // Iteramos desde la raiz (sin incluirla) hasta V
    for(ull i = raiz+1;i< V;i++ ){
        distancias[i] = ULLONG_MAX;
        NodoDist tupla = {ULLONG_MAX,i};
        Q.push(tupla);
    }

    // Paso 5
    Q.heapify();

    // Paso 6
    while(!Q.empty()){
        // Parte 6.a
        NodoDist minimo = Q.pop();
        ull v = minimo.neighbor;
        vector<NodoDist> vecinos = Aristas[v];
        //Parte 6.b
        for(NodoDist vecino : vecinos){
            ull u = vecino.neighbor;
            if(distancias[u]> distancias[v]+ vecino.weight){
                distancias[u] = distancias[v]+ vecino.weight;
                previos[u] = v;
                Q.decreaseKey(u,distancias[u]);
            }
        }
    }
    //Paso 7
    return {distancias,previos};
}
