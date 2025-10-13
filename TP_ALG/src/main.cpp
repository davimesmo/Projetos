#include "../include/graph.hpp"
#include "../include/heap.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
//Mergesortzinho para ordenar o vetor de Arestas
void merge(std::vector<int> &v, size_t l, size_t m, size_t r) {
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (size_t i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (size_t j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];
    size_t i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &v, size_t l, size_t r) {
    if (l < r) {
        size_t m = l + (r - l) / 2;
        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);
        merge(v, l, m, r);
    }
}
int main(int argc, char const *argv[]){
    //Parte 1
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    long long* dist = g.Dijkstra(1);
    cout << "Parte 1: " << dist[n] << endl;
    //Parte 2
    //Calcula Dijkstra apartir do destino
    long long* distR = g.Dijkstra(n);
    vector<Aresta> arestas = g.getArestas();
    vector<Aresta> minimas;
    cout << "Parte 2:";
    //Processa as arestas "ida e volta"
    for(auto i : arestas){
        if(dist[i.origem] + i.peso + distR[i.destino] == dist[n] || dist[i.destino] + i.peso + distR[i.origem] == dist[n]){
            cout << " ";
            cout << i.id;
            minimas.push_back(i);   
            }
        
    }
    cout << endl;
    //Parte 3
    int tam = g.getTam();
    //Faz subgrafo das arestas minimas
    Graph sub(minimas, tam);
    //Acha as pontes que se rompidas, alteram a distância e tals
    vector<int>pontes = sub.achaPontes();
    cout << "Parte 3: ";
    if(pontes.empty()){
        cout << -1;
    }else{
        mergeSort(pontes, 0, pontes.size() - 1);
        for(size_t a = 0; a < pontes.size(); a++ ){
            cout<< pontes[a];
            if(a + 1 != pontes.size()) 
                cout << " ";
        }
        cout << endl;
    }

    
    delete[] dist; 
    delete[] distR;
    return 0;
}
