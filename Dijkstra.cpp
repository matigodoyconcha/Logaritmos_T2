#include "structure.h"
#include <bits/stdc++.h>

using namespace std;

tuple<vector<double>,vector<ull>> Dijkstra(ull V ,vector<vector<NodoDist>> &Aristas,Estructura &Q, ull raiz){
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
    Q.heapify();

    // Paso 6
    while(!Q.empty()){
        // Parte 6.a
        NodoDist minimo = Q.pop();
        ull v = minimo.neighbor;
        //Parte 6.b
        for(NodoDist &vecino : Aristas[v]){
            ull u = vecino.neighbor;
            if (distancias[u] > distancias[v] + vecino.weight){
                distancias[u] = distancias[v] + vecino.weight;
                previos[u] = v;
                Q.decreaseKey(u,distancias[u]);	
            }
        }
    }
    //Paso 7
    return {distancias,previos};
}

