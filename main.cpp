#include "cola_Fibonacci.cpp"
#include "graph.cpp"
#include "Dijkstra.cpp"

int main(){
    for (int i = 0; i < 50; i++){
        Estructura *cola = new cola_fibonacci();
        vector<vector<NodoDist>> graph = graphGen(10, 16);
        cout << "Grafo generado" << endl;
        tuple<vector<double>,vector<ull>> res = Dijkstra(pow(2,10), graph, *cola, 0);
        cout << "Dijkstra ejecutado" << endl;
        vector<double> distancias = get<0>(res);
        vector<ull> previos = get<1>(res);
        delete cola;
    }
    return 0;
};