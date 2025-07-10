#include "heap.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

Heap::Heap(){
    cin >> this->tam;
    v = new Aresta[tam];
    for(int i = 0; i < tam; i++){
        cin >> v[i].u >> v[i].v >> v[i].custo;
    }
}
Heap::~Heap(){
    delete[] v;
}
int Heap::getNextR(int i) {
    if(2* i +2 >= tam){
        return -1;
    }
    return 2 * i + 2;
}
int Heap::getNextL(int i) {
    if(2 * i + 1 >= tam){
        return -1;
    }
    return 2 * i + 1;
}
void Heap::heapfy() {
  int i = (tam / 2) - 1;
  while (i >= 0) {
    i--;
    buildSub(i);
  }
}
void Heap::buildSub(int i){
    int menor = i;
    int l = getNextL(i);
    int r = getNextR(i);

    if (l != -1 && v[l].custo < v[menor].custo) {
        menor = l;
    }
    if (r != -1 && v[r].custo < v[menor].custo) {
        menor = r;
    }
    if (menor != i) {
        swap(&v[i], &v[menor]);
        buildSub(menor);
    }

}

void Heap::swap(Aresta *a, Aresta *b) {
    Aresta aux = *a;
    *a = *b;
    *b = aux;
}
Aresta Heap::removeMenor(){
    Aresta raiz = v[0];
    v[0] = v[tam-1];
    tam--;
    buildSub(0);
    return raiz;
}
bool Heap::isvazio(){
    return tam == 0;
}