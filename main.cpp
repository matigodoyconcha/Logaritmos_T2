#include "graph.cpp"
#include "Testing.cpp"

void coutMean(const string& filename){
    ifstream infile("Testing/" + filename + ".txt");
    ofstream outfile("Testing/Promedios.txt", ios::app);
    ull sum = 0;
    ull n = 0;
    double x;
    while(infile >> x){
        sum += x;
        n++;
    }
    outfile << filename << ";" << sum/n << endl;
    infile.close();
    outfile.close();
}


int main(){
    ofstream outfile("Testing/Promedios.txt");
    outfile << "Estructura;i;j;Promedio" << endl;
    outfile.close();
    for (int i = 10; i <15 ; i+=2){
        for(int j = 16 ; j<=22 ;j++){
            int n = pow(2,i);
            if(pow(2,j) > n*(n-1)/2 ){
                cout << "Nos pasamos del limite" << endl;
                break;
            }
            string h = "Heap;" + to_string(i) + ";" + to_string(j);
            string f = "Fibonacci;" + to_string(i)+ ";" + to_string(j);
            ofstream file_h("Testing/" + h + ".txt");
            ofstream file_f("Testing/" + f + ".txt");
            file_h.close();
            file_f.close();
            for(int k = 0; k < 50; k++){
                vector<vector<NodoDist>> graph = graphGen(i, j);
                //cout << "Grafo generado" << endl;
                //cout << "Fibonacci" << endl;
                //cout << "Heap" << endl;
                Heap_Test(graph,i,j,h);
                Fibonacci_Test(graph,i,j,f);
                //cout << "Dijkstra ejecutado" << endl;
            }
            coutMean(h);
            coutMean(f);
            cout << "Terminamos iteracion" << i << "," << j << endl;
        }
        
    }
    return 0;
};

/* int main(){
    cola_fibonacci *cola = new cola_fibonacci(pow(2,14));
    Heap *heap = new Heap();
    vector<vector<NodoDist>> graph = graphGen(14, 22);
    cout << "Heap:" << endl;
    tuple <vector<double>, vector<ull>> res = Dijkstra(pow(2,14), graph, *heap,  0);
    cout << "Fibonacci:" << endl;
    tuple <vector<double>, vector<ull>> res2 = Dijkstra(pow(2,14), graph, *cola, 0);
    for (int i = 0; i < 1024; i++){
        if (get<0>(res)[i] != get<0>(res2)[i]){
            cout << "Error en distancia " << i << endl;
            cout << get<0>(res)[i] << " " << get<0>(res2)[i] << endl;
        }
        if (get<1>(res)[i] != get<1>(res2)[i]){
            cout << "Error en previo" << i << endl;
        }
    }
    return 0;
} */