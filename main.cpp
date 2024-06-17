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
                Heap_Test(graph,i,j,h);
                Fibonacci_Test(graph,i,j,f);
            }
            coutMean(h);
            coutMean(f);
            cout << "Terminamos iteracion" << i << "," << j << endl;
        }
        
    }
    return 0;
};