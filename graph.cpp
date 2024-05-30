#include <bits/stdc++.h>
#include "structure.h"
using namespace std;


bool hasEdge(vector<NodoDist> &vec, ull v) {
    for (auto &i : vec) {
        if (i.neighbor == v) {
            return true;
        }
    }
    return false;
}

vector<vector<NodoDist>> graphGen(ull i, ull j) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    ull n = pow(2, i);
    ull m = pow(2, j);

    vector<vector<NodoDist>> graph(n);
    for (ull a = 0; a < n; a++) {
        graph[a].resize(n);
    }

    // Agregar v - 1 aristas para formar un árbol cobertor
    for (ull a = 1; a < n; a++) {
        ull b = gen() % a;
        double weight = dis(gen) + 0.000001; // Peso aleatorio en el rango (0..1]
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight});
    }

    // Añadir las 2j - (v - 1) aristas restantes
    for (ull a = 0; a < m - (n - 1); a++) {
        ull u = gen() % n;
        ull v = gen() % n;
        while (u == v || hasEdge(graph[u], v)) {
            u = gen() % n;
            v = gen() % n;
        }
        double weight = dis(gen) + 0.000001; // Peso aleatorio en el rango (0..1]
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }
    return graph;
}

