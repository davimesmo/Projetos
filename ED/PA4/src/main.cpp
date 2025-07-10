#include "heap.hpp"
#include "unionFind.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
    int n;
    cin >> n;

    UnionFind dsu(n);
    for(int i = 0; i<n; ++i){
        dsu.Make(i);
    }
    Heap arestitas;
    int custoAGM = 0;
    while(!arestitas.isvazio()){
        Aresta atual = arestitas.removeMenor();
        if(dsu.Find(atual.u) != dsu.Find(atual.v)){
            dsu.Union(atual.u, atual.v);
            custoAGM += atual.custo;
        }
    }
    cout << custoAGM << endl;
    return 0;
}
