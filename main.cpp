#include "graph.cpp"
#include "Testing.cpp"

int main(){
    for (int i = 10; i <15 ; i+=2){
        for(int j = 16 ; j<22 ;j++){
            int n = pow(2,i);
            if(pow(2,j) > n*(n-1)/2 ){
                cout << "Nos pasamos del limite" << endl;
                break;
            }
            for(int k = 0; k < 50; k++){
                vector<vector<NodoDist>> graph = graphGen(10, 16);
                //cout << "Grafo generado" << endl;
                string h = "Test_Heap " + to_string(i) + "," + to_string(j);
                string f = "Test_Fibonacci " + to_string(i)+ "," + to_string(j);
                Heap_Test(graph,i,j,h);
                Fibonacci_Test(graph,i,j,f);
                //cout << "Dijkstra ejecutado" << endl;
            }
            cout << "Terminamos iteracion" << i << "," << j << endl;
        }
        
    }
    return 0;
};