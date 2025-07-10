#include "unionFind.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

UnionFind::UnionFind(int quantidade_subconjuntos) {
    subconjuntos = new Subconjunto[quantidade_subconjuntos];
    this->tamanho = quantidade_subconjuntos;
}
UnionFind::~UnionFind(){
    delete[] subconjuntos;
}
void UnionFind::Make(int x){
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;  
}
int UnionFind::Find(int x){
    if(subconjuntos[x].representante != x){
        subconjuntos[x].representante = Find(subconjuntos[x].representante);
    }
    return subconjuntos[x].representante;
}
void UnionFind::Union(int x, int y){
    int raizX = Find(x);
    int raizY = Find(y);

    if (raizX != raizY) { // Só une se estiverem em conjuntos diferentes
        if (subconjuntos[raizX].rank < subconjuntos[raizY].rank) {
            subconjuntos[raizX].representante = raizY;
        } else if (subconjuntos[raizX].rank > subconjuntos[raizY].rank) {
            subconjuntos[raizY].representante = raizX;
        } else {
            subconjuntos[raizY].representante = raizX;
            subconjuntos[raizX].rank++;
        }
    }

}