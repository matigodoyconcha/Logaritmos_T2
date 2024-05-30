#include "cola_Fibonacci.cpp"
#include "graph.cpp"
#include "Dijkstra.cpp"

int main(){
    for (int i = 0; i < 10; i++){
        Estructura *cola = new cola_fibonacci();
        vector<vector<NodoDist>> graph = graphGen(14, 16);
        cout << "Grafo generado" << endl;
        tuple<vector<double>,vector<ull>> res = Dijkstra(pow(2,14), graph, *cola, 0);
        cout << "Dijkstra ejecutado" << endl;
        vector<double> distancias = get<0>(res);
        vector<ull> previos = get<1>(res);
        delete cola;
    }
/*     for (int i = 0; i < distancias.size(); i++){
        cout << "Distancia al nodo " << i << ": " << distancias[i] << endl;
    }
    for (int i = 0; i < previos.size(); i++){
        cout << "Nodo previo al nodo " << i << ": " << previos[i] << endl;
    } */
    return 0;
};